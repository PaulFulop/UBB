# A client server implementation in python for the number guess problem.
#  The server chooses a random number.
#  The clients connect and send numbers to server.
#  The server returns to each client a status message:

# ·‘H’ – send a larger number

# · ‘S’ – send a lower number

# · ‘G’ – you guessed my number

# · ‘L’ – another client guessed the number. You are a loser !

import socket

HOST = '127.0.0.1'
PORT = 1234

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect((HOST, PORT))

print(f"Connected to server at address ({(HOST, PORT)})...\nYou have to guess a number between 1 to 10k.\n")

with sock:
    while True:
        num = int(input('> '))
        print(f"Sending {num} to the server....")
        sock.sendall(num.to_bytes(4))

        letter = sock.recv(1).decode()
        print(letter + '\n')

        if letter in ('L', 'G'):
            break