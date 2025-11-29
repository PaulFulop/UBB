class Discipline:
    def __init__(self, disc_id:int, name:str):
        self.__disc_id = disc_id
        self.__name = name

    def __str__(self):
        return f"Discipline: {self.__name}, ID: {self.__disc_id}."        
    
    def __repr__(self):
        return str(self)  

    @property
    def id(self):
        return self.__disc_id
    
    @property
    def name(self):
        return self.__name 
    
    @name.setter
    def name(self, new_name:str):
        self.__name = new_name