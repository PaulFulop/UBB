#
# The program's functions are implemented here. There is no user interaction in this file, therefore no input/print statements. Functions here
# communicate via function parameters, the return statement and raising of exceptions. 
#

from texttable import Texttable
import random as rand

#expense (dict): money, day, category

# OTHER
def valid_day(day:int) -> bool:
    """Verifies if the parameter day is between 1 and 30 (a day in a month).

    :param day: the day of the month in which the expense was made
    :type day: int
    :return: true if it's a valid day in a month, false otherwise
    :rtype: bool
    """
    if day in range(1, 31):
        return True
    return False

def valid_category(category:str) -> bool:
    """Verifies if the parameter category is valid (the string is a valid expense type).

    :param category: the expense type for a certain expense
    :type category: str
    :return: true if it's a valid expense type, false otherwise
    :rtype: bool
    """
    if category in ["housekeeping", "food", "transport", "clothing", "internet", "others"]:
        return True
    return False

def create_table(expenses:list) -> Texttable:
    """Creates a table to display the list of expenses.

    :param expenses: the list of expenses
    :type expenses: list
    :return: the texttable containing the required info
    :rtype: Texttable
    """
    table = Texttable()
    header = ["amount of money", "day of the month", "expense category"]

    data = []
    for expense in expenses:
        data.append([get_money(expense), get_day(expense), get_category(expense)])

    table.add_rows([header] + data, True)
    table.set_cols_align(["c", "c", "c"])
    return table

def generate_expenses(n:int, max_money:int) -> list: #to generate a list of n random expenses
    expenses = []
    categories = ["housekeeping", "food", "transport", "clothing", "internet", "others"]

    i = 0
    while i < n:
        money = rand.randint(0, max_money)
        day = rand.randint(1, 30)
        category = rand.choice(categories)
        expenses.append({"money": money, "day": day, "category": category})
        i += 1

    return expenses

# GETTERS
def get_money(expense:dict) -> int:
    return expense["money"]

def get_day(expense:dict) -> int:
    return expense["day"]

def get_category(expense:dict) -> str:
    return expense["category"]

# SETTERS
def set_money(expense:dict, money:int) -> None:
    expense["money"] = money

def set_day(expense:dict, day:int) -> None:
    expense["day"] = day

def set_category(expense:dict, category:str) -> None:
    expense["category"] = category

# (A) Add a new expense
def add_expense(expenses:list, money:int, category:str, stack:list) -> None:
    """Adds a new expense to the end of the list at the current day.

    :param expenses: the list of expenses
    :type expenses: list
    :param money: the sum of money for the expense
    :type money: int
    :param category: the category of the expense
    :type category: str
    :param stack: used to keep track of all the states in the list of expenses (for undo)
    :type stack: list
    :raises ValueError: first value error if the sum of money is negative
    :raises ValueError: second value error if the category is not a valid expense type
    """
    if money < 0:
        raise ValueError("Sum of money can't be negative.")

    if not valid_category(category):
        raise ValueError("Invalid category.")
    
    expenses.append({"money": money, "day": 20, "category": category})
    stack.append(expenses[:])

def insert_expense(expenses:list, money:int, day:int, category:str, stack:list) -> None:
    """Inserts a new expense to the end of the list.

    :param expenses: the list of expenses
    :type expenses: list
    :param money: the sum of money for the expense
    :type money: int
    :param day: the day in which the expense was made
    :type day: int
    :param category: the category of the expense
    :type category: str
    :param stack: used to keep track of all the states in the list of expenses (for undo)
    :type stack: list
    :raises ValueError: first value error if the sum of money is negative
    :raises ValueError: second value error if its not a day in a month
    :raises ValueError: third value error if the category is not a valid expense type
    """
    if money < 0:
        raise ValueError("Sum of money can't be negative.")
    
    if not valid_day(day):
        raise ValueError("Invalid day.")

    if not valid_category(category):
        raise ValueError("Invalid category.")
    
    expenses.append({"money": money, "day": day, "category": category})
    stack.append(expenses[:])

