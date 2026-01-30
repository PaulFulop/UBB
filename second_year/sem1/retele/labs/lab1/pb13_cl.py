# The client sends a small text file to the server.
# The server saves the file and returns the length
# of the received file content as an unsigned integer

import socket

ADDR = ('127.0.0.1', 1234)

def start_client():
    try:
        fileName = input("Insert the name of the file you want to send here: ")

        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
            sock.connect(ADDR)
            print("Connected to the server. Sending text file...\n")

            sock.sendall(fileName.encode()) # sending the name of the file first
            with open(fileName, 'rb') as file:
                data = file.read()
                sock.sendall(data)
            
            print("The file has been sent!")
            count = int.from_bytes(sock.recv(1024), 'big')
            print(f"The file has a length of {count}.")
    except Exception as e:
        print(f"Some error occured: {e}")

if __name__ == '__main__':
    start_client()