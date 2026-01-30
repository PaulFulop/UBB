# Define a simple structure (e.g., a Person object with firstname, lastname, gender  and age).
# The client sends this structure to the server.
# The server increments the age and sends the updated structure back.

import socket
import json

ADDR = ('127.0.0.1', 1234)

def start_server():
    try:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
           sock.bind(ADDR)
           sock.listen(5)
           print(f"Server listening on {ADDR}...")

           conn, addr = sock.accept()
           print(f"Client from {addr} has connected to the server...")

           data = conn.recv(1024)
           if data:
               obj = json.loads(data)
               obj['age'] += 1
               print(f"Sending {obj} back to the client...")
               conn.sendall(json.dumps(obj).encode())
    except Exception as e:
        print(f"Some error occured: {e}")

if __name__ == '__main__':
    start_server()