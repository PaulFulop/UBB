import sys
sys.path.append("./src")
from domain.student import Student
from prettytable import PrettyTable
from services.undo_redo_services import Command, CascadeCommand, FunctionCall

class StudentServices:
    """Class used for managing the functionalities regarding to students.
    """
    def __init__(self, stud_repo, grade_repo, ur_serv):
        self.__stud_repo = stud_repo
        self.__grade_repo = grade_repo
        self.__undo_redo_service = ur_serv

    def add_stud(self, new_stud:Student):
        """Add a new student.

        :param new_stud: The new student to add.
        :type new_stud: Student
        """
        self.__stud_repo.add(new_stud)

        undo_func = FunctionCall(self.__stud_repo.remove, new_stud.id)
        redo_func = FunctionCall(self.__stud_repo.add, new_stud)
        ur_command = Command(undo_func, redo_func)
        self.__undo_redo_service.record(ur_command)

    def remove_stud(self, stud_id:int):

        ur_command = CascadeCommand()
        ur_command.add_undo_function(FunctionCall(self.__stud_repo.add, self.__stud_repo.find_by_id(stud_id)))
        ur_command.add_redo_function(FunctionCall(self.__stud_repo.remove, stud_id))
        ur_command.add_redo_function(FunctionCall(self.__grade_repo.remove_by_stud_id, stud_id))

        for grade in self.__grade_repo.data:
            if grade.stud_id == stud_id:
               ur_command.add_undo_function(FunctionCall(self.__grade_repo.add, grade)) 
        
        self.__undo_redo_service.record(ur_command)

        self.__stud_repo.remove(stud_id)
        self.__grade_repo.remove_by_stud_id(stud_id)

    def update_stud(self, stud_id:int, new_name:str):
        undo_func = FunctionCall(self.__stud_repo.update, stud_id, self.__stud_repo.find_by_id(stud_id).name)
        redo_func = FunctionCall(self.__stud_repo.update, stud_id, new_name)
        ur_command = Command(undo_func, redo_func)
        self.__undo_redo_service.record(ur_command)

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