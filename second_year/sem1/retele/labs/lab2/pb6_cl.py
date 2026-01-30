# The server chooses a random integer number.
# Each client generates a random integer number and send it to the server.
# The server answers with the message “larger”
#  if the client has sent a smaller number than the server’s choice,
#   or with message “smaller” if the client has send a larger number than the server’s choice.

# Each client continues generating a different random number (larger or smaller than the previous) according to the server’s indication.
# When a client guesses the server choice – the server sends back to the winner the message “You win – within x tries”.
# It also sends back to all other clients the message “You lost – after y retries!” (x and y are the number of tries of each respective client). 
# The server closes all connections upon a win and it chooses a different random integer for the next game (set of clients)

import socket
from random import randint
import time

ADDRESS = ('127.0.0.1', 1234)
finished = False

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect(ADDRESS)

while not finished:
    try:
        rand_num = randint(0, 100)
        sock.sendall(rand_num.to_bytes(4, 'big'))
        print(f"Sending {rand_num}...")
        msg = sock.recv(1024).decode()
        
        if msg.find('lost') != -1 or msg.find('win') != -1:
            finished = True
        print(f"{msg}\n")
    except socket.error:
        break

    time.sleep(0.125)