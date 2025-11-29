from domain import Route

class Repo:
    def __init__(self, file_path:str):
        self.__data = []
        self.__file_path = file_path
        self.__load()
    
    def add(self, new_route:Route):
        """adds a new route

        :param new_route: the new route
        :type new_route: Route
        :raises ValueError: if the route number is already added
        """
        for route in self.__data[1:]:
            if route.num == new_route.num:
                raise ValueError("A route with this number already exists.")
        
        self.__data.append(new_route)
        self.__save()
    
    def hourly_rate(self):  
        """returns the flat hourly rate

        :return: a number that describes the flat hourly rate
        :rtype: int
        """
        return self.__data[0]

    def get_routes(self):
        """returns all the routes

        :return: a list of all routes
        :rtype: list
        """
        return self.__data[1:]

    def update_tickets(self, pos:int):
        """updates a ticket of a train at a certain poition in the data list

        :param pos: the position of the route in the list
        :type pos: int
        """
        self.__data[pos + 1].tickets -= 1
        self.__save()
    
    def __save(self):
        """saves the new content to the file
        """
        try:
            with open(self.__file_path, "wt") as file:
                for obj in self.__data:
                    file.write(str(obj) + '\n')
        except FileNotFoundError:
            pass

    def __load(self):
        """loads the data into the file
        """
        try:
            with open(self.__file_path, "rt") as file:
                self.__data.clear()
                lines = file.readlines()

                for line in lines:
                    if "," not in line:
                        self.__data.append(int(line.removesuffix('\n')))
                    else:
                        tokens = line.split(",")
                        self.__data.append(Route(int(tokens[0]), tokens[1], tokens[2], tokens[3], tokens[4], int(tokens[5])))
        except FileNotFoundError:
            pass