# (B) Modify expenses
def remove_expense_day(expenses:list, day:int, stack:list) -> None:
    """Removes all the expenses at a given day.

    :param expenses: the list of expenses
    :type expenses: list
    :param day: the day of the expenses that have to be removed
    :type day: int
    :param stack: used to keep track of all the states in the list of expenses (for undo)
    :type stack: list
    :raises ValueError: value error if its not a day in a month
    """
    if not valid_day(day):
        raise ValueError("Invalid day.")

    for expense in expenses[:]:
        if get_day(expense) == day:
            expenses.remove(expense)
    
    stack.append(expenses[:])

def remove_expense_days(expenses:list, start_day:int, end_day:int, stack:list) -> None:
    """Remove all the expenses between 2 days.

    :param expenses: the list of expenses
    :type expenses: list
    :param start_day: the first day at which we want to remove the expenses
    :type start_day: int
    :param end_day: the last day at which we want to remove the expenses
    :type end_day: int
    :param stack: used to keep track of all the states in the list of expenses (for undo)
    :type stack: list
    :raises ValueError: value error if one / both of the days are not included in a month of 30 days
    """
    if not valid_day(start_day) or not valid_day(end_day):
        raise ValueError("Invalid days.")
    
    for expense in expenses[:]:
        expense_day = get_day(expense)
        if expense_day >= start_day and expense_day <= end_day:
            expenses.remove(expense)
    
    stack.append(expenses[:])
            
def remove_expense_category(expenses:list, category:str, stack:list) -> None:
    """Remove all the expenses with a given category.

    :param expenses: the list of expenses
    :type expenses: list
    :param category: the category of the expenses that have to be removed
    :type category: str
    :param stack: used to keep track of all the states in the list of expenses (for undo)
    :type stack: list
    :raises ValueError: value error if the category is not a valid expense type
    """
    if not valid_category(category):
        raise ValueError("Invalid category.")

    for expense in expenses[:]:
        if get_category(expense) == category:
            expenses.remove(expense)
    
    stack.append(expenses[:])

# (C) Display expenses with different properties
def list_expenses(expenses:list) -> list:
    """Displays all the current expenses in a texttable.

    :param expenses: the list of expenses
    :type expenses: list
    :raises ValueError: the list of expenses is empty
    :return: the expenses list
    :rtype: list
    """

    if len(expenses) == 0:
        raise ValueError("There are no expenses right now.")

    return expenses
    t = create_table(expenses)
    print(t.draw())

def list_expenses_category(expenses:list, category:str) -> list:
    """Displays all the current expenses with a given category in a texttable.

    :param expenses: the list of expenses
    :type expenses: list
    :param category: the category of the expenses that have to be displayed
    :type category: str
    :raises ValueError: first value error if the category is not a valid expense type
    :raises ValueError: second value error if the list containing all expenses with a certain type is empty
    :return: the list of expenses for a certain category
    :rtype: list
    """
    if not valid_category(category):
        raise ValueError("Invalid category.")

    req_expenses = [] # expenses to display
    for expense in expenses:
        if get_category(expense) == category:
            req_expenses.append(expense)
    
    if len(req_expenses) == 0:
        raise ValueError("There are no expenses of this category right now.")
    
    return req_expenses
    t = create_table(req_expenses)
    print(t.draw())

def list_expenses_advanced(expenses:list, category:str, symbol:str, money:int) -> list:
    """Displays all the current expenses with a given category and the property that the amount of money spent is < / = / > than a certain value.

    :param expenses: the list of expenses
    :type expenses: list
    :param category: the category of the expenses that have to be displayed
    :type category: str
    :param symbol: < / = / > (the preffered comparison between the amount of money spent with the value of "money")
    :type symbol: str
    :param money: value to compare with the amount of money spent in a expense
    :type money: int
    :raises ValueError: first value error if the category is not a valid expense type
    :raises ValueError: second value error if "money" is negative
    :raises ValueError: third value error if there are no expenses with that property
    :raises ValueError: fourth value error if there are no expenses with that property
    :raises ValueError: fifth value error if there are no expenses with that property
    :raises ValueError: sixth value error if the symbol is not < / = / >
    :return: the list of expenses for a certain category and for which the amount of money spent is < / = / > than a certain value
    :rtype: list
    """
    if not valid_category(category):
        raise ValueError("Invalid category.")

    if money < 0:
        raise ValueError("The value in 'money' can't be negative.")
    
    req_expenses_lower, req_expenses_equal, req_expenses_greater = [], [], []

    for expense in expenses:
        if get_category(expense) == category:
            if get_money(expense) < money:
                req_expenses_lower.append(expense)
            elif get_money(expense) == money:
                req_expenses_equal.append(expense)
            else:
                req_expenses_greater.append(expense)

    match symbol:
        case "<":
          if len(req_expenses_lower) == 0:
              raise ValueError("There are no expenses with this property right now.")

          return req_expenses_lower  
          print(create_table(req_expenses_lower).draw())
        case "=":
            if len(req_expenses_equal) == 0:
              raise ValueError("There are no expenses with this property right now.")
            
            return req_expenses_equal
            print(create_table(req_expenses_equal).draw())
        case ">":
            if len(req_expenses_greater) == 0:
              raise ValueError("There are no expenses with this property right now.")
            
            return req_expenses_greater
            print(create_table(req_expenses_greater).draw())
        case _:
            raise ValueError("Invalid symbol.")


