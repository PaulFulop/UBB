#Human player service (how should the human move)

import sys
sys.path.append("./src")
from services.moves import MoveService

class HumanPlayerService:
    def __init__(self, moves_service:MoveService, symbol:str):
        """Class constructor. Initializes a move service so that the human knows how to move,
          and the symbol that the human will use when playing

        :param moves_service: Used to update the board when the human makes a move.     
        :type moves_service: MoveService
        :param symbol: The symbol (X or O) that the human will use when playing the game    
        :type symbol: str
        """
        self.__moves_service = moves_service
        self.__symbol = symbol
    
    def make_move(self, x:int, y:int):
        """Marks the cell at row x and column y and all the surrounding cells if possible. 

        :param x: x-coordinate (the row)
        :type x: int
        :param y: y-coordinate (the column)
        :type y: int
        """
        self.__moves_service.mark(x, y, self.__symbol)