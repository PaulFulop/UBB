from seminar.group914.seminar_12.board import ShipDirection
from seminar.group914.seminar_12.game import Battleships


class UI:
    def __init__(self):
        self.__game = Battleships()

    def __place_player_ships(self):
        # TODO Remove hard coding
        self.__game.player_board.place_ship(0, 0, ShipDirection.DOWN)
        self.__game.player_board.place_ship(5, 5, ShipDirection.LEFT)

    def start(self):
        self.__place_player_ships()

        while True:
            print("My board")
            print(self.__game.player_board)
            print("Targeting board")
            print(self.__game.computer_board)
            fire_coordinates = input("fire>").strip()

            # TODO Checks here ...
            column = ord(fire_coordinates[0].upper()) - ord('A')  # 'B' - 'A' means column index 1
            row = int(fire_coordinates[1]) - 1

            self.__game.fire_human_player(row, column)
            self.__game.fire_computer_player()

ui = UI()
ui.start()
