import sys
import pickle
sys.path.append("./src")
from repository.memory_repo import ExpenseMemoryRepository
from domain.expense import Expense

class ExpenseBinRepository(ExpenseMemoryRepository):
    """Class for storing the expenses using a binary file.

    :param ExpenseMemoryRepository: The parent class.
    """
    def __init__(self, initial_list:list):
        """Initialize the repository with a given list.

        :param initial_list: The list from which we store expenses in the binary file.
        :type initial_list: list
        """
        if self.__file_empty() == True:
            super().__init__(initial_list)
            self.__save()
        else:
            self.__load()
            self._history = [self._data[:]]
    
    def add(self, new_expense:list):
        """Add a new expense and update the binary file.

        :param new_expense: The new expense to add.
        :type new_expense: list
        """
        super().add(new_expense)
        self.__save()
    
    def filter(self, value:int):
        """Filter the list so that it contains only expenses above a certain value and update the binary file.

        :param value: The value used to filter.
        :type value: int
        """
        super().filter(value)
        self.__save()
    
    def undo(self):
        """ Undo the last operation that modified the list of expenses and update the binary file.
            This step can be repeated.
            The user can undo only those operations made during the current run of the program.
        """
        super().undo()
        self.__save()

    def __file_empty(self):
        try:
            file = open("src/repository/expenses.bin", "rb")
            if file.read(1):
                file.close()
                return False
            file.close()
            return True
        except FileNotFoundError as fnfe:
            print(fnfe)

    def __save(self):
        """Overwrite the binary file with the new list o expenses and save it.

        :raises FileNotFoundError: If the file path is incorrect or the directory does not exist.
        """
        try:
            file = open("src/repository/expenses.bin", "wb")
            pickle.dump(self._data, file)
            file.close()
        except FileNotFoundError as fnfe:
            print(fnfe)
    
    def __load(self):
        try:
            file = open("src/repository/expenses.bin", "rb")
            self._data = pickle.load(file)
            file.close()
        except FileNotFoundError as fnfe:
            print(fnfe)

def test_add_expense():
    # Verify if adding works
    expenses = [Expense(12, 15, "food"), Expense(12, 50, "others"), Expense(15, 10, "others")]
    bin_repo = ExpenseBinRepository(expenses)

    bin_repo.add(Expense(13, 15, "internet"))
    assert len(bin_repo) == 4, "Adding doesn't work properly."

    # Verify if the file has been modified
    file = open("src/repository/expenses.bin", "rb")
    lines = pickle.load(file)
    assert len(lines) == 4, "The text file was not modified properly."

# test_add_expense()