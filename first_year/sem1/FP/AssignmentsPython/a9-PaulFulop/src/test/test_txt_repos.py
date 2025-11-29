import sys, unittest
sys.path.append("./src")
from repository.stud_repos.txt_repo import StudTxtRepo
from repository.disc_repos.txt_repo import DiscTxtRepo
from repository.grade_repos.txt_repo import GradeTxtRepo 

from domain.student import Student
from domain.discipline import Discipline
from domain.grade import Grade

class TestMemoRepo(unittest.TestCase):
    def setUp(self):
        self.stud_repo = StudTxtRepo("src/test/mock_file.txt")
        self.disc_repo = DiscTxtRepo("src/test/mock_file.txt")
        self.grade_repo = GradeTxtRepo("src/test/mock_file.txt")

    def test_add_stud(self):
        self.stud_repo.add(Student(1, "Paul"))
        self.assertEqual(len(self.stud_repo.data), 1)
        file = open("src/test/mock_file.txt", "wt")
        file.close()
    
    def test_add_disc(self):
        self.disc_repo.add(Discipline(1, "Math"))
        self.assertEqual(len(self.disc_repo.data), 1)
        file = open("src/test/mock_file.txt", "wt")
        file.close()

    def test_add_grade(self):
        self.grade_repo.add(Grade(1, 2, 3))
        self.assertEqual(len(self.grade_repo.data), 1)
        file = open("src/test/mock_file.txt", "wt")
        file.close()

if __name__ == '__main__':
    unittest.main()