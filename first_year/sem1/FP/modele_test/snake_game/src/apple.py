import random

class Apple:
    def __init__(self, bound:int):
        self.boundary = bound

    def generate_new_position(self):
        appleX = random.randint(1, self.boundary)
        appleY = random.randint(1, self.boundary)
        return [appleX, appleY]