# (D) Filter expenses
def filter_expenses_category(expenses:list, category:str, stack:list) -> None:
    """Only keeps the expenses that have a certain category.

    :param expenses: the list of expenses
    :type expenses: list
    :param category: the category of the expenses that will remain in the list
    :type category: str
    :param stack: used to keep track of all the states in the list of expenses (for undo)
    :type stack: list
    :raises ValueError: value error if the category is not a valid expense type
    """
    if not valid_category(category):
        raise ValueError("Invalid category.")

    for expense in expenses[:]:
        if get_category(expense) != category:
            expenses.remove(expense)
    
    stack.append(expenses[:])

def filter_expenses_advanced(expenses:list, category:str, symbol:str, money:int, stack:list) -> None:
    """Only keeps the expenses that have a certain category and the property that the amount of money spent is < / = / > than a certain value.

    :param expenses: the list of expenses
    :type expenses: list
    :param category: the category of the expenses that will remain in the list
    :type category: str
    :param symbol: < / = / > (the preffered comparison between the amount of money spent with the value of "money")
    :type symbol: str
    :param money: value to compare with the amount of money spent in a expense
    :type money: int
    :param stack: used to keep track of all the states in the list of expenses (for undo)
    :type stack: list
    :raises ValueError: fist value error if the category is not a valid expense type
    :raises ValueError: second value error if the symbol is not < / = / >
    """
    if not valid_category(category):
        raise ValueError("Invalid category.")
    
    flt_expenses_lower, flt_expenses_equal, flt_expenses_greater = [], [], []

    for expense in expenses:
        if get_category(expense) == category:
            if get_money(expense) < money:
                flt_expenses_lower.append(expense)
            elif get_money(expense) == money:
                flt_expenses_equal.append(expense)
            else:
                flt_expenses_greater.append(expense)
    expenses.clear()
    match symbol:
        case "<":
            expenses.extend(flt_expenses_lower)
        case "=":
            expenses.extend(flt_expenses_equal)
        case ">":
            expenses.extend(flt_expenses_greater)
        case _:
            raise ValueError("Invalid symbol.")
    
    stack.append(expenses[:])

# (E) Undo
def undo_operation(expenses:list, stack:list) -> None:
    """Undo the last operation performed on the list of expenses.

    :param expenses: the list of expenses
    :type expenses: list
    :param stack: used to keep track of all the states in the list of expenses
    :type stack: list
    :raises IndexError: index error if the list of expenses is already at the initial state
    """
    if len(stack) == 1:
        raise IndexError("There are no more changes to the expenses list.")

    stack.pop()
    expenses.clear()
    expenses.extend(stack[-1][:])

# TEST FUNCTIONS
def test_add_expense() -> None:
    # Test with empty list
    expenses = []
    add_expense(expenses, 10, "food", [])
    assert expenses == [{"money": 10, "day": 14, "category": "food"}], "Doesn't add expenses on an empty list."

    # Test with non-empty list
    expenses = [{"money": 15, "day": 20, "category": "others"},
                {"money": 100, "day": 25, "category": "food"}]
    expenses_copy = expenses.copy()

    add_expense(expenses, 40, "transport", [])
    assert expenses == expenses_copy + [{"money": 40, "day": 14, "category": "transport"}], "Doesn't add expenses on a non-empty list."

    # Test with negative sum of money
    try:
        add_expense(expenses, -20, "food", [])
    except ValueError as e:
        assert str(e) == "Sum of money can't be negative.", "Expense with negative sum gets added to the list."
    
    #Test with invalid category
    try:
        add_expense(expenses, 10, "invalid category", [])
    except ValueError as e:
        assert str(e) == "Invalid category.", "Expense with invalid category gets added to the list."

