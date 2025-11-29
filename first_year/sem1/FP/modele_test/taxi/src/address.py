
class Address:
    def __init__(self, id:int, name:str, number:int, x:int, y:int):
        if id < 0 or len(name) < 3 or number not in range(0, 101) or x not in range(-100, 101) or y not in range(-100, 101):
            raise ValueError("Invalid address data")

        self.id = id
        self.name = name
        self.number = number
        self.x = x
        self.y = y

    def __str__(self):
        return f"{self.id}, {self.name}, {self.number}, {self.x}, {self.y}"