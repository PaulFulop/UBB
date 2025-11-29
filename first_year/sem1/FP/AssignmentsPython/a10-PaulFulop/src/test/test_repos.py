import sys, unittest
sys.path.append("./src")
from repository.score_repo import ScoreRepo

class TestRepos(unittest.TestCase):
    def test_score_repo(self):
        with open("src/test/mock_file3.txt", "w") as file:
            file.write("0 0")
        
        score_repo = ScoreRepo("src/test/mock_file3.txt")
        self.assertEqual(score_repo.data, [0, 0])

        score_repo.update_score(False)
        self.assertEqual(score_repo.data, [1, 0])

        score_repo.update_score(True)
        self.assertEqual(score_repo.data, [1, 1])


if __name__ == '__main__':
    unittest.main()