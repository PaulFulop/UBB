#Service for the computer moves (how should the AI play)

import sys, random
sys.path.append("./src")
from services.moves import MoveService

class AIPlayerService:
    def __init__(self, moves_service:MoveService, symbol:str, difficulty:int):
        """Class constructor.Initializes the computer player based on the desired difficulty

        :param moves_service: Used to mark the computer's moves on the board
        :type moves_service: MoveService
        :param symbol: The symbol that the computer will play with (X or O)
        :type symbol: str
        :param difficulty: Describes how smart the computer should play (0 -> stupid, 1 -> normal or equally good to a human, 2 -> smart)
        :type difficulty: int
        """
        match difficulty:
            case 1:
                self.__ai = StupidAIPlayer(moves_service, symbol)
            case 2:
                self.__ai = NormalAIPlayer(moves_service, symbol)
            case _:
                self.__ai = SmartAIPlayer(moves_service, symbol)
    
    def make_move(self):
        """Makes a move on the board
        """
        self.computer.make_move()
    
    @property
    def computer(self):
        return self.__ai

class StupidAIPlayer:
    def __init__(self, moves_service:MoveService, symbol:str):
        """Class constructor. Initializes the StupidAIPlayer object

        :param moves_service: Used to mark the computer's moves on the board
        :type moves_service: MoveService
        :param symbol: The symbol that the computer will play with (X or O)
        :type symbol: str
        """
        self._moves_service = moves_service
        self._symbol = symbol
    
    def make_move(self):
        """Make a valid random move on the board.
        """
        x = random.randint(0, 5)
        y = random.randint(0, 5)

        while(self._moves_service.board[x, y] != ' '):
            x = random.randint(0, 5)
            y = random.randint(0, 5)
        
        self._moves_service.mark(x, y, self._symbol)
        

