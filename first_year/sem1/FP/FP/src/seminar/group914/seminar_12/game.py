from random import randint

from seminar.group914.seminar_12.board import ComputerBoard, PlayerBoard, ShipDirection


# NOTE We implement the Strategy design pattern for the computer's choices
# https://refactoring.guru/design-patterns/strategy
# The idea is to put the algorithm(s) in their own class
# We instantiate the class that corresponds to the algorithm we want
# ex: easy difficulty -> random moves from computer
# ex: hard difficulty -> once a hit is recorded, the computer bombs the area :)
class ComputerStrategy:
    def __init__(self, computer_board: ComputerBoard, player_board: PlayerBoard):
        self.__computer_board = computer_board
        self.__player_board = player_board

        # NOTE the computer can already place its ships at this point
        self.place_ships()

    def place_ships(self):
        """
        Computer's strategy for placing ships on its own board
        """
        # TODO Randomize me
        self.__computer_board.place_ship(1, 1, ShipDirection.RIGHT)
        self.__computer_board.place_ship(2, 3, ShipDirection.RIGHT)

    def fire(self):
        """
        Computer's strategy to fire
        """
        # TODO Implement something better here
        row = randint(0, 5)
        column = randint(0, 5)
        self.__player_board.fire(row, column)


class Battleships:
    def __init__(self):
        self.__computer_board = ComputerBoard()
        self.__player_board = PlayerBoard()
        # TODO Read the difficulty level (computer strategy) from a settings file
        self.__strategy = ComputerStrategy(self.__computer_board, self.__player_board)

    @property
    def computer_board(self):
        return self.__computer_board

    @property
    def player_board(self):
        return self.__player_board

    def fire_human_player(self, row: int, column: int):
        self.__computer_board.fire(row, column)

    def fire_computer_player(self):
        # NOTE This method does not need to know about the computer's actual strategy
        # NOTE Return the fired coordinates so we know what the computer did
        self.__strategy.fire()
