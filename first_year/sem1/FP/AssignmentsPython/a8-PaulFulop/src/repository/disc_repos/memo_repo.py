import sys
sys.path.append("./src")
from domain.discipline import Discipline
from repository.repo_exceptions import IDNotFoundError, DuplicateIDError, NegativeIDError

class DiscMemoRepo():
    """Repository class used for storing data in memory.
    """
    def __init__(self):
        self._data = {}

    def add(self, new_disc:Discipline):
        """Add a new discipline.

        :param new_disc: The new discipline to add.
        :type new_disc: Discipline
        :raises NegativeIDError: If the id is a negative number.
        :raises DuplicateIDError: If the id already exists.Two different disciplines can't have the same id.
        """
        if new_disc.id < 0:
            raise NegativeIDError
        
        if new_disc.id in self._data.keys():
            raise DuplicateIDError(new_disc.id)
        
        self._data[new_disc.id] = new_disc

    def remove(self, disc_id:int):
        if disc_id not in self._data.keys():
            raise IDNotFoundError(disc_id)
        
        self._data.pop(disc_id)
    
    def update(self, disc_id:int, new_name:str):
        if disc_id not in self._data.keys():
            raise IDNotFoundError(disc_id)

        self._data[disc_id] = Discipline(disc_id, new_name)
    
    def find_by_id(self, disc_id:int):
        if disc_id not in self._data.keys():
            raise IDNotFoundError(disc_id)
        
        return self._data[disc_id]
    
    def find_by_name(self, disc_name:str):
        matching_disciplines = {}
        disc_name = disc_name.lower()

        for value in self._data.values():
            if disc_name in value.name.lower():
                matching_disciplines[value.id] = Discipline(value.id, value.name)
        
        return matching_disciplines
    
    @property
    def data(self):
        return self._data