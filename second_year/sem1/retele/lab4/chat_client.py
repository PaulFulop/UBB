import socket

HOST = '172.21.117.89'
PORT = 5678

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
    sock.connect((HOST, PORT))
    while True:
        data = sock.recv(1024)
        msg = data.decode()

        if msg.lower() == 'please provide your username:\n':
            user = input(msg)
            sock.sendall((user + '\n').encode())
        else:
            print(msg)