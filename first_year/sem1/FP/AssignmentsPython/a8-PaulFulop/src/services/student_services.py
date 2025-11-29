import sys
sys.path.append("./src")
from domain.student import Student
from prettytable import PrettyTable

class StudentServices:
    """Class used for managing the functionalities regarding to students.
    """
    def __init__(self, stud_repo, grade_repo):
        self.__stud_repo = stud_repo
        self.__grade_repo = grade_repo

    def add_stud(self, new_stud:Student):
        """Add a new student.

        :param new_stud: The new student to add.
        :type new_stud: Student
        """
        self.__stud_repo.add(new_stud)

    def remove_stud(self, stud_id:int):
        self.__stud_repo.remove(stud_id)
        self.__grade_repo.remove_by_stud_id(stud_id)

    def update_stud(self, stud_id:int, new_name:str):
        self.__stud_repo.update(stud_id, new_name)

    def list_students(self):
        table = self.__initialize_table()
        for stud in self.__stud_repo.data.values():
            table.add_row([stud.id, stud.name])
        return table
    
    def search_stud_by_id(self, stud_id:int):
        return str(self.__stud_repo.find_by_id(stud_id))

    def search_stud_by_name(self, stud_name:str):
        matching_students = self.__stud_repo.find_by_name(stud_name) 

        table = self.__initialize_table()
        for stud in matching_students.values():
            table.add_row([stud.id, stud.name])
        return table

    def __initialize_table(self):
        table = PrettyTable(["ID", "Student name"])
        return table