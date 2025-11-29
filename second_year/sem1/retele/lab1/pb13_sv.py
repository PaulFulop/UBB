# The client sends a small text file to the server.
# The server saves the file and returns the length
# of the received file content as an unsigned integer

import socket

ADDR = ('127.0.0.1', 1234)

def start_server():
    try:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
            sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            sock.bind(ADDR)
            sock.listen(5)
            print(f"Server listening on {ADDR}")
            conn, addr = sock.accept()
            print(f"Client from {addr} connected. Receiving text file...\n")

            fileName = "copy_" + conn.recv(1024).decode()
            with open(fileName, 'w') as file:
                data = conn.recv(2000) # up to 2000 chars ig
                text = data.decode()
                count = file.write(text)

            print(f"Sending {count} to the client...\n")
            conn.sendall(count.to_bytes(4, 'big'))
    except Exception as e:
        print(f"Some error occured: {e}")

if __name__ == '__main__':
    start_server()