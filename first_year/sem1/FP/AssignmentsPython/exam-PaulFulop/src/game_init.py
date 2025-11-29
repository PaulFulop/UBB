from players import Order, Chaos
from board import Board

class GameInit:
    def __init__(self, size:int):
        self.board = Board(size)
        self.order = Order(self.board)
        self.chaos = Chaos(self.board)
    
    def restart(self):
        for i in range(self.board.board_size):
            for j in range(self.board.board_size):
                self.board[i, j] = ' '
        self.board.occupied_cells.clear()
        self.board.free_space = self.board.board_size ** 2