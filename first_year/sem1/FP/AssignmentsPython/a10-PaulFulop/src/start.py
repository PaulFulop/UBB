# For starting the game and choosing which mode to play on (console or custom window with pygame)

import sys
sys.path.append("./src")
from game_exceptions import PropertiesError
from services.game_init import Players
from interface.ui import UI
from interface.gui import GUI 

def get_properties():
    try:
        with open("src/settings.properties", "rt") as file:
            lines = file.readlines()
            tokens = []
            for line in lines:
                tokens.append(line.split('=')[1].removesuffix('\n').strip().lower())
    except FileNotFoundError:
        raise PropertiesError
    
    if len(lines) == 0:
        raise PropertiesError 

    if tokens[0] not in ['console', 'pygame'] or tokens[1] not in ['human', 'computer']:
        raise PropertiesError 

    try:
        tokens[2] = int(tokens[2])
    except ValueError:
        raise PropertiesError

    tokens[1] = Players.HUMAN_PLAYER if tokens[1] == 'human' else Players.AI_PLAYER
    
    return tokens


def start_game():
    try:
        props = get_properties()
        if props[0] == 'console':
            ui = UI(props[1], props[2])
            ui.run()
        else:
            gui = GUI(props[1], props[2])
            gui.run()
    except PropertiesError:
        ui = UI(Players.HUMAN_PLAYER, 3)
        ui.run()

if __name__ == "__main__":
    start_game()