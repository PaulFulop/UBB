#  The client sends periodical PING datagrams
#  with a random content to a <server> and <port>
#  specified in command line. The server returns back (echoes)
#  the same packets (content). 
#  The client checks the content of the received packets to match
#  what was sent and computes the round trip time and displays it to
#  the user – for each sent packet.

import socket
import sys
import time

HOST = '127.0.0.1'
PORT = 1234

try:
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.bind((HOST, PORT))

    print(f"Server bound to port {PORT}. Listening... ")

    while True:
        content, client_addr = sock.recvfrom(1024)
        sock.sendto(content, client_addr)
        print(f"Sending data ({content}) back to the client...")
except Exception as e:
    print(str(e))