import socket  

TCP_ADDR = ('192.168.40.125', 1234)
UDP_ADDR = ('192.168.40.125', 1235)

def connect_tcp():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
        user = input("Insert username: ")
        sock.connect(TCP_ADDR)
        print(f"Connected to {TCP_ADDR}")
        sock.sendall(user.encode())
        msg = sock.recv(1024).decode()
        print(msg)


def connect_udp():
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as sock:
        sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        while True:
            txt = input("Insert a text here: ")
            if txt.lower() == 'stop':
                print("The game has ended. Thank you!")
                break

            print("Sending the text to the server...")
            sock.sendto(txt.encode(), UDP_ADDR)
            pasareasca = sock.recvfrom(1024)[0].decode()

            print(f"The text in pasareasca is: {pasareasca}!")

if __name__ == '__main__':
    connect_tcp ()
    connect_udp()