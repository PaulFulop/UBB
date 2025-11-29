from texttable import Texttable

class Board(Texttable):
    def __init__(self, size:int):
        super().__init__()
        self.board_size = size
        self.free_space = size ** 2
        self.occupied_cells = []
        self.build_table()

    def __getitem__(self, index:tuple):
        if index[0] <= 0 or index[1] <= 0 or index[1] > self.board_size or index[0] > self.board_size:
            raise ValueError("Invalid position.")

        return self._rows[index[0] - 1][index[1] - 1]
    
    def __setitem__(self, key:tuple, value:str):
        if key[0] <= 0 or key[1] <= 0 or key[1] > self.board_size or key[0] > self.board_size:
            raise ValueError("Invalid position.")
        
        self._rows[key[0] - 1][key[1] - 1] = value
        self.occupied_cells.append((key[0], key[1]))
        self.free_space -= 1
    
    def __str__(self):
        return self.draw()

    def build_table(self):
        for _ in range(self.board_size):
            self.add_row([" " for i in range(self.board_size)])