import sys, pickle
sys.path.append("./src")
from domain.discipline import Discipline
from repository.disc_repos.txt_repo import DiscTxtRepo

class DiscBinRepo(DiscTxtRepo):
    """Repository class used for storing data in a binary file.

    :param DiscTxtRepo: The parent class.
    :type DiscTxtRepo: class
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

#bin_repo = DiscBinRepo("src/repository/disc_repos/disciplines.bin")