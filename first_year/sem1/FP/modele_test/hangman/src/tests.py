import unittest
from services import Services
from repo import Repo

class TestAdd(unittest.TestCase):
    def test_add(self):
        serv = Services("src/mock_file.txt")
        serv.add_sentence("testing")
        with open("src/mock_file.txt", "rt") as file:
            line = file.readlines()[-1].removesuffix('\n')
            self.assertEqual(line, "testing")

        repo = Repo("src/mock_file.txt")
        repo.add("testing again")
        with open("src/mock_file.txt", "rt") as file:
            line = file.readlines()[-1].removesuffix('\n')
            self.assertEqual(line, "testing again")
        
if __name__ == '__main__':
    unittest.main()