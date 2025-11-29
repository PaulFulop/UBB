import sys, unittest
sys.path.append("./src")

from domain.board import Board
from services.ai_player import AIPlayerService, StupidAIPlayer, NormalAIPlayer, SmartAIPlayer
from services.human_player import HumanPlayerService
from services.moves import MoveService
from services.state import BoardStateService
from services.score import ScoreService
from services.game_init import GameInit
from services.game_init import Players

class TestServices(unittest.TestCase):
    def test_game_init(self):
        game = GameInit(Players.AI_PLAYER, 1)
        self.assertEqual(game.flag, True)

        game = GameInit(Players.HUMAN_PLAYER, 1)
        self.assertEqual(game.flag, False)
        
        game.board[0, 0] = 'X'
        game.clear_board()
        self.assertEqual(len(game.board.free_cells), 36)
    
    def test_moves_service(self):
        board = Board()
        moves = MoveService(board)

        moves.cells_to_mark(1, 1, 0, [])
        self.assertEqual(moves.history[-1], [(1, 1), (0, 0), (0, 1), (0, 2), (1, 2), (2, 2), (2, 1), (1, 0), (2, 0)])

        moves.undo()
        self.assertTrue(len(moves.history) == 0)

        moves.mark(1, 1, 'X')
        self.assertEqual(len(board.free_cells), 27)
        moves.mark(5, 5, 'O')
        self.assertEqual(len(board.free_cells), 23)
        moves.undo()
        self.assertEqual(len(board.free_cells), 27)
        moves.undo()
        self.assertEqual(len(board.free_cells), 36)

        try:
            moves.mark(5, 6, 'X')
        except Exception as e:
            self.assertEqual(str(e), "Out of board.")

        try:
            moves.mark(1, 1, 'X')
            moves.mark(1, 1, 'O')
        except Exception as e:
            self.assertEqual(str(e), "The cell at row 1 and column 1 is already occupied.")
    
    def test_ai_service(self):
        board = Board()
        moves = MoveService(board)
        
        ai = AIPlayerService(moves, 'X', 1)
        self.assertIsInstance(ai.computer, StupidAIPlayer)
        ai.make_move()
        self.assertNotEqual(len(board.free_cells), 36)

        board = Board()
        moves = MoveService(board)

        ai = AIPlayerService(moves, 'X', 2)
        ai.make_move()
        self.assertIsInstance(ai.computer, NormalAIPlayer)
        self.assertEqual(len(board.free_cells), 27)

        board = Board()
        moves = MoveService(board)

        ai = AIPlayerService(moves, 'X', 3)
        ai.make_move()
        self.assertIsInstance(ai.computer, SmartAIPlayer)
        self.assertEqual(len(board.free_cells), 27)

        ai = AIPlayerService(moves, 'X', -21947)
        self.assertIsInstance(ai.computer, SmartAIPlayer)
    
    def test_human_service(self):
        board = Board()
        moves = MoveService(board)
        human = HumanPlayerService(moves, 'X')

        human.make_move(1, 1)
        self.assertEqual(board[1, 1], 'X')
        self.assertEqual(len(board.free_cells), 27)
    
    def test_state_service(self):
        board = Board()
        board.free_cells.clear()
        state = BoardStateService("src/test/mock_file1.txt")

        try:
            state.record_state(board, False)
        except Exception as e:
            self.assertEqual(str(e), "You won!")

        try:
            state.record_state(board, True)
        except Exception as e:
            self.assertEqual(str(e), "The computer won!")
    
    def test_score_service(self):
        with open("src/test/mock_file2.txt", "w") as file:
            file.write("0 0")

        score = ScoreService("src/test/mock_file2.txt")
        self.assertEqual(score.list_score(), [0, 0])

        score.update_score(False)
        self.assertEqual(score.list_score(), [1, 0])

        score.update_score(True)
        self.assertEqual(score.list_score(), [1, 1])

if __name__ == '__main__':
    unittest.main()