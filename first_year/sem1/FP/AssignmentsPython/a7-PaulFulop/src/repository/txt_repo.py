import sys
sys.path.append("./src")
from repository.memory_repo import ExpenseMemoryRepository
from domain.expense import Expense


class ExpenseTxtRepository(ExpenseMemoryRepository):
    """Class for storing the expenses using a text file.

    :param ExpenseMemoryRepository: The parent class.
    """
    def __init__(self, initial_list:list):
        """Initialize the repository with a given list.

        :param initial_list: The list from which we store expenses in the text file.
        :type initial_list: list
        """
        if self.__file_empty() == True:
            super().__init__(initial_list)
            self.__save()
        else:
            self.__load()
            self._history = [self._data[:]]
    
    def add(self, new_expense:Expense):
        """Adds a new expense.

        :param new_expense: The new expense to add.
        :type new_expense: Expense
        """
        super().add(new_expense)
        self.__save()
    
    def filter(self, value:int):
        """Filter the list so that it contains only expenses above a certain value and update the text file.

        :param value: The value used to filter.
        :type value: int
        """
        super().filter(value)
        self.__save()
    
    def undo(self):
        """ Undo the last operation that modified the list of expenses and update the text file.
            This step can be repeated.
            The user can undo only those operations made during the current run of the program.
        """
        super().undo()
        self.__save()
    
    def __file_empty(self):
        try:
            file = open("src/repository/expenses.txt", "r")
            if file.read().strip() == "":
                file.close()
                return True
            file.close()
            return False
        except FileNotFoundError as fnfe:
            print(fnfe)

    def __save(self):
        """Overwrite the text file with the new list o expenses and save it.

        :raises FileNotFoundError: If the file path is incorrect or the directory does not exist.
        """
        try:
            file = open("src/repository/expenses.txt", "wt")
            str_data = []
            for exp in self._data:
                str_data.append(str(exp) + "\n")
            file.writelines(str_data)
            file.close()     
        except FileNotFoundError as fnfe:
            print(fnfe)
    
    def __load(self):
        try:
            file = open("src/repository/expenses.txt", "r")
            lines = file.readlines()
            expenses = []
            for line in lines:
                words = line.split(" ")
                for word in words:
                    word.strip()

                expenses.append(Expense(int(words[1][:-1]), int(words[3][:-1]), words[5][:-2])) 

            self._data = expenses[:]
        except FileNotFoundError as fnfe:
            print(fnfe)

def test_add_expense():
    # Verify if adding works
    expenses = [Expense(12, 15, "food"), Expense(12, 50, "others"), Expense(15, 10, "others")]
    txt_repo = ExpenseTxtRepository(expenses)

    txt_repo.add(Expense(13, 15, "food"))
    assert len(txt_repo) == 4, "Adding doesn't work properly."

    # Verify if the file has been modified
    file = open("src/repository/expenses.txt", "r")
    lines = file.readlines()
    assert len(lines) == 4, "The text file was not modified properly."

# test_add()