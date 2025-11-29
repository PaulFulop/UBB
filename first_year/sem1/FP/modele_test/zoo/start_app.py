from ui import menu

def start_app():
    animals = [["1234", "alex", "carnivore", "lion"],
            ["z02", "julia", "herbivore", "zebra"],
                ["1j23", "rex", "carnivore", "tiger"],
                ["12bj", "olly", "herbivore", "koala"],
                    ["asj2", "mike", "carnivore", "lion"]]

    menu(animals)

if __name__ == "__main__":
    start_app()