from domain import Adress
from repository import Repo

class Services:
    def __init__(self):
        self.__repo = Repo()
    
    def add_adress(self, new_address:Adress):
        self.__repo.add(new_address)
    
    def determine_addresses(self, posX:int, posY:int, dist:int):
        """Determines what addresses have distance at most "dist" from point (posX, posY) and returns
          all data about addresses and their distance in ncreasing order of the distance.

        :param posX: the desired x-coordinate
        :type posX: int
        :param posY: the desired y-coordinate
        :type posY: int
        :param dist: the desired maximum distance
        :type dist: int
        """
        addresses = self.__repo.list_adresses()[:]
        filtered_data = []

        for address in addresses:
            d = ((address.x - posX)**2 + (address.y - posY)**2)**0.5
            if d <= dist:
                filtered_data.append((address, d))
        
        for i in range(len(filtered_data) - 1):
            for j in range(i + 1, len(filtered_data)):
                if filtered_data[i][1] > filtered_data[j][1]:
                    filtered_data[i], filtered_data[j] = filtered_data[j], filtered_data[i]
        
        return filtered_data
    
    def determine_new_station(self):
        bestX, bestY = -1e9, -1e9
        min_avg_dist = 1e9
        positions = []
        addresses = self.__repo.list_adresses()[:]
        min_pointX, min_pointY = 1e9, 1e9
        max_pointX, max_pointY = -1e9, -1e9

        for address in addresses:
            positions.append((address.x, address.y))

            min_pointX = min(min_pointX, address.x)
            min_pointY = min(min_pointY, address.y)

            max_pointX = max(max_pointX, address.x)
            max_pointY = max(max_pointY, address.y)

        for x in range(min_pointX - 10, max_pointX + 10):
            for y in range(min_pointY - 10, max_pointY + 10):
                if (x, y) not in positions:
                    avg_dist = 0
                    for posX, posY in positions:
                        avg_dist += ((posX - x)**2 + (posY - y)**2)**0.5
                    avg_dist /= len(positions)

                    if avg_dist < min_avg_dist:
                        min_avg_dist = avg_dist
                        bestX, bestY = x, y 
        return (bestX, bestY)