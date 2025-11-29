from domain import Adress

class Repo:
    def __init__(self):
        self.__data = []
    
    def add(self, new_adress:Adress):
        self.__load()
        for adress in self.__data:
            if adress.id == new_adress.id:
                raise ValueError(f"ID {new_adress.id} already exists.")
        
        self.__data.append(new_adress)
        self.__save()
    
    def list_adresses(self):
        self.__load()
        return self.__data
    
    def __load(self):
        self.__data.clear()
        with open("src/adresses.txt", "rt") as file:
            lines  = file.readlines()

            for line in lines:
                tokens = line.split(',')
                self.__data.append(Adress(int(tokens[0].strip()), tokens[1].strip(), tokens[2].strip(), int(tokens[3].strip()), int(tokens[4].strip().removesuffix('\n'))))
            
    def __save(self):
        with open("src/adresses.txt", "wt") as file:
            for adress in self.__data:
                file.write(str(adress) + '\n')

