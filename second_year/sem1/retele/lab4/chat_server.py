import socket
import threading
from contextlib import suppress

HOST = '0.0.0.0'
PORT = 5678
ENCODING = 'utf-8'

clients_lock = threading.Lock()
clients = {}  # username -> conn


def send(conn: socket.socket, msg: str):
    conn.sendall((msg + '\n').encode(ENCODING))


def recv_line(conn: socket.socket):
    """Read until '\n'. Returns decoded line (str) or None on disconnect."""
    buf = bytearray()
    while True:
        chunk = conn.recv(1024)
        if not chunk:           # client closed
            return None
        buf.extend(chunk)
        if b'\n' in chunk:
            line, _, _ = buf.partition(b'\n')
            return line.decode(ENCODING, errors='replace').strip()


def broadcast(message: str, exclude: set[str] = frozenset()):
    """Send to all clients except usernames in 'exclude'."""
    with clients_lock:
        dead = []
        for user, conn in clients.items():
            if user in exclude:
                continue
            with suppress(Exception):
                send(conn, message)
        # Optionally: remove dead sockets if you track failures


def handle_client(conn: socket.socket, addr):
    username = None
    try:
        send(conn, "Please provide your username:")
        username = recv_line(conn)
        if not username or any(ch.isspace() for ch in username):
            with suppress(Exception):
                send(conn, "Invalid username. Bye.")
            return

        with clients_lock:
            if username in clients:
                send(conn, "Username already taken. Bye.")
                return
            clients[username] = conn

        send(conn, f"Welcome, {username}!")
        broadcast(f"{username} has joined the chat.", exclude={username})

        # Message loop
        while True:
            line = recv_line(conn)
            if line is None:          # disconnect
                break
            if not line:
                continue
            if line.lower() in {"quit", "/quit", "exit", "/exit"}:
                break
            broadcast(f"{username}: {line}")

    except Exception as e:
        # Log if you want: print(f"Error with client {addr}: {e}")
        pass
    finally:
        # Clean up user + notify others
        with clients_lock:
            if username and clients.get(username) is conn:
                clients.pop(username, None)
        broadcast(f"{username} disconnected." if username else f"{addr} disconnected.")
        with suppress(Exception):
            conn.shutdown(socket.SHUT_RDWR)
            conn.close()


def server():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        s.bind((HOST, PORT))
        s.listen()
        print(f"Server listening on port {PORT}...")

        while True:
            conn, addr = s.accept()
            # Low-latency small sends (optional)
            with suppress(Exception):
                conn.setsockopt(socket.IPPROTO_TCP, socket.TCP_NODELAY, 1)
            print(f"Connected by {addr}")
            threading.Thread(target=handle_client, args=(conn, addr), daemon=True).start()


if __name__ == "__main__":
    server()