class SmartAIPlayer(StupidAIPlayer):

    __weight = [[0.1, 0.2, 0.2, 0.2, 0.2, 0.1], [0.2, 0.4, 0.4, 0.4, 0.4, 0.2], [0.2, 0.4, 0.7, 0.7, 0.4, 0.2],
               [0.2, 0.4, 0.7, 0.7, 0.4, 0.2], [0.2, 0.4, 0.4, 0.4, 0.4, 0.2], [0.1, 0.2, 0.2, 0.2, 0.2, 0.1]]
    def __init__(self, moves_service:MoveService, symbol:str):
        """Class constructor. Initializes the SmartAIPlayer object.

        :param moves_service: Used to mark the computer's moves on the board
        :type moves_service: MoveService
        :param symbol: The symbol that the computer will play with (X or O)
        :type symbol: str
        """
        super().__init__(moves_service, symbol)

    def make_move(self):
        """Given a board state, the function will find the best move by iterating through all the free cells of the board,
        temporarily marking them and then applying the minimax algorithm, which will return a numerical value that basically
        describes how good the current move was. Finding the best move involves finding the maximum / minimimum
        (depends wether the compter is the first one to play or not) value that the minimax algorithm will return.
            In addition to this, the value that minimax returns will be slightly adjusted based on the weight of the
        current marked cell (cells in the corner have smaller weights compared to those in the center,
        because intuitively speaking, a move closer to the center is better since it will occupy more cells)
        and on the amount of cells occupied (a move that restricts the opponent's valid moves as much as possible is better).
        """
        best_eval = int(-1e9) if self._symbol == 'O' else int(1e9)
        best_move = None
        is_maximizing = (self._symbol == 'O') # True if we are the max player, False otherwise
        sign = 1 if is_maximizing else -1
        candidate_cells = self._get_best_candidate_cells() if len(self._moves_service.board.free_cells) == 36 else self._moves_service.board.free_cells[:]

        for x, y in candidate_cells:
            self._moves_service.mark(x, y, self._symbol)
            eval = self._minimax(not is_maximizing, int(-1e9), int(1e9)) + sign * ((36 - len(self._moves_service.board.free_cells)) + SmartAIPlayer.__weight[x][y])
            self._moves_service.undo()

            if (is_maximizing and eval > best_eval) or (not is_maximizing and eval < best_eval):
                best_eval = eval
                best_move = (x, y)
        
        self._moves_service.mark(best_move[0], best_move[1], self._symbol)

    def _minimax(self, max_player:bool, alpha:int, beta:int):
        """Algorithm that evaluates the state of the board and returns a numerical value
          based on wether the position is winning or losing for the  maximizing/minimizing player.
          In addition, alpha-beta pruning is used as an optimization technique that reduces the amount of time
          needed to evaluate all the possible moves by cutting off "branches" that are never going to be
          taken into consideration by the algorithm anyway (basically bad moves).

        :param max_player: mainly used to alternate between players
        :type max_player: bool
        :param alpha: used for the alpha-beta prunning (initially alpha should be a very big value)
        :type alpha: int
        :param beta: used for alpha-beta prunning (intially beta should be a very small value)
        :type beta: int
        :return: a numerical value describing how good a state of the board is for the maximizing/minimizing player
                 (depending on the max_player prameter)
        :rtype: int
        """
        if self._terminal_state() == True:
            return self._static_eval_function(max_player)
        
        candidate_cells = self._moves_service.board.free_cells[:]
        
        if max_player == True:
            max_eval = int(-1e9)
            for x, y in candidate_cells:
                self._moves_service.mark(x, y, 'O')
                eval = self._minimax(False, alpha, beta)
                max_eval = max(max_eval, eval)

                alpha =  max(max_eval, eval)
                if alpha >= beta:
                    self._moves_service.undo() 
                    break

                self._moves_service.undo() 
            return max_eval
        else:
            min_eval = int(1e9)
            for x, y in candidate_cells:
                self._moves_service.mark(x, y, 'X')
                eval = self._minimax(True, alpha, beta)
                min_eval = min(min_eval, eval)

                beta = min(min_eval, eval)
                if alpha >= beta:
                    self._moves_service.undo()
                    break

                self._moves_service.undo()
            return min_eval
        
    def _terminal_state(self):
        """Checks if the board is full and no moves can be made anymore.

        :return: True if the board is full, False otherwise
        :rtype: bool
        """
        return len(self._moves_service.board.free_cells) == 0

    def _static_eval_function(self, max_player:bool):
        """Evaluates the state of the board by returning a big number (1000) if the first player is winning,
          or by returning a very small number (-1000) if the second player is winning.

        :param max_player: Used to determine wether the last player that made a move was the first player (maximizing player),
                            or the second one (minimzing player)
        :type max_player: bool
        :return: 1000 if the maximizing player made the last move, -1000 otherwise
        :rtype: int
        """
        return 1000 if not max_player == True else -1000
    
    def _get_best_candidate_cells(self):
        """ If the computer is the first to play, it will have to go through the whole board and analyze every move possible,
            which is very time consuming.This funtion will reduce the number of moves the computer has to analyze by removing:
                1 -> all the cells that are symmetric (e.g. cell[1, 1] is symmetric to cell[1, 4], cell[4, 1] and cell[4, 4])
                     because especially when dealing with an empty board, making a move on multiple symmetric cells will result in
                     same outcome overall
                2 -> all the cells that are in the corner or on a margin (e.g. cell[0, 1], cell[5, 5] etc) because especially
                     in the beginning, occupying as much space as possible is crucial and playing in the corner or on a margin 
                     will drastically decrease the possibility of winning.

        :return: list of the best cells (tuples of positions on the board) to mark on an empty board
        :rtype: list
        """
        candidate_cells = self._moves_service.board.filter_symmetric_positions()[:]
        for x, y in candidate_cells[:]:
            if x == 0 or x == 5 or y == 0 or y == 5:
                candidate_cells.remove((x, y))
        return candidate_cells

class NormalAIPlayer(SmartAIPlayer):
    def __init__(self, moves_service:MoveService, symbol:str):
        """Class constructor. Initializes the NormalAIPlayer object.

        :param moves_service: Used to mark the computer's moves on the board
        :type moves_service: MoveService
        :param symbol: The symbol that the computer will play with (X or O)
        :type symbol: str
        """
        super().__init__(moves_service, symbol)
    
    def make_move(self):
        """Function derived from SmartAIPlayer. It has the same purpose, except that this function
          will potentially use the first move that is winning for the computer, if it exists. It doesn't check if it's a
          winning move that also occupies as much space as possible, nor if it's as close as possible to the center.
        """
        best_eval = int(-1e9) if self._symbol == 'O' else int(1e9)
        best_move = None
        is_maximizing = (self._symbol == 'O') # True if we are the max player, False otherwise
        candidate_cells = self._get_best_candidate_cells() if len(self._moves_service.board.free_cells) == 36 else self._moves_service.board.free_cells[:]

        for x, y in candidate_cells:
            self._moves_service.mark(x, y, self._symbol)
            eval = self._minimax(not is_maximizing, int(-1e9), int(1e9))
            self._moves_service.undo()

            if (is_maximizing and eval > best_eval) or (not is_maximizing and eval < best_eval):
                best_eval = eval
                best_move = (x, y)
        
        self._moves_service.mark(best_move[0], best_move[1], self._symbol)