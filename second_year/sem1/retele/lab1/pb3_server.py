# A client sends to the server a string. The server returns the reversed string to the client (characters from the end to beginning)

import socket

HOST = ''
PORT = 1234

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
s.bind((HOST, PORT)) # binding to the address
s.listen(5)

print(f"Server is listening on port {PORT}...")

conn, addr = s.accept()
str = conn.recv(1024).decode().strip()
print(f"The server has received {str}!")

reversed_str = ""
for i in range(len(str) - 1, -1, -1):
    reversed_str += str[i]

print(f"The reversed string is: {reversed_str}; sending it back to the client...")
conn.sendall(reversed_str.encode())

conn.close()
s.close()