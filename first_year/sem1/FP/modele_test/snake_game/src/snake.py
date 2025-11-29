
class Snake:
    def __init__(self, startX:int, startY:int, dir:str, bound:int):
        self.positions = [[startX - 1, startY], [startX, startY], [startX + 1, startY]]
        self.boundary = bound

        match dir:
            case "left":
                self.direction = [0, -1]
            case "right":
                self.direction = [0, 1]
            case "down":
                self.direction = [1, 0]
            case _:
                self.direction = [-1, 0]


    def move(self, n:int):
        if n < 0 or n > self.boundary:
            raise ValueError
        
        for i in range(n):
            self.move_tail()
            self.positions[0][0] += self.direction[0]
            self.positions[0][1] += self.direction[1]
    
    def move_left(self):
        self.direction = [0, -1]
        self.move_tail()
        self.positions[0][1] -= 1

    def move_right(self):
        self.direction = [0, 1]
        self.move_tail()
        self.positions[0][1] += 1

    def move_up(self):
        self.direction = [-1, 0]
        self.move_tail()
        self.positions[0][0] -= 1

    def move_down(self):
        self.direction = [1, 0]
        self.move_tail()
        self.positions[0][0] += 1

    def grow(self):
        tailX, tailY = self.positions[-1]
        tailX -= self.direction[0]
        tailY -= self.direction[1]
        self.positions.append([tailX, tailY])
    
    def check_collision(self):
        return self.positions[0][0] < 0 or self.positions[0][0] > self.boundary or self.positions[0][1] < 0 or self.positions[0][1] > self.boundary or self.positions[0] in self.positions[1:]

    def move_tail(self):
        for i in range(len(self.positions) - 1, 0, -1):
            self.positions[i][0] = self.positions[i - 1][0]
            self.positions[i][1] = self.positions[i - 1][1]