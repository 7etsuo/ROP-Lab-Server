# Vulnerable TCP Server and Exploit Demonstration

**7etsuo, 2024**

- [Twitter](https://twitter.com/7etsuo)
- [GitHub](https://github.com/7etsuo)
- [YouTube](https://www.youtube.com/@snowcrash-)

---

![image](https://github.com/7etsuo/ROP-Lab-Server/assets/90065760/f057e627-2978-4f53-975e-f47473a20616)

---

> This repository contains a collection of files designed to demonstrate a buffer overflow exploit using Return-Oriented Programming (ROP) on a purposely vulnerable TCP server. The server is written in C, and the exploit is demonstrated using a Python script.

## Warning

**For Educational Use Only**: This software is intended to simulate security vulnerabilities for educational purposes only. It is designed for use in a controlled, consensual environment such as security training or software testing labs. Unauthorized testing against non-consenting systems is illegal and unethical.

## Components

- **`my_tcp.h` and `my_tcp.c`**: These files handle the basic TCP server operations, including socket initialization, binding, and client handling.
- **`main.c`**: Implements the main function of the server and includes the deliberately vulnerable function to demonstrate buffer overflow.
- **`gadgets.h` and `gadgets.c`**: Provide implementations of various ROP gadgets used in the exploit.
- **`exploit.py`**: A Python script that sends a payload designed to exploit the buffer overflow vulnerability in the TCP server.

## Setup Instructions

### Configuring Visual Studio Code

Three options to compile the server

1. **Disable Security Features for Compilation**: Configure your compiler to disable ASLR, stack cookies, etc., while keeping DEP enabled. This can be done in Visual Studio by setting the appropriate linker options:

    ```plaintext
    /DYNAMICBASE:NO /NXCOMPAT /GS-
    ```

2. **Compile the Server**: Open Visual Studio Command Prompt or use MinGW to compile the server:

    ```bash
    cl my_tcp.c main.c /Fe:vulnerable_server.exe /link /MACHINE:X86 /DYNAMICBASE:NO /NXCOMPAT /GS-
    ```

    or using MinGW:

    ```bash
    gcc my_tcp.c main.c -o vulnerable_server.exe -Wl,--dynamicbase=no,--nxcompat -fno-stack-protector -lws2_32
    ```

3. To compile the C server in Visual Studio Code with MinGW, set up the `tasks.json` file under the `.vscode` folder with the appropriate tasks configuration:

1. **Create a `.vscode` directory** in your project root if it doesn't already exist.
2. **Create or edit the `tasks.json` file** inside the `.vscode` folder to include the following task configuration:

    ```json
    {
        "version": "2.0.0",
        "tasks": [
            {
                "label": "build vulnerable server",
                "type": "shell",
                "command": "gcc",
                "args": [
                    "-o",
                    "${fileDirname}\\${fileBasenameNoExtension}.exe",
                    "${fileDirname}\\${fileBasename}",
                    "-m32",  // Compiles the code to run on 32-bit Windows
                    "-Wl,-dynamicbase:no",  // Disables ASLR (Address Space Layout Randomization)
                    "-Wl,-nxcompat",        // Enables DEP (Data Execution Prevention)
                    "-fno-stack-protector"  // Disables stack protection (stack cookies)
                ],
                "group": {
                    "kind": "build",
                    "isDefault": true
                },
                "presentation": {
                    "echo": true,
                    "reveal": "always",
                    "focus": false,
                    "panel": "shared",
                    "showReuseMessage": true,
                    "clear": false
                },
                "problemMatcher": "$gcc",
                "detail": "Compiler task configured to disable ASLR, enable DEP, and disable stack protection."
            }
        ]
    }
    ```

This configuration sets up a build task that compiles the C server using GCC with flags to disable ASLR, enable DEP, and disable stack cookies, ensuring that the environment is configured for the purposes of demonstrating the vulnerability exploit.

### Compile the Server

Open the command palette in VSCode (Ctrl+Shift+P), type "Run Build Task", and select the "build vulnerable server" task. This compiles the server according to the specified settings in `tasks.json`.

### Running the Server and Exploit

- **Run the Server**: Navigate to the output directory in your terminal or command prompt and execute the server:

    ```bash
    ./vulnerable_server.exe
    ```

- **Run the Exploit**: Make sure the server is running and listening on the default TCP port 12345. Execute the Python script `exploit.py` from a command line:

    ```bash
    python exploit.py
    ```

## Exploit Details

The Python script, `exploit.py`, sends a payload that exploits a buffer overflow vulnerability, manipulating the stack and using ROP to execute arbitrary code through carefully chosen gadgets.
