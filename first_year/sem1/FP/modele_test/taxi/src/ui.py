from address_services import AddressServices
from address import Address

class UI:
    def __init__(self):
        self.__serv = AddressServices()
    
    @staticmethod
    def display_commands():
        print("List of commands:\n"
              "1 -> add a new station\n"
              "2 -> display all registered stations\n"
              "3 -> find all addresses that have at most a certain distance from a point\n"
              "4 -> determine the best coordinates for a new taxi station\n"
              "5 -> exit\n\n")

    def run(self):
        UI.display_commands()

        while True:
            cmd = input("> ")

            match cmd:
                case '1':
                    id = input("Insert the id here: ")
                    name = input("Insert the street name here: ")
                    number = input("Insert the street number here: ")
                    x = input("Insert the x cord. here: ")
                    y = input("Insert the y cord. here: ")

                    try:
                        new_address = Address(int(id), name, int(number), int(x), int(y))
                        self.__serv.add(new_address)
                        print("A new taxi station was added.")
                    except Exception as e:
                        print(str(e) + '\n')
                case '2':
                    print(self.__serv.list_addresses())
                case '3':
                    posX = input("Insert the x cord. of the searching position here: ")
                    posY = input("Insert the y cord. of the searching position here: ")
                    dist = input("Inert the max. distance here: ")

                    try:
                        data = self.__serv.find_addresses(int(posX), int(posY), int(dist))
                        if len(data) == 0:
                            print("No such addresses were found.\n")
                        else:
                            for d in data:
                                print(f"Address: {d[0]}. Distance: {d[1]}.")
                            print('\n')
                    except Exception as e:
                        print(str(e) + '\n')
                case '4':
                    bestX, bestY = self.__serv.find_best_new_location()
                    if bestX == -101 or bestY == -101:
                        print("No place for a new station.")
                    else:
                        print(f"A new station with minimal total distance could be made at {bestX}, {bestY}.")
                case '5':
                    print("Exiting...\n")
                    return
                case _:
                    print("Invalid command")