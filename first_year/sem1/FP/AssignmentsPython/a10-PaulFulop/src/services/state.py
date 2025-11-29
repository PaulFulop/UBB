# Check for win conditions.

import sys
sys.path.append("./src")
from domain.board import Board
from game_exceptions import GameOverError
from services.score import ScoreService

class BoardStateService:
    def __init__(self, file_path:str):
        """Class constructor. Initializes a score service that loads data from the file_path parameter

        :param file_path: path to the desired file
        :type file_path: str
        """
        self.__score_serv = ScoreService(file_path)

    def record_state(self, board:Board, flag:bool):
        """Records the state of the board (wether the board is full or not). 

        :param board: the board for which to record the state
        :type board: Board
        :param flag: used to determine which player (human or computer) made the last move on the board 
                    (False -> human player, True -> computer player)
        :type flag: bool
        :raises GameOverError: if the board is full, meaining the player who made the last move won
        """
        if len(board.free_cells) == 0:
            current_player = "You" if not flag else "The computer" 
            self.__score_serv.update_score(flag)
            raise GameOverError(current_player)
    
    @property
    def score_serv(self):
        return self.__score_serv