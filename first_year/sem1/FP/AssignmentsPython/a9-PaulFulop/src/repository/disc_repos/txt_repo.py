import sys
sys.path.append("./src")
from domain.discipline import Discipline
from repository.disc_repos.memo_repo import DiscMemoRepo

class DiscTxtRepo(DiscMemoRepo):
    """Repository class used for storing data in a text file.

    :param DiscMemoRepo: The parent class.
    :type DiscMemoRepo: class
    """
    def __init__(self, file_name:str):
        super().__init__()
        self.file_name = file_name
        self._load()
    
    def add(self, new_disc:Discipline):
        """Add a new discipline.

        :param new_disc: The new discipline to add.
        :type new_disc: Discipline
        """
        super().add(new_disc)
        self._save()
    
    def remove(self, disc_id):
        super().remove(disc_id)
        self._save()
    
    def update(self, disc_id, new_name):
        super().update(disc_id, new_name)
        self._save()
    
    def find_by_id(self, disc_id):
        return super().find_by_id(disc_id)
    
    def find_by_name(self, disc_name):
        return super().find_by_name(disc_name)
    
    def _save(self):
        try:
            file = open(self.file_name, "wt")
        except FileNotFoundError:
            return
        
        for disc in self._data.values():
            file.write(f"{disc.id},{disc.name}\n")
        file.close()

    def _load(self):
        try:
            file = open(self.file_name, "rt")
        except FileNotFoundError:
            return
        
        lines = file.readlines()
        for line in lines:
            tokens = line.split(",")
            super().add(Discipline(int(tokens[0]), tokens[1].removesuffix("\n")))
        file.close()


# disc_repo = DiscTxtRepo("src/repository/disc_repos/disciplines.txt")
# disc_repo.update(20, "Romana")