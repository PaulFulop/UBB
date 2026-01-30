# A client server implementation in python for the number guess problem.
#  The server chooses a random number.
#  The clients connect and send numbers to server.
#  The server returns to each client a status message:

# ·‘H’ – send a larger number

# · ‘S’ – send a lower number

# · ‘G’ – you guessed my number

# · ‘L’ – another client guessed the number. You are a loser !

import socket
from random import randint

HOST = '127.0.0.1'
PORT = 1234
flag = False

try:
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as sock:
        sock.bind((HOST, PORT))
        sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        print(f"Server connected to address ({(HOST, PORT)})...")
        rand_num = randint(0, int(1e4))
        print(f"The number has been generated: {rand_num}\n")

        while True:
            data, client_addr = sock.recvfrom(1024)
            num = int.from_bytes(data, 'big')

            if flag:
                sock.sendto(b'L', client_addr)
                print(f"Client from address ({client_addr}) is a loser {num}...\n")


            print(f"Client from address ({client_addr}) has sent the number {num}...\n")

            if num > rand_num:
                sock.sendto(b'S', client_addr)
            elif num < rand_num:
                sock.sendto(b'H', client_addr)
            else:
                sock.sendto(b'G', client_addr)
                print(f"Client from address ({client_addr}) is a winner!\n")
                flag = True
except Exception as e:
    print(str(e))