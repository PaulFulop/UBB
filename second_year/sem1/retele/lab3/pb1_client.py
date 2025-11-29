# The client sends periodical PING datagrams
# with a random content to a <server> and <port>
#  specified in command line. The server returns back (echoes)
#  the same packets (content). 
#  The client checks the content of the received packets to match
#  what was sent and computes the round trip time and displays it to
#  the user – for each sent packet.

import socket
import sys
import random
import time

try:
    sv_addr = (sys.argv[1], int(sys.argv[2]))
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    packets_num = int(input("How many packets do you want to send to the server?\n\n> "))
    while packets_num:
        time.sleep(3.0)
        packet = random.randint(0, 1000).to_bytes(4)
        print(f"Sending package ({packet})...\n")

        start_time = time.perf_counter_ns()
        sock.sendto(packet, sv_addr)
        print("Waiting for the package to come back...")
        recv_packet = sock.recvfrom(1024)[0]
        end_time = time.perf_counter_ns()

        if packet == recv_packet:
            print("The client received the same packet!")
        else:
            print("The cliend did not receive the same package!")

        rtt = (end_time - start_time) / 1e9
        print(f"Round trip time: {rtt} seconds")

        packets_num -= 1

    print("\nGoodbye!\n")
except Exception as e:
    print(str(e))