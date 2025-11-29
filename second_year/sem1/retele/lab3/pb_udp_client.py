import socket

UDP_HOST = '127.0.0.1'
UDP_PORT = 1234
ADDR = (UDP_HOST, UDP_PORT)

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

len = int(input("Insert the length of the array here: "))
s.sendto(len.to_bytes(), ADDR)

while len:
    num = int(input("> "))
    s.sendto(num.to_bytes(), ADDR)

    len -= 1

print("All the data has been sent to the server...\n")

sum = int.from_bytes(s.recvfrom(1024)[0])
print(f"The sum is {sum}")