#  Implement the Chat server example (see the link bellow) using UDP and TCP
# –only this time each client should contact the server
# just for registration. All communication happens directly
#  between the peers (clients) without passing trough the server.
# Each client maintains an endpoint (TCP/UDP) with the server just
#  for learning the arrival/departure of other clients.
#   You create a mesh architecture where all clients connect
#  directly between each others.

import socket
SEND_ADDR = ('255.255.255.255', 1234)
RECV_ADDR = ('', 1234)

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
sock.bind(RECV_ADDR)

print("Server is ready...")
while True:
    data = sock.recvfrom(1024)[0]
    if data:
        sock.sendto(data, SEND_ADDR)