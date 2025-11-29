import sys, unittest
sys.path.append("./src")
from repository.stud_repos.memo_repo import StudMemoRepo
from repository.disc_repos.memo_repo import DiscMemoRepo
from repository.grade_repos.memo_repo import GradeMemoRepo 

from domain.student import Student
from domain.discipline import Discipline
from domain.grade import Grade

class TestMemoRepo(unittest.TestCase):
    def setUp(self):
        self.stud_repo = StudMemoRepo()
        self.disc_repo = DiscMemoRepo()
        self.grade_repo = GradeMemoRepo()

    def test_add_stud(self):
        self.stud_repo.add(Student(1, "Paul"))
        self.assertEqual(len(self.stud_repo.data), 1)
    
    def test_add_disc(self):
        self.disc_repo.add(Discipline(1, "Math"))
        self.assertEqual(len(self.disc_repo.data), 1)

    def test_add_grade(self):
        self.grade_repo.add(Grade(1, 2, 3))
        self.assertEqual(len(self.grade_repo.data), 1)

if __name__ == '__main__':
    unittest.main()