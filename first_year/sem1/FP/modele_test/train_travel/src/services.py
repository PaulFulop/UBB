from repo import Repo
from domain import Route

class Services:
    def __init__(self, file_path:str):
        """class constructor for the Services class

        :param file_path: the path of the file to look in
        :type file_path: str
        """
        self.__repo = Repo(file_path)
        self.h_rate = self.__repo.hourly_rate()
        self.income = 0
        self.sold_tickets = [0] * len(self.__repo.get_routes())
    
    def add_route(self, new_route:Route):
        """adds a new route

        :param new_route: the new route to be added 
        :type new_route: Route
        """
        self.__repo.add(new_route)
        self.sold_tickets.append(0)
    
    def sell_ticket(self, num:int):
        """sell a ticket for a certain route

        :param num: the unique route number
        :type num: int
        """
        route, i = self.find_route(num)
        self.__repo.update_tickets(i)
        self.add_price(route)
        self.sold_tickets[i] += 1

    def find_route(self, num:int):
        """finds the route given the unique number

        :param num: the unique identifier of every route
        :type num: int
        :raises ValueError: _description_
        """
        routes = self.__repo.get_routes()[:]
        for i in range(len(routes)):
            if routes[i].num == num:

                return (routes[i], i)
            
        raise ValueError(f"Train route with number {num} not found.")

    def add_price(self, route:Route):
        """adds the price to the total income when a ticket is sold

        :param route: the route for which the ticket was sold
        :type route: Route
        """
        self.income += self.get_price(route)

    def get_price(self, route:Route):
        """computes the price

        :param route: the route to compute the ticket price for
        :type route: Route
        :return: the amount of money needed to pay
        :rtype: int
        """
        hour1, minute1 = route.t1.split(":")
        hour1, minute1 = int(hour1), int(minute1)

        hour2, minute2 = route.t2.split(":")
        hour2, minute2 = int(hour2), int(minute2)

        deltaT = 60 * (hour2 - hour1) + minute2 - minute1
        return deltaT
    
    def build_report(self):
        """builds a report based on how many tickets were sold for each route

        :return: a tuple consisting of all the routes and number of sold tickets for each route
        :rtype: tuple
        """
        sorted_routes = self.__repo.get_routes()[:]
        sorted_tickets = self.sold_tickets[:]

        for i in range(len(sorted_routes) - 1):
            for j in range(i, len(sorted_routes)):
                if sorted_tickets[i] < sorted_tickets[j]:
                    sorted_routes[i], sorted_routes[j] = sorted_routes[j], sorted_routes[i]
                    sorted_tickets[i], sorted_tickets[j] = sorted_tickets[j], sorted_tickets[i]

        return (sorted_routes, sorted_tickets)