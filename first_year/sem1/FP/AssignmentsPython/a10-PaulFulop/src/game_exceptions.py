# Custom game exceptions

"""Parent class for all the custom game exceptions/errors
"""
class GameException(Exception):
    pass

class OutOfBoardError(GameException):
    """This exception occurs when a player is trying to make a move outside the board.

    :param GameException: Parent class
    :type GameException: GameException
    """
    def __init__(self):
        super().__init__("Out of board.")

class OccpiedCellError(GameException):
    """This exception occurs when a player is trying to make a move on a cell that is already occupied/obstructed.

    :param GameException: Parent class
    :type GameException: GameException
    """
    def __init__(self, x:int, y:int):
        super().__init__(f"The cell at row {x} and column {y} is already occupied.")

class GameOverError(GameException):
    """This exception occurs when a player won and plotting more moves on the board would be impossible.

    :param GameException: Parent class
    :type GameException: GameException
    """
    def __init__(self, current_player:str):
        super().__init__(f"{current_player} won!")

class PropertiesError(GameException):
    """This exception occurs when the properties in the settings.properties file are invalid or missing

    :param GameException: Parent class
    :type GameException: GameException
    """
    def __init__(self):
        super().__init__("The settings.properties file has incomplete/invalid information about the game properties or it doesn't exist.")