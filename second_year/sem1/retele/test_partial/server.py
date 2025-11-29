import socket
import threading

TCP_ADDR = ('192.168.40.125', 1234)
UDP_ADDR = ('192.168.40.125', 1235)

total_msg = {}

def traduce_pasareasca(text:str) -> str:
    pasareasca = ""
    for i in range(len(text)):
        pasareasca += text[i]
        if text[i] in "aeiouAEIOU":
            pasareasca += 'p' + text[i]
    
    return pasareasca

def start_server_tcp():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
        sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        sock.bind(TCP_ADDR)
        print(f"Server has connected to {TCP_ADDR}")
        sock.listen(5)

        while True:
            conn, client_addr = sock.accept()
            user = conn.recv(1024).decode()
            print(f"{user} from {client_addr} has connected!")
            ip = client_addr[0]
            total_msg[ip] = 0
            msg = 'Connection successful. Switching to UDP.'
            conn.sendall(msg.encode())

            

def start_server_udp():
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as sock:
        sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        sock.bind(UDP_ADDR)
        
        while True:
            txt, ret_addr = sock.recvfrom(1024)
            txt = txt.decode()

            ip = ret_addr[0]
            total_msg[ip] = total_msg.get(ip) + 1

            if txt.lower().removesuffix('\n') == "stop":
                sock.sendto(txt.encode(), ret_addr)
                reply = f"The client from {ip} has sent {total_msg[ip]} messages!"
                print(reply)
                continue

            pasareasca = traduce_pasareasca(txt)
            print(f"Sending {pasareasca} back to the client...")
            sock.sendto(pasareasca.encode(), ret_addr)


def start_server():
    th = threading.Thread(target=start_server_tcp, daemon=True)
    th.start()
    start_server_udp()

if __name__ == '__main__':
    start_server()