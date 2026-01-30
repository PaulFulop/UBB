import socket
import pickle
import struct
PORT = 1234

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

arr = list(map(int, input("Enter numbers: ").split()))
s.connect( ("10.42.213.89", PORT) )
data = pickle.dumps(arr)


s.sendall(len(data).to_bytes(4, 'big'))
s.sendall(data)

c = s.recv(4)
c = struct.unpack("!i", c)
print(f"The sum is: {c[0].__format__('d')}")

s.close()