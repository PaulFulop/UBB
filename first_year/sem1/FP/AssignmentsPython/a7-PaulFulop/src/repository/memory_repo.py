import sys
sys.path.append("./src")
from domain.expense import Expense

class ExpenseMemoryRepository():
    """Class for storing the expenses in memory.
    """
    def __init__(self, initial_list:list):
        """Initialize the repository with a given list.

        :param initial_list: The list from which we store expenses in memory.
        :type initial_list: list
        """
        self._data = initial_list
        self._history = []
        self._history.append(self._data[:])

    def add(self, new_expense:Expense):
        """Adds a new expense and stores it in memory.

        :param new_expense: The new expense to add.
        :type new_expense: Expense
        """
        self._data.append(new_expense)
        self._history.append(self._data[:])

    def filter(self, value:int):
        """Filter the list so that it contains only expenses above a certain value..

        :param value: The value used to filter.
        :type value: int
        """
        for exp in self._data[:]:
            if exp.money <= value:
                self._data.remove(exp)
        
        self._history.append(self._data[:])

    def undo(self):
        """ Undo the last operation that modified the list of expenses.
            This step can be repeated.
            The user can undo only those operations made during the current run of the program.
            :raises IndexError: If there are no more changes to the expenses list.
        """
        if len(self._history) == 1:
            raise IndexError("There are no more changes to the expenses list.")
        
        self._history.pop()
        self._data.clear()
        self._data.extend(self._history[-1][:])
    
    def __len__(self):
        """Will make len work for a custom list.

        :return: The length of the list of expenses stored in _data.
        :rtype: int
        """
        return len(self._data)

def test_add_expense():
    # Verify if adding works
    expenses = [Expense(12, 15, "food"), Expense(12, 50, "others"), Expense(15, 10, "others")]
    memo_repo = ExpenseMemoryRepository(expenses)

    memo_repo.add(Expense(13, 15, "food"))
    assert len(memo_repo) == 4, "Adding doesn't work properly."

# test_add()