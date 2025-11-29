import sys
sys.path.append("./src")
from domain.grade import Grade
from repository.repo_exceptions import IDNotFoundError
from prettytable import PrettyTable

class GradeServices():
    """Class used for managing the functionalities regarding to grades.
    """
    def __init__(self, grade_repo, disc_repo, stud_repo):
        self.__grade_repo = grade_repo
        self.__disc_repo = disc_repo
        self.__stud_repo = stud_repo

    def grade_student(self, new_grade:Grade):
        """Adds a new grade to a student and at a certain discipline, updating the currently working repository.    

        :param new_grade: The new grade to add.
        :type new_grade: Grade
        :raises IDNotFoundError: The id of the discipline was not found.We can't assign a grade for a non-existing discipline.
        :raises IDNotFoundError: The id of the student was not found.We can't assign a grade to a non-existing student.
        """
        found_disc_id, found_stud_id = False, False

        for disc in self.__disc_repo.data.values():
            if new_grade.disc_id == disc.id:
                found_disc_id = True
                break
        
        for stud in self.__stud_repo.data.values():
            if new_grade.stud_id == stud.id:
                found_stud_id = True
                break
        
        if not found_disc_id:
            raise IDNotFoundError(new_grade.disc_id)      
          
        if not found_stud_id:
            raise IDNotFoundError(new_grade.stud_id)        

        self.__grade_repo.add(new_grade)

    def list_grades(self):
        table = self.__initialize_table()
        for grade in self.__grade_repo.data:
            table.add_row([grade.disc_id, grade.stud_id, grade.grade])
        return table
    
    def __initialize_table(self):
        table = PrettyTable(["Discipline ID", "Student ID", "Grade"])
        return table