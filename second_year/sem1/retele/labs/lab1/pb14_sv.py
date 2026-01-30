# The client sends an array of boolean values.
# The server counts how many true values are in the
# array and returns the count.


class Person:
    def __init__(self):
        self.firstName = ''
        self.lastName = ''
        self.gender = False
        self.age = 0

import socket
import pickle
ADDR = ('127.0.0.1', 1234)

def start_server():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
        sock.bind(ADDR)
        sock.listen(5)
        print(f"Server listening to address {ADDR}...")

        conn, addr = sock.accept()
        print(f"Client from address {addr} has connected...")

        data = conn.recv(1024)
        pickled_arr = pickle.loads(data)
        print(f"Received array: {pickled_arr}")
        count = len([m for m in pickled_arr if m is True])

        print(f"Sending {count} back to the client...")
        conn.sendall(count.to_bytes(4, 'big'))

if __name__ == '__main__':
    start_server()