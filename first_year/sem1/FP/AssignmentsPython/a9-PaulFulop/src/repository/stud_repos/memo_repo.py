import sys
sys.path.append("./src")
from domain.student import Student
from repository.repo_exceptions import IDNotFoundError, DuplicateIDError, NegativeIDError

class StudMemoRepo():
    """Repository class used for storing data in memory.
    """
    def __init__(self):
        self._data = {}

    def add(self, new_stud:Student):
        """Add a new student.

        :param new_stud: The new student to add
        :type new_stud: Student
        :raises NegativeIDError: If the id is a negative number.
        :raises DuplicateIDError: If the id already exists.Two different students can't have the same id.
        """
        if new_stud.id < 0:
            raise NegativeIDError
        
        if new_stud.id in self._data.keys():
            raise DuplicateIDError(new_stud.id)
        
        self._data[new_stud.id] = new_stud

    def remove(self, stud_id:int):
        if stud_id not in self._data.keys():
            raise IDNotFoundError(stud_id)
        
        self._data.pop(stud_id)
    
    def update(self, stud_id:int, new_name:str):
        if stud_id not in self._data.keys():
            raise IDNotFoundError(stud_id)

        self._data[stud_id] = Student(stud_id, new_name)
    
    def find_by_id(self, stud_id:int):
        if stud_id not in self._data.keys():
            raise IDNotFoundError(stud_id)
        
        return self._data[stud_id]
    
    def find_by_name(self, stud_name:str):
        matching_students = {}
        stud_name = stud_name.lower()

        for value in self._data.values():
            if stud_name in value.name.lower():
                matching_students[value.id] = Student(value.id, value.name)
        
        return matching_students

    @property
    def data(self):
        return self._data