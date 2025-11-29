from address import Address
from repo import AddressRepo

class AddressServices:
    def __init__(self):
        self.__repo = AddressRepo()
    
    def add(self, new_address:Address):
        self.__repo.add(new_address)
    
    def list_addresses(self):
        text = ""
        addresses = self.__repo.list()
        for address in addresses:
            text += str(address) + '\n'
        
        return text

    def find_addresses(self, posX:int, posY:int, dist:int):
        """Finds all the addresses for which the distance between them and the position at coordintes (posX, posY) is at most dist

        :param posX: the x-cord. of the desired position
        :type posX: int
        :param posY: the y-cord. of the desired position
        :type posY: int
        :param dist: the desired maximum distance between the point and an adress
        :type dist: int
        :return: a list of tuples in which the first element is the address that has the property above, and the second element is the distance
        :rtype: list
        """
        addresses = self.__repo.list()
        filtered_data = []

        for address in addresses:
            euc_dist = ((posX - address.x)**2 + (posY - address.y)**2)**(0.5)
            if euc_dist <= dist:
                filtered_data.append((address, euc_dist))
        
        return filtered_data
    
    def find_best_new_location(self):
        min_dist, bestX, bestY = 1e9, -101, -101
        addresses = self.__repo.list()

        positions = []
        for address in addresses:
            positions.append((address.x, address.y))

        for x in range(-100, 101):
            for y in range(-100, 101):
                if (x, y) not in positions:
                    total_distance = 0
                    for position in positions:
                        total_distance += ((position[0] - x) ** 2 + (position[1] - y) ** 2) ** 0.5

                    if min_dist > total_distance:
                        min_dist = total_distance
                        bestX, bestY = x, y
        
        return (bestX, bestY)