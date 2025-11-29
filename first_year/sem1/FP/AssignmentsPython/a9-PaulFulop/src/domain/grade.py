class Grade:
    def __init__(self, disc_id:int, stud_id:int, grade:int):        
        self.__disc_id = disc_id
        self.__stud_id = stud_id
        self.__grade = grade
    
    @property
    def disc_id(self):
        return self.__disc_id
    
    @property
    def stud_id(self):
        return self.__stud_id
    
    @property
    def grade(self):
        return self.__grade
    
    def __str__(self):
        return f"{self.__grade} points for student with id {self.__stud_id} at discipline with id {self.__disc_id}"
    
    def __repr__(self):
        return str(self)   