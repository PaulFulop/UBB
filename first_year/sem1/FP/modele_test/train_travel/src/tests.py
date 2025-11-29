import unittest
import random
from domain import Route
from services import Services
from repo import Repo

class Tests(unittest.TestCase):
    def test_repo(self):
        random_int = random.randint(1, 100)
        repo = Repo("src/mock_file.txt")
        repo.add(Route(random_int, "test1", "10:20", "test3", "12:23", 1))
        self.assertGreater(len(repo.get_routes()), 0)
        self.assertEqual(random_int, repo.get_routes()[-1].num)
        self.assertEqual(1, repo.hourly_rate())

        tickets = repo.get_routes()[-1].tickets
        repo.update_tickets(len(repo.get_routes()))
        self.assertEqual(tickets - 1, repo.get_routes()[-1].tickets)



    def test_services(self):
        serv = Services("src/mock_file.txt")
        random_int = random.randint(1, 100)
        

    def test_route(self):
        try:
            route1 = Route(1, "test1", "10:20", "test1", "12:23", 1)

        except Exception as e:
            self.assertEqual(type(e), ValueError)
        try:
            route2 = Route(1, "test1", "15:20", "test2", "12:23", 1)
        except Exception as e:
            self.assertEqual(type(e), ValueError)
        try:
            route3 = Route(1, "test1", "15:20", "test2", "12:23", -1)
        except Exception as e:
            self.assertEqual(type(e), ValueError)

if __name__ == "__main__":
    unittest.main()