from board import Board
import random

class Order:

    directions = [(-1, 0), (-1, 1), (0, 1), (1, 1), (1, 0), (1, -1), (0, -1), (-1, -1)]
    def __init__(self, board:Board):
        self.board = board
    
    def make_move(self, position:tuple, symbol:str):

        if symbol not in ["X", "O"]:
            raise ValueError("Invalid symbol.")
        
        if position in self.board.occupied_cells:
            raise ValueError("That cell is already occupied.")

        self.board[position[0], position[1]] = symbol

        if self.check_win(position):
            raise ValueError("Order won!")

        if self.board.free_space == 0:
            raise ValueError("Chaos won!")
    
    def check_win(self, position:tuple):
        for position in self.board.occupied_cells:
            valid_directions = []

            for direction in Order.directions:
                if position[0] + 4 * direction[0] > 0 and position[0] + 4 * direction[0] <= self.board.board_size and position[1] + 4 * direction[1] > 0 and position[1] + 4 * direction[1] <= self.board.board_size:
                    valid_directions.append(direction)

            symbol = self.board[position[0], position[1]]
            for direction in valid_directions: 
                if self.board[position[0] + direction[0], position[1] + direction[1]] == symbol and self.board[position[0] + 2 * direction[0], position[1] + 2 * direction[1]] == symbol and self.board[position[0] + 3 * direction[0], position[1] + 3 * direction[1]] == symbol and self.board[position[0] + 4 * direction[0], position[1] + 4 * direction[1]] == symbol:
                    return True
        
        return False


class Chaos:
    directions = [(-1, 0), (-1, 1), (0, 1), (1, 1), (1, 0), (1, -1), (0, -1), (-1, -1)]
    def __init__(self, board:Board):
        self.board = board
    
    def make_move(self):
        move = self.block_move()
        if move == -1:
            posX = random.randint(1, self.board.board_size)
            posY = random.randint(1, self.board.board_size)

            while (posX, posY) in self.board.occupied_cells:
                posX = random.randint(1, self.board.board_size)
                posY = random.randint(1, self.board.board_size)
            
            self.board[posX, posY] = random.choice(["X", "O"])
        else:
            posX = move[0][0]
            posY = move[0][1]
            symbol = "X" if move[1] == "O" else "O"

            self.board[posX, posY] = symbol
        
        if self.board.free_space == 0:
            raise ValueError("Chaos won!")

    def block_move(self):
        for position in self.board.occupied_cells:
            valid_directions = []
            for direction in Order.directions:
                if position[0] + 4 * direction[0] > 0 and position[0] + 4 * direction[0] <= self.board.board_size and position[1] + 4 * direction[1] > 0 and position[1] + 4 * direction[1] <= self.board.board_size:
                    valid_directions.append(direction)

            symbol = self.board[position[0], position[1]]
            for direction in valid_directions: 
                if self.board[position[0] + direction[0], position[1] + direction[1]] == symbol and self.board[position[0] + 2 * direction[0], position[1] + 2 * direction[1]] == symbol and self.board[position[0] + 3 * direction[0], position[1] + 3 * direction[1]] == symbol and self.board[position[0] + 4 * direction[0], position[1] + 4 * direction[1]] == ' ':
                    return ((position[0] + 4 * direction[0], position[1] + 4 * direction[1]), symbol)
        
        return -1

# board = Board(6)
# order = Order(board)
# chaos = Chaos(board)

# order.make_move((5, 2), 'X')
# order.make_move((5, 3), 'X')
# order.make_move((5, 4), 'X')
# order.make_move((5, 5), 'X')
# chaos.make_move()
# print(board)