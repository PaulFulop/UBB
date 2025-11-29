import sys
sys.path.append("./src")

#Parent exception
class RepositoryException(Exception):
    pass

class IDNotFoundError(RepositoryException):
    def __init__(self, id):
        super().__init__(f"ID {id} not found.")

class DuplicateIDError(RepositoryException):
    def __init__(self, id):
        super().__init__(f"ID {id} does exist.")

class InvalidGradeValueError(RepositoryException):
    def __init__(self):
        super().__init__("The grade can't be below than 1 or above 10.")

class NegativeIDError(RepositoryException):
    def __init__(self):
        super().__init__("The ID can't be negative.")