import socket
import select

ADDR = ('192.168.0.248', 1234)

def start_server():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server:
        server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        server.setblocking(False)
        server.bind(ADDR)
        server.listen(5)
        sockets = [server]

        print(f"Server is listening on port {ADDR[1]}...")
        while True:
            readable, _, _ = select.select(sockets, [], []) # server is listening...

            for s in readable:
                if s is server:
                    conn,addr = server.accept()
                    sockets.append(conn)
                    print(f"Client {addr} has joined!")
                else:
                    try:
                        data = s.recv(1024)
                        if data:
                            for client_con in sockets:
                                if client_con != server and client_con != s:
                                    client_con.sendall(data)
                        else:
                            print(f"Client {addr} has disconnected...")
                            sockets.remove(s)
                            s.close()
                    except ConnectionResetError:
                        print(f"Client {addr} has disconnected...")
                        sockets.remove(s)
                        s.close()

if __name__ == '__main__':
    start_server()