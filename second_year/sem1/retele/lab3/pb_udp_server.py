#Enunt: Clientul trimite serverului un sir de numere. Serverul le primeste, le afiseaza pe ecran si trimite clientului suma lor.

import socket
UDP_HOST = '127.0.0.1'
UDP_PORT = 1234

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.bind((UDP_HOST, UDP_PORT))
print(f"Connected to address with host: {UDP_HOST} and port: {UDP_PORT}\n")

while True:
    sum = 0
    len, address = s.recvfrom(1024)
    len = int.from_bytes(len)
    print(f"The server has received an array length of {len}...")

    while len:
        num = int.from_bytes(s.recvfrom(1024)[0])
        sum += num
        len -= 1 

    print(f"The sum is {sum}. Sending it to the client...\n")
    s.sendto(sum.to_bytes(), address)
        