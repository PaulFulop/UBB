class Student:
    def __init__(self, stud_id:int, name:str):
        self.__stud_id = stud_id
        self.__name = name
    
    def __str__(self):
        return f"Student with ID: {self.__stud_id} and name: {self.__name}."    

    def __repr__(self):
        return str(self)   

    @property
    def id(self):
        return self.__stud_id
    
    @property
    def name(self):
        return self.__name 
    
    @name.setter
    def name(self, new_name:str):
        self.__name = new_name