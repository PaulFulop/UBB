import socket
from datetime import datetime

PORT = 1234
HOST = ''

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
s.bind((HOST, PORT))
s.listen(5)

print(f"Server listening on port {PORT}...")
conn, addr = s.accept()
print(f"Connected from address {addr}!")

data = conn.recv(1024)
date_str = data.decode().strip()
date_obj = datetime.strptime(date_str, "%Y-%m-%d")
date_name = date_obj.strftime("%A")

print(f"Sending {date_name}...")
conn.sendall(date_name.encode())

conn.close()
s.close()