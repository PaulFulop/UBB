# The clients send an integer number N and an array of N float values.
# The server will merge sort the numbers received from all clients until
# it gets an empty array of floats (N=0).
# The server returns to each client the size of the merge-sorted
# array followed by the merge-sorted arrays of all floats from all clients.

import socket
import select
import pickle

ADDR = ('127.0.0.1', 1234)

def merge_sort(l1:list, l2:list, N:int) -> list:
    if not len(l1):
        return sorted(l2)
    if not len(l2):
        return sorted(l1)

    new_list = []
    m = len(l1)


    i, j = 0, 0
    while i < m and j < N:
        if l1[i] < l2[j]:
            new_list.append(l1[i])
            i += 1
        else:
            new_list.append(l2[j])
            j += 1

    while i < m:
        new_list.append(l1[i])
        i += 1
    while j < N:
        new_list.append(l2[j])
        j += 1
    return new_list

def start_server():
    try:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
            sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            sock.bind(ADDR)
            print(f"Server listening on address {ADDR}...")
            sock.listen(5)
            sockets = [sock]
            full_list = []
            
            while True:
                readable, _, _ = select.select(sockets, [], [])

                for s in readable:
                    if s is sock:
                        conn, client_addr = sock.accept()
                        sockets.append(conn)
                        print(f"Client {client_addr} has connected!") 
                    else:
                        n = int.from_bytes(s.recv(1024))
                        if not n:
                            n1 = len(full_list)
                            print("We got an empty array! Sending it all...")
                            for s1 in sockets:
                                if s1 != sock:
                                    s1.sendall(int.to_bytes(n1, 4, 'big'))
                                    s1.sendall(pickle.dumps(full_list))
                            return

                        
                        arr = pickle.loads(s.recv(1024))
                        print(f"Got {n} and {arr} from {s.getpeername()}!")

                        full_list = merge_sort(full_list, arr, n)
                        print(f"List merged and sorted: {full_list}")
    except Exception as e:
        print(f"Some error occured: {e}")

if __name__ == '__main__':
    start_server()