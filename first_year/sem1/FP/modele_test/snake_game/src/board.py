from texttable import Texttable

class Board(Texttable):
    def __init__(self, size:int):
        super().__init__()
        self.size = size
        self.__generate_board()
    
    def __generate_board(self):
        row_content = [' ' for _ in range(self.size)]

        for _ in range(self.size):
            self.add_row(row_content)
    
    def __setitem__(self, index:tuple, value:str):
        if index[0] < 0 or index[0] > self.size or index[1] < 0 or index[1] > self.size:
            raise IndexError
        
        self._rows[index[0]][index[1]] = value

    def __getitem__(self, index:tuple):
        if index[0] < 0 or index[0] > self.size or index[1] < 0 or index[1] > self.size:
            raise IndexError
        
        return self._rows[index[0]][index[1]]

    def __str__(self):
        return self.draw()