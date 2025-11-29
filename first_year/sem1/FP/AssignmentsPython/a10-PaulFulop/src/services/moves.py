# Allowing players to make moves (marking an X or O on the board)

import sys
sys.path.append("./src")
from domain.board import Board
from game_exceptions import OutOfBoardError, OccpiedCellError

class MoveService:
    __directions = [(0, 0), (-1, -1), (-1, 0), (-1, 1), (0, 1), (1, 1), (1, 0), (0, -1), (1, -1)]


    def __init__(self, board:Board):
        """Class constructor. Initializes a board to make moves in, and a history of moves.

        :param board: _description_
        :type board: Board
        """
        self.__board = board
        self.__history = []
    
    def cells_to_mark(self, x:int, y:int, k:int, cells:list):
        """Recursive function that computes the list of positions that have to be marked when a player makes a move on the board.

        :param x: x-coordinate (the row)
        :type x: int
        :param y: y-coordinate (the column)
        :type y: int
        :param k: playing a move on x,y will mark the x,y cell and all the other cells surrounding it;
          because of this (and also because the function is recursive), k is used to iterate through a list of directions
        :type k: int
        :param cells: list of cells ((x, y) -> tuple meaining the cordinates of a cell)  that have to be marked on the board
        :type cells: list
        :raises OutOfBoardError: If a player is trying to play on a cell outside the board (outside range(0,5))
        :raises OccpiedCellError: If a player is trying to play on a cell that has already been marked/obstructed.
        """
        if k > 8:
            self.__history.append(cells[:])
            return

        if x + MoveService.__directions[k][0] < 0 or x + MoveService.__directions[k][0] > 5 or y + MoveService.__directions[k][1] < 0 or y + MoveService.__directions[k][1] > 5:
            if k:
                self.cells_to_mark(x, y, k + 1, cells)
                return

            raise OutOfBoardError

        if (x + MoveService.__directions[k][0], y + MoveService.__directions[k][1]) not in self.__board.free_cells:
            if k:
                self.cells_to_mark(x, y, k + 1, cells)
                return
            
            raise OccpiedCellError(x, y)

        self.cells_to_mark(x, y, k + 1, cells + [(x + MoveService.__directions[k][0], y + MoveService.__directions[k][1])])

    def mark(self, x:int, y:int, symbol:str):
        """Updates the board by plotting values (symbol, *) on it according to the coordinates (x, y)

        :param x: x-coordinate (the row)
        :type x: int
        :param y: y-coordinate (the column)
        :type y: int
        :param symbol: (X, O) -> the symbol used to play the game       
        :type symbol: str
        """
        self.cells_to_mark(x, y, 0, [])
        row, col = self.__history[-1][0]
        self.__board[row, col] = symbol

        for row, col in self.__history[-1][1:]:
            self.__board[row, col] = '*'
    
    def undo(self):
        """Will undo the last move that was played by one of the players.
        """
        if len(self.__history) > 0:
            for row, col in self.__history[-1]:
                self.__board[row, col] = ' '

            self.__history.pop()

    @property
    def board(self):
        return self.__board

    @property
    def history(self):
        return self.__history