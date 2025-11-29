
class Player:
    def __init__(self, id:int, name:str, strength:int):
        self.id = id
        self.name = name
        self.strength = strength
    
    def __str__(self):
        return f"{self.id}, {self.name}, {self.strength}"