def test_insert_expense() -> None:
    #Test with empty list
    expenses = []
    insert_expense(expenses, 15, 10, "food", [])
    assert expenses == [{"money": 15, "day": 10, "category": "food"}], "Doesn't insert expenses on an empty list."

    #Test with a non-empty list
    expenses = [{"money": 15, "day": 20, "category": "others"},
                {"money": 100, "day": 25, "category": "food"}]
    expenses_copy = expenses.copy()

    insert_expense(expenses, 25, 16, "internet", [])
    assert expenses == expenses_copy + [{"money": 25, "day": 16, "category": "internet"}], "Doesn't insert expenses on a non-empty list."

    # Test with negative sum
    try:
        insert_expense(expenses, -2, 10, "food", [])
    except ValueError as e:
        assert str(e) == "Sum of money can't be negative.", "Expense with negative sum gets inserted to the list."
    
    # Test with invalid day
    try:
        insert_expense(expenses, 15, 70, "internet", [])
    except ValueError as e:
        assert str(e) == "Invalid day.", "Expense with invalid day gets inserted to the list."

    # Test with invalid category
    try:
        insert_expense(expenses, 15, 20, "invalid category", [])
    except ValueError as e:
        assert str(e) == "Invalid category.", "Expense with invalid category gets inserted to the list."


def test_remove_expense_day() -> None:
    # Test with a valid day
    expenses = [{"money": 12, "day":20, "category": "food"},
                {"money": 13, "day":21, "category": "internet"},
                {"money": 15, "day":20, "category": "others"},
                {"money": 19, "day":20, "category": "clothing"},
                {"money": 10, "day":20, "category": "food"}]

    remove_expense_day(expenses, 20, [])
    assert expenses == [{"money": 13, "day":21, "category": "internet"}], "Expenses do not get removed as expected."

    # Test with invalid day
    try:
        remove_expense_day(expenses, 50, [])
    except ValueError as e:
        assert str(e) == "Invalid day.", "Invalid day parameter doesn't raise an error."

def test_remove_expense_days() -> None:
    # Test with a valid interval of days
    expenses = [{"money": 12, "day":12, "category": "food"},
            {"money": 13, "day":21, "category": "internet"},
            {"money": 15, "day":13, "category": "others"},
            {"money": 19, "day":14, "category": "clothing"},
            {"money": 10, "day":15, "category": "food"}]

    remove_expense_days(expenses, 10, 20, [])
    assert expenses == [{"money": 13, "day":21, "category": "internet"}], "Expenses do not get removed as expected."

    # Test with invalid start_day
    try:
        remove_expense_days(expenses, 0, 20, [])
    except ValueError as e:
        assert str(e) == "Invalid days.", "Invalid start_day parameter doesn't raise an error."

    # Test with invalid end_day
    try:
        remove_expense_days(expenses, 20, 50, [])
    except ValueError as e:
        assert str(e) == "Invalid days.", "Invalid end_day parameter doesn't raise an error."  

def test_remove_expense_category() -> None:
 # Test with a valid category
    expenses = [{"money": 12, "day":12, "category": "food"},
            {"money": 13, "day":21, "category": "internet"},
            {"money": 15, "day":13, "category": "food"},
            {"money": 19, "day":14, "category": "food"},
            {"money": 10, "day":15, "category": "food"}]

    remove_expense_category(expenses, "food", [])
    assert expenses == [{"money": 13, "day":21, "category": "internet"}], "Expenses do not get removed as expected."

    # Test with invalid category
    try:
        remove_expense_category(expenses, "invalid_category", [])
    except ValueError as e:
        assert str(e) == "Invalid category.", "Invalid category parameter doesn't raise an error."

# test_remove_expense_category()
# test_remove_expense_day()
# test_remove_expense_days()
# test_add_expense()
# test_insert_expense()