from board import Board
from snake import Snake
from apple import Apple

class Services:
    s_symbol_head = '*'
    s_symbol_tail = '+'
    a_symbol = 'a'

    def __init__(self, board_size:int, num_apples:int):
        self.snake = Snake(board_size // 2, board_size // 2, "up", board_size  - 1)
        self.apple = Apple(board_size - 2)
        self.board = Board(board_size)
        self.apples = self.generate_apples(num_apples)
        self.mark_board()

    def generate_apples(self, num_apples):
        apples = []
        while len(apples) != num_apples:
            appleX, appleY = self.apple.generate_new_position()

            if self.verify_valid_apple(appleX, appleY):
                self.board[appleX, appleY] = Services.a_symbol
                apples.append([appleX, appleY])
        
        return apples

    def clear_board(self):
        for i in range(self.board.size):
            for j in range(self.board.size):
                self.board[i, j] = ' '

    def verify_valid_apple(self, appleX, appleY):
        return self.board[appleX, appleY] == ' ' and self.board[appleX - 1, appleY] != Services.a_symbol and self.board[appleX + 1, appleY] != Services.a_symbol and self.board[appleX, appleY - 1] != Services.a_symbol and self.board[appleX, appleY + 1] != Services.a_symbol

    def mark_board(self): 
        self.clear_board()       
        for apple_pos in self.apples:
            self.board[apple_pos[0], apple_pos[1]] = Services.a_symbol

        for snake_pos in self.snake.positions:
            self.board[snake_pos[0], snake_pos[1]] = Services.s_symbol_tail
        
        self.board[self.snake.positions[0][0], self.snake.positions[0][1]] = Services.s_symbol_head
    
    def move(self, dir:int, n:int):
        match dir:
            case 0:
                self.snake.move(n)
                if self.snake.check_collision():
                    raise ValueError
            case 1:
                self.snake.move_up()
                if self.snake.check_collision():
                    raise ValueError
            case 2:
                self.snake.move_right()
                if self.snake.check_collision():
                    raise ValueError
            case 3:
                self.snake.move_down()
                if self.snake.check_collision():
                    raise ValueError
            case 4:
                self.snake.move_left()
                if self.snake.check_collision():
                    raise ValueError
        
        self.verify_apple_collision()
        
        self.mark_board()

    def verify_apple_collision(self):
        for pos in self.apples[:]:
            if pos[0] == self.snake.positions[0][0] and pos[1] == self.snake.positions[0][1]:
                self.apples.remove(pos)
                self.snake.grow()

                appleX, appleY = self.apple.generate_new_position()
                while not self.verify_valid_apple(appleX, appleY):
                    appleX, appleY = self.apple.generate_new_position()
                
                self.apples.append([appleX, appleY])
                break
