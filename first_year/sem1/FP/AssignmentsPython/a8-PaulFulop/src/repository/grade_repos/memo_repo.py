import sys
sys.path.append("./src")

from domain.grade import Grade
from repository.repo_exceptions import InvalidGradeValueError

class GradeMemoRepo():
    """Repository class used for storing data in memory.
    """
    def __init__(self):
        self._data = []
    
    def add(self, new_grade:Grade):
        """Add a new grade to the repository.

        :param new_grade: The new grade to add.
        :type new_grade: Grade
        :raises InvalidGradeValueError: If the grade is not between 1 and 10
        """
        if new_grade.grade < 1 or new_grade.grade > 10:
            raise InvalidGradeValueError
        
        self._data.append(new_grade)
    
    def remove_by_stud_id(self, stud_id:int):
        for grade in self._data[:]:
            if grade.stud_id == stud_id:
                self._data.remove(grade)

    def remove_by_disc_id(self, disc_id:int):
        for grade in self._data[:]:
            if grade.disc_id == disc_id:
                self._data.remove(grade)
    
    @property
    def data(self):
        return self._data