<#
.SYNOPSIS
    A PowerShell script to attach a debugger to a running process or a service.

.DESCRIPTION
    This script allows you to attach a debugger (WinDBG) to a running process or a service, with optional commands executed at the start of the debugging session.
    It can also start an executable specified by a file path and attach the debugger to it.

.PARAMETER service_name
    The name of the service to restart and attach the debugger to (optional).
    If specified, the script will restart the service and then attach the debugger to the associated process.

.PARAMETER path
    The file path of the executable to debug (optional).
    If specified, the script will start the executable and then attach the debugger to it.
    Note: You cannot use both service_name and path parameters at the same time.

.PARAMETER process_name
    The name of the running process to attach the debugger to (required).
    Do not include the ".exe" extension in the process name.

.PARAMETER commands
    A semicolon-separated string of WinDBG commands to be executed at the beginning of the debugging session (optional).
    If not provided, the debugger will start without any initial commands.

.EXAMPLE
    C:\PS> .\attach-process.ps1 -service-name fastbackserver -process-name fastbackserver -commands 'bp wsock32!recv'

    This example restarts the fastback server service, then attaches the debugger to the fastback server process.
    Additionally, it sets a breakpoint at the wsock32!recv function as an initial command.

.EXAMPLE
    C:\PS> .\attach-process.ps1 -process-name Notepad

    This example attaches the debugger to the running Notepad process without executing any initial commands.
    Note: Do not include the ".exe" extension in the process name.
#>

[CmdletBinding()]
param (
    [Parameter()]
    [ValidateNotNullOrEmpty()]
    [string]
    $commands
)

DynamicParam {
        $svc_param = 'service-name'
        $RuntimeParameterDictionary = New-Object System.Management.Automation.RuntimeDefinedParameterDictionary
        $AttributeCollection = New-Object System.Collections.ObjectModel.Collection[System.Attribute]
        $ParameterAttribute = New-Object System.Management.Automation.ParameterAttribute
        $AttributeCollection.Add($ParameterAttribute)
        $svc_set = Get-Service | select -ExpandProperty Name
        $ValidateSetAttribute = New-Object System.Management.Automation.ValidateSetAttribute($svc_set)
        $AttributeCollection.Add($ValidateSetAttribute)
        $RuntimeParameter = New-Object System.Management.Automation.RuntimeDefinedParameter($svc_param, [string], $AttributeCollection)
        $RuntimeParameterDictionary.Add($svc_param, $RuntimeParameter)
        $ps_param = 'process-name'
        $ps_attrs = New-Object System.Collections.ObjectModel.Collection[System.Attribute]
        $ps_paramattr = New-Object System.Management.Automation.ParameterAttribute
        $ps_attrs.Add($ps_paramattr)
        $ps_rtp = New-Object System.Management.Automation.RuntimeDefinedParameter($ps_param, [string], $ps_attrs)
        $RuntimeParameterDictionary.add($ps_param, $ps_rtp)
        $name_param = 'path'
        $name_attrs = New-Object System.Collections.ObjectModel.Collection[System.Attribute]
        $name_paramattr = New-Object System.Management.Automation.ParameterAttribute 
        $name_attrs.Add($name_paramattr)
        $name_rtp = New-Object System.Management.Automation.RuntimeDefinedParameter($name_param, [string], $name_attrs)
        $RuntimeParameterDictionary.add($name_param, $name_rtp)
        return $RuntimeParameterDictionary
}

begin {
    $service_name = $PsBoundParameters[$svc_param]
    $path = $PsBoundParameters[$name_param]

    if ($service_name -and $path) {
        Write-Error "Cannot specify -service-name and -path arguments together." -ErrorAction Stop
    }

    if ($path) {
        $path_validate = Test-Path $path
        if ($path_validate -eq $false ) {
            Write-Error "Supplied -path $path argument does not exist" -ErrorAction Stop
        }

        Write-Host "[+] Starting $path"
        $pathproc = Start-Process -FilePath $path -PassThru
    }

    if ($service_name) {
        $svc = get-service -name $service_name

        if ($svc.status -ne 'Running') {
            Write-Host "[+] Starting $service_name"
            start-service -name $service_name
        }        
    }

    $process_name = $PsBoundParameters[$ps_param]
}

process {
    $process = Get-Process $process_name

    if (-not $process) {
        Write-Host "[-] Killing $pathproc"
        stop-process $pathproc
        Write-Error "Supplied -process-name $process_name not found" -ErrorAction Stop
    }

    $cmd_args = "-WF c:\Tools\windbg_custom.WEW -p $($process.id)"
    
    if ($commands) {
        $cmd_args += " -c '$commands'"
    } else {
        $cmd_args += " -g"
    }
    
    write-host "[+] Attaching to $process_name"
    start-process -wait -filepath "C:\Program Files (x86)\Windows Kits\10\Debuggers\x86\windbg.exe" -verb RunAs -argumentlist $cmd_args

    if ($service_name) {
        Do {
            restart-service -name $service_name -force -erroraction silentlycontinue 

            $svc = get-service -name $service_name 

            If ($svc.status -ne 'Running') { 
                Write-Host "Waiting for service $service_name to start" 
                Start-Sleep -Milliseconds 250 
            } Else { 
                Write-Host "[+] $service_name has been restarted" 
            }
        }
        Until ($svc.status -eq 'Running')
    }
}
