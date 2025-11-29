from enum import Enum

from texttable import Texttable


class ShipDirection(Enum):
    UP = 0
    DOWN = 1
    LEFT = 2
    RIGHT = 3


class BattleshipsBoard:
    # The rules are not tied to any single board, so they don't need the self parameter
    # this is a general placement rule
    # These are class-level variables (similar to static variables in other languages)
    __placement_rules = {ShipDirection.UP: (-1, 0), ShipDirection.DOWN: (1, 0), ShipDirection.LEFT: (0, -1),
                         ShipDirection.RIGHT: (0, 1)}

    __ship_length = 3

    def __init__(self):
        self._data = []
        for i in range(6):
            self._data.append([0] * 6)
        # we represent the next added ship using 1's
        self.__current_ship = 1

    def place_ship(self, row: int, column: int, direction: ShipDirection):
        # TODO Bunch of checks -- ship contained in board, ships don't overlap
        move_x = BattleshipsBoard.__placement_rules[direction][0]
        move_y = BattleshipsBoard.__placement_rules[direction][1]

        current_x = row
        current_y = column

        for cell in range(0, BattleshipsBoard.__ship_length):
            self._data[current_x][current_y] = self.__current_ship
            current_x += move_x
            current_y += move_y

        # move to the next ship index
        self.__current_ship += 1

    def fire(self, row: int, column: int):
        # TODO Checks
        if self._data[row][column] == 0:
            self._data[row][column] = 100
        elif self._data[row][column] > 0:
            self._data[row][column] = -1 * self._data[row][column]
        # TODO Raise an exception if a ship is sunk (UI message to player) or all ships sunk (Game Over)


class PlayerBoard(BattleshipsBoard):
    def __init__(self):
        # must call superclass constructor to initialize board
        super().__init__()

    def __str__(self):
        t = Texttable()
        t.header(['/', 'A', 'B', 'C', 'D', 'E', 'F'])  # easier with ord(), chr()
        # for ascii_code in range(ord('A'),ord('F')+1):
        #     print(chr(ascii_code))

        for row in range(6):
            row_data = [row + 1] + [' '] * 6  # initialize an empty row

            for column in range(6):
                symbol = ' '
                if self._data[row][column] == 100:
                    symbol = '.'
                elif self._data[row][column] > 0:
                    symbol = str(self._data[row][column])
                elif self._data[row][column] < 0:
                    symbol = 'X'
                row_data[column + 1] = symbol
            t.add_row(row_data)
        return t.draw()


class ComputerBoard(BattleshipsBoard):
    def __init__(self):
        # must call superclass constructor to initialize board
        super().__init__()

    def __str__(self):
        t = Texttable()
        t.header(['/', 'A', 'B', 'C', 'D', 'E', 'F'])  # easier with ord(), chr()
        # for ascii_code in range(ord('A'),ord('F')+1):
        #     print(chr(ascii_code))

        for row in range(6):
            row_data = [row + 1] + [' '] * 6  # initialize an empty row

            for column in range(6):
                symbol = ' '
                if self._data[row][column] == 100:
                    symbol = '.'
                elif self._data[row][column] < 0:
                    symbol = 'X'
                row_data[column + 1] = symbol
            t.add_row(row_data)
        return t.draw()


if __name__ == "__main__":
    bb = PlayerBoard()
    print(bb)
    bb.place_ship(1, 1, ShipDirection.DOWN)
    bb.place_ship(1, 2, ShipDirection.RIGHT)
    bb.place_ship(5, 5, ShipDirection.UP)
    bb.fire(2, 1)
    bb.fire(3, 3)
    print(bb)
