# Define a simple structure (e.g., a Person object with firstname, lastname, gender  and age).
# The client sends this structure to the server.
# The server increments the age and sends the updated structure back.

import socket
import json

ADDR = ('127.0.0.1', 1234)

class Person():
    def __init__(self, firstname='', lastname='', gender=False, age=0):
        self.firstname = firstname
        self.lastname = lastname
        self.gender = gender
        self.age = age
    
    def __str__(self):
        return f"{self.firstname}\n{self.lastname}\n{'male' if self.gender else 'female'}\n{self.age}"
    

def start_client():
    try:
        firstname = input("Insert first name: ")
        lastname = input("Insert last name: ")
        gender = True if input("Insert gender (male / female): ").lower() == 'male' else False
        age = int(input("Insert age: "))
        if age < 1 or age > 100:
            raise Exception("Invalid age.")
        
        person = Person(firstname, lastname, gender, age)
        print(f"This person has the age {person.age}")

        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
            sock.connect(ADDR)
            print("Connected to the server. Sending the person object to the server...")
            sock.sendall(json.dumps(person.__dict__).encode())
            print("Waiting for the age of the person object to increment...")
            data = sock.recv(1024)
            if data:
                obj = json.loads(data)
                person = Person()
                person.__dict__.update(obj)
                print(f"The age of the person has been updated. Now the person has the age {person.age}")
                print(person)
    except Exception as e:
        print(f"Some error occured: {e}")

if __name__ == '__main__':
    start_client()