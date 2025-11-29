#2.   The client sends the complete path to a file. 
# The server returns back the length of the file and its 
# content in the case the file exists. When the file does not
#  exist the server returns a length of -1 and no content.
#  The client will store the content in a file with the same name as the input 
# file with the suffix –copy appended (ex: for f.txt => f.txt-copy).

import socket
import os
import struct

# 'C:\Users\Gaboruu\Informatica\Retele\test.txt'

PORT = 5000
HOST = '10.63.203.89'

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))
print(f"Connected on adress with host {HOST} and port {PORT}...")
address = input("Insert the path here: ")

#address_bytes = struct.pack('!s', address)

s.sendall((address + '\n').encode())
fileName = os.path.basename(address) + '-copy'

length = s.recv(8)

if length != -1:
    text = s.recv(4096).decode().strip()
    print(int.from_bytes(length))
    print(text)

    with open(fileName, 'w') as file:
        file.write(text)
else:
    print("There was no file!\n")

s.close()