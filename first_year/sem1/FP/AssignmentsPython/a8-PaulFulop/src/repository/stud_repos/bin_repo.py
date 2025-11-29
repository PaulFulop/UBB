import sys, pickle
sys.path.append("./src")
from domain.student import Student
from repository.stud_repos.txt_repo import StudTxtRepo

class StudBinRepo(StudTxtRepo):
    """Repository class used for storing data in a binary file.

    :param StudTxtRepo: The parent class.
    :type StudTxtRepo: class
    """
    def __init__(self, file_name:str):
        super().__init__(file_name)

    def _save(self):
        try:
            file = open(self.file_name, "wb")
        except FileNotFoundError:
            return
        
        pickle.dump(self._data, file)
        file.close()

    def _load(self):
        try:
            file = open(self.file_name, "rb")
        except FileNotFoundError:
            return
        
        try:    
            self._data = pickle.load(file)
        except EOFError:
            self._data = {}
            
        file.close()

# stud_repo = StudBinRepo("src/repository/stud_repos/students.bin")
# stud_repo.add(Student(1, "Math"))