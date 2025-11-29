import sys, pickle
sys.path.append("./src")

from domain.grade import Grade
from repository.grade_repos.txt_repo import GradeTxtRepo

class GradeBinRepo(GradeTxtRepo):
    """Repository class used for storing data in a binary file.

    :param GradeTxtRepo: The parent class.
    :type GradeTxtRepo: class
    """
    def __init__(self, file_name):
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
            self._data = []
        
        file.close()