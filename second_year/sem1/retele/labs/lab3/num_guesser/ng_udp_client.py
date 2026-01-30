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
guessed = False

try:
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as sock:
        print("You need to guess a number between 0 and 10k.\n")

        while not guessed:
            num = int(input("> "))
            sock.sendto(num.to_bytes(4, 'big'), (HOST, PORT))
            letter = sock.recvfrom(1)[0].decode()
            print(letter)
            if letter in ('G', 'L'):
                guessed = True
except Exception as e:
    print(str(e))