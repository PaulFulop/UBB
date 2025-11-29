import sys
sys.path.append("./src")
from domain.student import Student  
from repository.stud_repos.memo_repo import StudMemoRepo

class StudTxtRepo(StudMemoRepo):
    """Repository class used for storing data in a text file.

    :param StudMemoRepo: The parent class.
    :type StudMemoRepo: class
    """
    def __init__(self, file_name:str):
        super().__init__()
        self.file_name = file_name
        self._load()
    
    def add(self, new_stud:Student):
        """Add a new student.

        :param new_stud: The new student to add.
        :type new_stud: Student
        """
        super().add(new_stud)
        self._save()
    
    def remove(self, stud):
        super().remove(stud)
        self._save()
    
    def update(self, stud, new_name):
        super().update(stud, new_name)
        self._save()
    
    def find_by_id(self, stud):
        return super().find_by_id(stud)
    
    def find_by_name(self, stud_name):
        return super().find_by_name(stud_name)
    
    def _save(self):
        try:
            file = open(self.file_name, "wt")
        except FileNotFoundError:
            return
        
        for stud in self._data.values():
            file.write(f"{stud.id},{stud.name}\n")
        file.close()

    def _load(self):
        try:
            file = open(self.file_name, "rt")
        except FileNotFoundError:
            return
        
        lines = file.readlines()
        for line in lines:
            tokens = line.split(",")
            super().add(Student(int(tokens[0]), tokens[1].removesuffix("\n")))
        file.close()


stud_repo = StudTxtRepo("src/repository/stud_repos/students.txt")
#stud_repo.add(Student(10, "Romana"))