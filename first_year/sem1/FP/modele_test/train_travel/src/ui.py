from services import Services
from domain import Route

class UI:
    def __init__(self, file_path:str):
        self.__serv = Services(file_path)
    
    @staticmethod
    def display_commands():
        print("1 -> add a new train\n"
              "2 -> buy a ticket\n"
              "3 -> show the total income\n"
              "4 -> show report\n"
              "5 -> exit\n")
    
    def run(self):
        UI.display_commands()

        while True:
            cmd = input("> ")

            match cmd:
                case "1":
                    try:
                        num = int(input("Insert the number of the route here: "))
                        d_city = input("Insert the departure city here: ")
                        t1 = input("Insert the departure time here: ")
                        a_city = input("Insert the arrival city here: ")
                        t2 = input("Insert the arrival time here: ")
                        tickets = int(input("Insert the number of tickets here: "))
                        self.__serv.add_route(Route(num, d_city, t1, a_city, t2, tickets))
                        print("New route added.\n")
                    except Exception as e:
                        print(str(e) + '\n')
                case "2":
                    try:
                        num = int(input("Insert the number of the route here: "))
                        route = self.__serv.find_route(num)[0]
                        choice = input(f"The price of the ticket is {self.__serv.get_price(route)}. Do you want to continue? (y/n) ")

                        if choice == "y":
                            self.__serv.sell_ticket(num)
                            print("Ticket sold.\n")
                    except Exception as e:
                        print(str(e) + '\n')                        
                case "3":
                    print(f"Total income: {self.__serv.income}")
                case "4":
                    txt = ""
                    routes_tickets = self.__serv.build_report()

                    for i in range(len(routes_tickets[0])):
                        txt += f"{routes_tickets[0][i]},{routes_tickets[1][i]}\n"
                    print(txt + '\n')
                case "5":
                    print("Exiting...\n")
                    return
                case _:
                    print("Invalid command.\n")