import sys
sys.path.append("./src")
from domain.expense import Expense
from repository.memory_repo import ExpenseMemoryRepository
from repository.txt_repo import ExpenseTxtRepository
from repository.bin_repo import ExpenseBinRepository
from repository.json_repo import ExpenseJsonRepository
from repository.db_repo import ExpenseDataBaseRepository

class ExpenseServices:
    def __init__(self, expenses:list):
        self.__get_repository(expenses)
    
    def add_expense(self, day:int, amount:int, type:str):
        """Adds a new expense

        :param day: The day when the expense was made
        :type day: int
        :param amount: The amount of money for the expense
        :type amount: int
        :param type: The type of the expense
        :type type: str
        """

        new_expense = Expense(day, amount, type)
        self.__expenses_repo.add(new_expense)
    
    def display_expenses(self):
        if len(self.__expenses_repo._data) == 0:
            return "No expenses to display."

        output = "Here's the list of expenses for this month:\n\n" 
        for expense in self.__expenses_repo._data:
            output += str(expense) + "\n"
        return output[:len(output) - 1]
    
    def filter_expenses(self, value:int):
        if value < 0:
            raise ValueError("Invalid value.")
        self.__expenses_repo.filter(value)
    
    def undo_expenses(self):
        self.__expenses_repo.undo()
    
    def __get_repository(self, expenses:list):
        file = open("src/settings.properties", "r")
        line = file.readline()
        repo = line.split("=")[1].strip()

        match repo:
            case "0":
                self.__expenses_repo = ExpenseMemoryRepository(expenses)
            case "1":
                self.__expenses_repo = ExpenseTxtRepository(expenses)
            case "2":
                self.__expenses_repo = ExpenseBinRepository(expenses)
            case "3":
                self.__expenses_repo = ExpenseJsonRepository(expenses)
            case "4":
                self.__expenses_repo = ExpenseDataBaseRepository(expenses, "paul", "Paul", "Paul1234", "Data", "ExpensesTable")
            case _:
                self.__expenses_repo = ExpenseMemoryRepository(expenses)
    
    @property
    def expenses(self):
        return self.__expenses_repo

def test_add_expense():
    # Verify if adding works.
    expenses = [Expense(1, 50, "food"), Expense(2, 20, "transport")]
    services = ExpenseServices(expenses)
    services.add_expense(3, 75, "internet")
    assert len(expenses) == 3, "Adding doesn't work properly."

    # Verify if the ValueErrors are raised properly
    try:
        services.add_expense(31, 50, "food")
        print("Value error for invalid day not raised.")
    except ValueError as e:
        assert str(e) == "Invalid day.", "Not the expected ValueError for invalid day."

    try:
        services.add_expense(30, -1, "food")
        print("Value error for negative amount of money not raised.")
    except ValueError as e:
        assert str(e) == "Amount of money can't be negative.", "Not the expected ValueError for negative amount of money."

    try:
        services.add_expense(30, 1, "invalid_category")
        print("Value error for invalid type not raised.")
    except ValueError as e:
        assert str(e) == "Invalid type.", "Not the expected ValueError for invalid type."

# test_add_expense()