# The clients send an integer number N and an array of N float values.
# The server will merge sort the numbers received from all clients until
# it gets an empty array of floats (N=0).
# The server returns to each client the size of the merge-sorted
# array followed by the merge-sorted arrays of all floats from all clients.

ADDR = ('127.0.0.1', 1234)

import socket
import threading
import pickle
import sys

flag = True

def handle_receive(sock:socket.socket):
    global flag
    N = int.from_bytes(sock.recv(1024), 'big')
    arr = pickle.loads(sock.recv(1024))
    flag = False
    print(f"We got the final length {N} and the final array {arr}! gg")
    sys.exit() # not good practice but yea

def start_client():
    global flag
    try:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
            sock.connect(ADDR)
            print(f"Connected to address {ADDR}...")
            worker = threading.Thread(target=handle_receive, args=[sock], daemon=True)
            worker.start()

            while flag:
                try:
                    arr = []
                    N = int(input("N - "))
                    sock.sendall(int.to_bytes(N, 4, 'big'))
                    print(f"Sending {N}...")
                    if not N: continue

                    for i in range(N):
                        elem = int(input(f"{i + 1} - "))
                        arr.append(elem)
                except Exception as e:
                    continue
                
                sock.sendall(pickle.dumps(arr))
                print(f"Sending {arr}...")
    except Exception as e:
        print(f"Some error occured: {e}")

if __name__ == '__main__':
    start_client()