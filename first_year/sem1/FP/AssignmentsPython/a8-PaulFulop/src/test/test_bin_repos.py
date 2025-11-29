import sys, unittest
sys.path.append("./src")
from repository.stud_repos.bin_repo import StudBinRepo
from repository.disc_repos.bin_repo import DiscBinRepo
from repository.grade_repos.bin_repo import GradeBinRepo 

from domain.student import Student
from domain.discipline import Discipline
from domain.grade import Grade

class TestMemoRepo(unittest.TestCase):
    def setUp(self):
        self.stud_repo = StudBinRepo("src/test/mock_file.bin")
        self.disc_repo = DiscBinRepo("src/test/mock_file.bin")
        self.grade_repo = GradeBinRepo("src/test/mock_file.bin")

    def test_add_stud(self):
        self.stud_repo.add(Student(1, "Paul"))
        self.assertEqual(len(self.stud_repo.data), 1)
        file = open("src/test/mock_file.bin", "wb")
        file.close()
    
    def test_add_disc(self):
        self.disc_repo.add(Discipline(1, "Math"))
        self.assertEqual(len(self.disc_repo.data), 1)
        file = open("src/test/mock_file.bin", "wb")
        file.close()

    def test_add_grade(self):
        self.grade_repo.add(Grade(1, 2, 3))
        self.assertEqual(len(self.grade_repo.data), 1)
        file = open("src/test/mock_file.bin", "wb")
        file.close()

if __name__ == '__main__':
    unittest.main()