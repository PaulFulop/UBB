# A client server implementation in python for the number guess problem.
#  The server chooses a random number.
#  The clients connect and send numbers to server.
#  The server returns to each client a status message:

# · ‘H’ – send a larger number

# · ‘S’ – send a lower number

# · ‘G’ – you guessed my number

# · ‘L’ – another client guessed the number. You are a loser !

import socket
import threading
from random import randint

HOST = '127.0.0.1'
PORT = 1234

found = False
mylock = threading.Lock()

# in order make the server worked even after someone has won and 
# the game has ended, i would probably need another thread that only
# runs when the game has ended, resetting the flags and the number

def handle_client(client_sock:socket.socket, random_num:int):
    global found, mylock
    with client_sock:
        while True:
            data = client_sock.recv(4)
            if not data:
                break

            num = int.from_bytes(data, 'big')

            if found == True:
                client_sock.sendall(b'L')
                break

            with mylock:
                if num < random_num:
                    client_sock.sendall(b'H')
                elif num > random_num:
                    client_sock.sendall(b'S')
                else:
                    client_sock.sendall(b'G')
                    found = True
                    break


def start_server():
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    sock.bind((HOST, PORT))
    sock.listen(5)
    print(f"Server connected to address ({(HOST, PORT)})...\n")

    random_num = randint(0, int(1e4))
    print(f"The number has been generated: {random_num}")

    with sock:
        while True:
            client_sock, client_addr = sock.accept()
            print(f"Client with address {client_addr} has connected...")

            client_thread = threading.Thread(target=handle_client, args=(client_sock, random_num))
            client_thread.start()


if __name__ == '__main__':
    start_server()