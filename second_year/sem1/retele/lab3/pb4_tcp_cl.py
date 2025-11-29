import socket
import threading

ADDR = ('192.168.0.248', 1234)

def handle_receiving_msgs(conn:socket.socket):
    while True:
        try:
            data = conn.recv(1024)
            if not data:
                print("Server closed connection.")
                break
            print(f"\n{data.decode()}\n> ", end="", flush=True)
        except Exception as e:
            print(f"Error in thread: {e}")
            break


def start_client():
    try:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
            sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            sock.connect(ADDR)

            thread = threading.Thread(target=handle_receiving_msgs, args=[sock], daemon=True)
            thread.start()

            while True:
                msg = input("> ")
                if msg:
                    sock.sendall(msg.encode())
    except Exception as e:
        print(f"Connection error: {e}")


if __name__ == '__main__':
    start_client()