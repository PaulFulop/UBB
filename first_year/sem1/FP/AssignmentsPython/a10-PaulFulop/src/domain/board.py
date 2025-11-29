#Board for the game

from texttable import Texttable

"""A 6 x 6 texttable with some additional features that works as a printable grid.
    :raises IndexError: if the row index is out of the predefined range (e.g. custom_tt[7, 1] will not work)
    :raises IndexError: if the column index is out of the predefined range (e.g. custom_tt[1, 7] will not work)
    :raises IndexError: if the index format is not supported (e.g. custom_tt[1][1], custom_tt[2], custom_tt[sanf, -2] or anything else will not work)
    :return: A CustomTextTable object.
    :rtype: CustomTextTable
    """
class CustomTextTable(Texttable):
    """The class constructor

    :param Texttable: The parent class
    :type Texttable: texttable object
    """
    def __init__(self):
        super().__init__()
    
    """Saying print(custom_tt) will automatically convert the grid/table to str
    """
    def __str__(self):
        return self.draw()

    """Allows one to say custom_tt[row, col] and get its str value
    """
    def __getitem__(self, index):
        if isinstance(index, tuple) and len(index) == 2:
            row, column = index
            if row < 0 or row > 5:
                raise IndexError("Row index out of range.")

            if column < 0 or column > 5:
                raise IndexError("Column index out of range.")
            
            return self._rows[row][column]
        else:
            raise IndexError("Invalid index format.")

    """Allows one to say custom_tt[row, col] = value
    """
    def __setitem__(self, index, value):
        if isinstance(index, tuple) and len(index) == 2:
            row, column = index
            if row < 0 or row > 5:
                raise IndexError("Row index out of range.")

            if column < 0 or column > 5:
                raise IndexError("Column index out of range.")
            
            self._rows[row][column] = str(value)
        else:
            raise IndexError("Invalid index format.")

class Board:
    BORDER_COLOR = (32, 34, 36)
    LIGHT_GREY = (212, 210, 217)
    BLUE = (60, 133, 181)
    RED = (186, 17, 17)

    """Class constructor that initializes the 6x6 board for playing obstruction
    """
    def __init__(self):
        self.__board = CustomTextTable()
        rows = [[' ' for _ in range(6)] for _ in range(6)]
        self.__board.add_rows(rows, header=False)
        self.__free_cells = [(i, j) for i in range(6) for j in range(6)] 
    
    """Saying print(board) will show the board on the console with different colors.
    """
    def __str__(self):
        brown = f"\x1b[38;2;{99};{70};{43}m"
        blue = f"\x1b[38;2;{60};{133};{181}m"
        red = f"\x1b[38;2;{186};{17};{17}m"
        grey = f"\x1b[38;2;{212};{210};{217}m"
        reset_color = "\x1b[0m"
        raw_board = self.__board.draw().replace('+', f"{brown}+{reset_color}").replace('-', f"{brown}-{reset_color}").replace('|', f"{brown}|{reset_color}")
        return raw_board.replace('X', f"{blue}X{reset_color}").replace('O', f"{red}O{reset_color}").replace('*', f"{grey}*{reset_color}")

    """Allows one to say board[row, col] and get its str value (X, O, *, ' ')
    """
    def __getitem__(self, index):
        return self.__board.__getitem__(index)
    
    """Allows one to say board[row, col] = value
    """
    def __setitem__(self, index, value):
        self.__board.__setitem__(index, value)

        if value == ' ' and index not in self.__free_cells:
            self.__free_cells.append(index)
        elif value != ' ' and index in self.__free_cells:
            self.__free_cells.remove(index)
        
    def filter_symmetric_positions(self):
        """Only works well for the empty board -> used for optimization on the minimax algorithm by reducing the number of moves to verify

        :return: list of the only relevant positions (e.g. board[1, 1] and board[4, 4] are symmetric, hence only board[1, 1] will appear in the list)
        :rtype: list
        """
        positions = self.free_cells[:]

        for position in positions:
            x, y = position
            
            if (y, 5 - x) in positions:
                positions.remove((y, 5 - x))

            if (5 - x, 5 - y) in positions:
                positions.remove((5 - x, 5 - y))
            
            if (5 - y, x) in positions:
                positions.remove((5 - y, x))
        
        return positions
    
    @property
    def free_cells(self):
        return self.__free_cells