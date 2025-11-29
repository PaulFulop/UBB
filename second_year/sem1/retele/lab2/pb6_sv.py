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
import threading
from random import randint

ADDRESS = ('127.0.0.1', 1234)
mylock = threading.Lock()
finihed = False

def handle_client(client_sock:socket.socket, num:int):
    global mylock, finihed

    with client_sock:
        attempts = 1
        while not finihed:
            client_num = int.from_bytes(client_sock.recv(4), 'big')
            if num == client_num:
                mylock.acquire_lock()
                finihed = True
                mylock.release_lock()

                win_msg = 'You win - within ' + str(attempts) + ' tries!'
                client_sock.sendall(win_msg.encode())
                return
            elif num < client_num:
                client_sock.sendall(b'smaller')
            else:
                client_sock.sendall(b'larger')
            attempts += 1
        
        lost_msg = 'You lost - after ' + str(attempts) + ' retries!'
        client_sock.sendall(lost_msg.encode())

def start_server():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
        sock.bind(ADDRESS)
        print(f"Server has connected to address {ADDRESS}")
        num = randint(0, 100)
        print(f"The number generated is {num}")
        sock.listen(5)

        while True:
            client_sock, client_addr = sock.accept() 
            print(f"Client from address {client_addr} has connected!")
            client_thread = threading.Thread(target=handle_client, args=(client_sock, num))
            client_thread.start()


if __name__ == '__main__':
    start_server()