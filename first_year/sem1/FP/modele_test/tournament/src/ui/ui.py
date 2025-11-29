import sys
sys.path.append("./src")

from domain.player import Player
from services.tournament_services import TournamentServices

class UI:
    def __init__(self):
        self.__serv = TournamentServices()
    
    def display_all_players(self):
        players = self.__serv.list_players()
        text = ""
        for player in players:
            text += str(player) + '\n'
        print(text)
    
    @staticmethod
    def display_commands():
        print("Welcome to the tournament!\n"
              "Avaliable commnds:\n"
              "1 -> display all players\n"
              "2 -> start tournament\n"
              "3 -> exit tournament\n\n")
    
    def run(self):
        UI.display_commands()

        while True:
            cmd = input("> ")
            match cmd:
                case '1':
                    self.display_all_players()
                case '2':
                    self.tournament()
                case '3':
                    print("Exiting...\n")
                    return
                case _:
                    print("Invalid command!\n")
    
    def tournament(self):
        players = self.__serv.list_players()[:]

        if self.__serv.verify_qualif(players):
            print("Qualifying round\n\n")
            com_players_num = self.__serv.verify_qualif(players)
            competing_players = players[:2 * com_players_num]
            pairs = self.__serv.pair_players(competing_players)

            for i in range(com_players_num):
                print(f"Qualification round: {i + 1}\n"
                      f"{pairs[i][0].name} vs {pairs[i][1].name}\n")

                choice = ""
                while choice not in ["1", "2"]:
                    choice = input("Choose which one to win (1 or 2): ")
                    if choice == '1':
                        self.__serv.update_player_strength(pairs[i][0].id)
                        players.remove(pairs[i][1])
                    elif choice == '2':
                        self.__serv.update_player_strength(pairs[i][1].id)
                        players.remove(pairs[i][0])
                    else:
                        print("invalid\n")
        

        print("\nFinals: \n\n")
        while len(players) != 1:
            print(f"Last {len(players)}:\n")

            pairs = self.__serv.pair_players(players)
            for i in range(len(pairs)):
                print(f"Round {i + 1}:")
                print(f"{pairs[i][0].name} vs {pairs[i][1].name}\n")

                choice = ""
                while choice not in ["1", "2"]:
                    choice = input("Choose which one to win (1 or 2): ")
                    if choice == '1':
                        self.__serv.update_player_strength(pairs[i][0].id)
                        players.remove(pairs[i][1])
                    elif choice == '2':
                        self.__serv.update_player_strength(pairs[i][1].id)
                        players.remove(pairs[i][0])
                    else:
                        print("invalid\n")
        
        print(f"The winner is {players[0].name}!!\n")