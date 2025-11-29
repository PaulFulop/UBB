import sys, random
sys.path.append("./src")

from domain.player import Player
from repo.player_repo import PlayerRepo

class TournamentServices:
    def __init__(self):
        self.__repo = PlayerRepo()
    
    def list_players(self):
        players = self.__repo.list_players()[:]

        for i in range(len(players) - 1):
            for j in range(i + 1, len(players)):
                if players[i].strength < players[j].strength:
                    players[i], players[j] = players[j], players[i]

        return players
    
    @staticmethod
    def verify_qualif(players:list):
        pow = 1
        num_players = len(players)
        while pow < num_players:
            pow *= 2
        pow //= 2
        return num_players - pow
    
    @staticmethod
    def pair_players(rem_players:list):
        """Generates random pairing for all remaining players

        :param rem_players: The players remaining in the tournament
        :type rem_players: list
        :return: list of pairs of players
        :rtype: list
        """
        pairs = []
        players = rem_players[:]
        num_players = len(players)

        while num_players:
            p1 = random.choice(players)
            players.remove(p1)
            p2 = random.choice(players)
            players.remove(p2)
            pairs.append((p1, p2))

            num_players -= 2

        return pairs
    
    def update_player_strength(self, id:int):
        self.__repo.update_strength(id)
