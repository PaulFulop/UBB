
class Route:
    def __init__(self, num:int, d_city:str, t1:str, a_city:str, t2:str, tickets:int):
        """class constructor for the Route class

        :param num: the unique number of every route
        :type num: int
        :param d_city: the departure city
        :type d_city: str
        :param t1: the departure time
        :type t1: str
        :param a_city: the arrival city
        :type a_city: str
        :param t2: the arrival time
        :type t2: str
        :param tickets: the number of avaliable tickets
        :type tickets: int
        :raises ValueError: if the departure city is the same as the arrival city
        :raises ValueError: if the departure time is later than the arrival time
        :raises ValueError: if the number of tickets is invalid
        """
        if d_city == a_city:
            raise ValueError("The departure and arrival city are the same.")
        
        hour1, minute1 = t1.split(":")
        hour1, minute1 = int(hour1), int(minute1)

        hour2, minute2 = t2.split(":")
        hour2, minute2 = int(hour2), int(minute2)

        if hour1 > hour2 or (hour1 == hour2 and minute1 > minute2):
            raise ValueError("You can't depart later than to arrive.")

        if tickets < 0:
            raise ValueError("The number of tickets can't be a negative value.")

        self.num = num
        self.d_city = d_city
        self.t1 = t1
        self.a_city = a_city
        self.t2 = t2   
        self.tickets = tickets

    def __str__(self):
        """string representation for the Route object

        :return: string representation  
        :rtype: str
        """
        return f"{self.num},{self.d_city},{self.t1},{self.a_city},{self.t2},{self.tickets}"     