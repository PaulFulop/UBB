# A client sends to the server a string. The server returns the count of spaces in the string.

import socket

HOST = ''
PORT = 1234

#the address in those cases is basically a tuple -> the host (like a school name) and the port (like the classroom number)

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
s.bind((HOST, PORT))
s.listen(5)
print(f"Server is listening on port {PORT}...")

conn, addr = s.accept() #conn is basically just another socket now, which can send and recv
print(f"The server accepted a connection on address {addr}!")

str = conn.recv(1024).decode().strip() # we receiva max 1024 bytes but we want to clearall the leading / trailing whitespaces
print(f"The server received the string {str}!")

count = 0
for ch in str:
    if ch == ' ':
        count += 1

print(f"Ths server has found {count} whitespaces in the string and it will return this number back to the client...")
conn.sendall(count.to_bytes(4, 'big'))

s.close()
conn.close()