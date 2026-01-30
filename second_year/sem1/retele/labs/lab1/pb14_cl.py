# The client sends an array of boolean values.
# The server counts how many true values are in the
# array and returns the count.

import socket
import pickle
from random import randint, choice

ADDR = ('127.0.0.1', 1234)

# generate a random boolean array 
def generate_boolean_array() -> list:
    len = randint(4, 18)
    arr = []

    while len:
        arr.append(choice([False, True]))
        len -= 1

    return arr


def start_client():
    arr = generate_boolean_array()
    print(f"Generated array: {arr}.\nSending it to the server...")

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
        sock.connect(ADDR)
        print(f"Connected to {ADDR}...")

        pickled_arr = pickle.dumps(arr)
        print("Sending data...")
        sock.sendall(pickled_arr)

        count = int.from_bytes(sock.recv(1024), 'big')
        print(f"There are {count} true values in the boolean array.")

if __name__ == '__main__':
    start_client()