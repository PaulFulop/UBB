
class Student:
    def __init__(self, id:int, name:str, attendance_count:int, grade:int):
        if id < 0 or attendance_count < 0 or grade not in range(0, 11):
            raise ValueError("Invalid student data.")
        
        words = name.split()
        if len(words) < 2:
            raise ValueError("Invalid student data.")
        
        for word in words:
            if len(word) < 3:
                raise ValueError("Invalid student data.")

        self.id = id
        self.name = name
        self.attendance_count = attendance_count
        self.grade = grade

    def __str__(self):
        return f"{self.id}, {self.name}, {self.attendance_count}, {self.grade}"