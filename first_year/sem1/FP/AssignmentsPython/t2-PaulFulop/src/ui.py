from domain import Adress
from services import Services


class UI:
    def __init__(self):
        self.__serv = Services()
    
    @staticmethod
    def display_commands():
        print("List of commands:\n\n"
              "1 -> add an address\n"
              "2 -> determine aaddresses that have at most a desired distance from a desired point\n"
              "3 -> determine a optimal position for a new station\n"
              "4 -> exit\n\n")
    
    def run(self):
        UI.display_commands()
        while True:
            cmd = input("> ")

            match cmd:
                case '1':
                    try:
                        id = input("Insert the id here: ")
                        name = input("Insert the name here: ")
                        number = input("Insert the street number here: ")
                        x = input("Insert the x position here: ")
                        y = input("Insert the y position here: ")

                        self.__serv.add_adress(Adress(int(id), name, number, int(x), int(y)))
                        print("New address added successfully.\n")
                    except Exception as e:
                        print(str(e) + '\n')
                case '2':
                    try:
                        posX = input("Insert the desired x position here: ")
                        posY = input("Insert the desired y position here: ")
                        dist = input("Insert the desired distance here: ")

                        data = self.__serv.determine_addresses(int(posX), int(posY), int(dist))
                        print('\n')
                        text = ""
                        for d in data:
                            text += f"Address: {str(d[0])}. Distance: {d[1]}.\n"
                        print(text)
                    except Exception as e:
                        print(str(e) + '\n')
                case '3':
                    bestX, bestY = self.__serv.determine_new_station()
                    print(f"The best position for a new station is {bestX, bestY}\n")
                case '4':
                    print("Exiting...\n")
                    return
                case _:
                    print("Invalid command.\n")