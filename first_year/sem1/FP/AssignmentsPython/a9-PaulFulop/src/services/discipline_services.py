import sys
sys.path.append("./src")
from domain.discipline import Discipline
from prettytable import PrettyTable
from services.undo_redo_services import Command, CascadeCommand, FunctionCall

class DisciplineServices:
    """Class used for managing the functionalities regarding to disciplines.
    """
    def __init__(self, disc_repo, grade_repo, ur_serv):
        self.__disc_repo = disc_repo
        self.__grade_repo = grade_repo
        self.__undo_redo_service = ur_serv

    def add_disc(self, new_disc:Discipline):
        """Add a new discipline to the currently working repository.

        :param new_disc: The new discipline to add
        :type new_disc: Discipline
        """
        self.__disc_repo.add(new_disc)

        undo_func = FunctionCall(self.__disc_repo.remove, new_disc.id)
        redo_func = FunctionCall(self.__disc_repo.add, new_disc)
        ur_command = Command(undo_func, redo_func)
        self.__undo_redo_service.record(ur_command)

    def remove_disc(self, disc_id:int):
        ur_command = CascadeCommand()
        ur_command.add_undo_function(FunctionCall(self.__disc_repo.add, self.__disc_repo.find_by_id(disc_id)))
        ur_command.add_redo_function(FunctionCall(self.__disc_repo.remove, disc_id))
        ur_command.add_redo_function(FunctionCall(self.__grade_repo.remove_by_disc_id, disc_id))

        for grade in self.__grade_repo.data:
            if grade.disc_id == disc_id:
                ur_command.add_undo_function(FunctionCall(self.__grade_repo.add, grade))

        self.__undo_redo_service.record(ur_command)

        self.__disc_repo.remove(disc_id)
        self.__grade_repo.remove_by_disc_id(disc_id)

    def update_disc(self, disc_id:int, new_name:str):
        undo_func = FunctionCall(self.__disc_repo.update, disc_id, self.__disc_repo.find_by_id(disc_id).name)
        redo_func = FunctionCall(self.__disc_repo.update, disc_id, new_name)
        ur_command = Command(undo_func, redo_func)
        self.__undo_redo_service.record(ur_command)

        self.__disc_repo.update(disc_id, new_name)

    def list_disciplines(self):
        table = self.__initialize_table()
        for disc in self.__disc_repo.data.values():
            table.add_row([disc.id, disc.name])
        return table
    
    def search_disc_by_id(self, disc_id:int):
        return str(self.__disc_repo.find_by_id(disc_id))

    def search_disc_by_name(self, disc_name:str):
        matching_disciplines = self.__disc_repo.find_by_name(disc_name)

        table = self.__initialize_table()
        for disc in matching_disciplines.values():
            table.add_row([disc.id, disc.name])
        return table

    def __initialize_table(self):
        table = PrettyTable(["ID", "Discipline name"])
        return table