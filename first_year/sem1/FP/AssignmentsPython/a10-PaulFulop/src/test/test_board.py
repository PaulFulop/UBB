import sys, unittest
sys.path.append("./src")

from domain.board import Board

class TestBoard(unittest.TestCase):
    def test_board(self):
        board = Board()
        self.assertEqual(len(board.free_cells), 36, "The free_cells property doesn't work as expected.")

        board[0, 0] = 'X'
        self.assertEqual(len(board.free_cells), 35, "The free_cells property doesn't work as expected.")
        self.assertEqual(board[0, 0], 'X', "The board doesnt work properly.")

        board[0, 0] = ' '
        self.assertEqual(len(board.free_cells), 36, "The free_cells property doesn't work as expected.")

        symmetric_positions = board.filter_symmetric_positions()
        self.assertLess(len(symmetric_positions), len(board.free_cells), "The symmetric postions are not filtered properly.")


if __name__ == '__main__':
    unittest.main()