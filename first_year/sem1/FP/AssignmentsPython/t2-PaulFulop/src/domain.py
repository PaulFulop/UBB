
class Adress:
    def __init__(self, id:int, street_name:str, street_number:str, x:int, y:int):

        if id < 0 or len(street_name) < 3:
            raise ValueError("Invalid address data.")

        self.id = id
        self.street_name = street_name
        self.street_number = street_number
        self.x = x
        self.y = y

    def __str__(self):
        return f"{self.id}, {self.street_name}, {self.street_number}, {self.x}, {self.y}"
        