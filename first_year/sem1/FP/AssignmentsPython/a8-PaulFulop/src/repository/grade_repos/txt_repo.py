import sys
sys.path.append("./src")

from domain.grade import Grade
from repository.grade_repos.memo_repo import GradeMemoRepo

class GradeTxtRepo(GradeMemoRepo):
    """Repository class used for storing data in a text file.

    :param GradeMemoRepo: The parent class.
    :type GradeMemoRepo: class
    """
    def __init__(self, file_name:str):
        super().__init__()
        self.file_name = file_name
        self._load()
    
    def add(self, new_grade:Grade):
        """Add a new grade to the repository.

        :param new_grade: The new grade to add.
        :type new_grade: Grade
        """
        super().add(new_grade)
        self._save()
    
    def remove_by_stud_id(self, stud_id):
        super().remove_by_stud_id(stud_id)
        self._save()

    def remove_by_disc_id(self, disc_id):
        super().remove_by_disc_id(disc_id)
        self._save()

    def _save(self):
        try:
            file = open(self.file_name, "wt")
        except FileNotFoundError:
            return
        
        for grade in self._data:
            file.write(f"{grade.disc_id},{grade.stud_id},{grade.grade}\n")
        file.close()

    def _load(self):
        try:
            file = open(self.file_name, "rt")
        except FileNotFoundError:
            return
        
        lines = file.readlines()
        for line in lines:
            tokens = line.split(",")
            self._data.append(Grade(int(tokens[0]), int(tokens[1]), int(tokens[2].removesuffix("\n"))))
        file.close()

# grade = GradeTxtRepo("src/repository/grade_repos/grades.txt")
# grade.add(Grade(1, 2, 4))