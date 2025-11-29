import sys
sys.path.append("./src")

from domain.player import Player

class PlayerRepo:
    def __init__(self):
        self.__data = []
        self.__load()

    def list_players(self):
        return self.__data

    def update_strength(self, id:int):
        for player in self.__data:
            if player.id == id:
                player.strength += 1
                self.__save()
                break

    def __load(self):
        with open("src/repo/players.txt", "rt") as file:
            lines = file.readlines()
            for line in lines:
                tokens = line.split(",")
                self.__data.append(Player(int(tokens[0].strip()), tokens[1].strip(), int(tokens[2].strip().removesuffix('\n'))))

    def __save(self):
        with open("src/repo/players.txt", "wt") as file:
            for player in self.__data:
                file.write(str(player) + "\n")