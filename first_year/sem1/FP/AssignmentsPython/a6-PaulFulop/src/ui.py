#
# This is the program's UI module. The user interface and all interaction with the user (print and input statements) are found here
#

from functions import add_expense
from functions import insert_expense
from functions import remove_expense_day
from functions import remove_expense_days
from functions import remove_expense_category
from functions import list_expenses
from functions import list_expenses_category
from functions import list_expenses_advanced
from functions import filter_expenses_category
from functions import filter_expenses_advanced
from functions import undo_operation
from functions import generate_expenses
from functions import create_table

def menu() -> None:
    expenses = generate_expenses(10, 1000)
    history = []
    history.append(expenses[:])
    cmd_guide()

    while True:
        command = input("> ").lower() # the input won't be case sensitive 
        word = command.split()

        match word[0]:
            case "add":
                if len(word) != 3:
                    print("Invalid command.\n")
                else:
                    try:
                        money = int(word[1])
                        category = word[2]
                        add_expense(expenses, money, category, history)
                        print(f"Added expense of {money} RON for {category} at the current day.\n")
                    except ValueError as e:
                        print(str(e) + "\n")
            case "insert":
                if len(word) != 4:
                    print("Invalid command.\n")
                else:
                    try:
                        day = int(word[1])
                        money = int(word[2])
                        category = word[3]
                        insert_expense(expenses, money, day, category, history)
                        print(f"Added expense of {money} RON for {category} at day {day}.\n")
                    except ValueError as e:
                        print(str(e) + "\n")
            case "remove":
                if len(word) == 4 and word[2] == "to":
                    try:
                        start_day = int(word[1])
                        end_day = int(word[-1])
                        remove_expense_days(expenses, start_day, end_day, history)
                        print(f"Removed expenses between day {start_day} and day {end_day}.\n")
                    except ValueError as e:
                        print(str(e) + "\n")
                elif len(word) == 2:
                    try:
                        day = int(word[1])
                        try:
                            remove_expense_day(expenses, day, history)
                            print(f"Removed all expenses from day {day}.\n")
                        except ValueError as e:
                            print(str(e) + "\n")
                    except ValueError as e:
                        try:
                            category = word[1]
                            remove_expense_category(expenses, category, history)
                            print(f"Removed all expenses for {category}.\n")
                        except ValueError as e:
                            print(str(e) + "\n")  
                else:
                    print("Invalid command.\n")
            case "list":
                if len(word) == 1:
                    try:
                        print(create_table(list_expenses(expenses)).draw())
                    except ValueError as e:
                        print(str(e) + "\n")
                elif len(word) == 2:
                    try:
                        category = word[1]
                        try:
                            print(create_table(list_expenses_category(expenses, category)).draw())
                        except ValueError as e:
                            print(str(e) + "\n")
                    except ValueError as e:
                        print(str(e) + "\n")
                elif len(word) == 4:
                    try:
                        category = word[1]
                        symbol = word[2]
                        money = int(word[3])

                        print(create_table(list_expenses_advanced(expenses, category, symbol, money)).draw())
                    except ValueError as e:
                        print(str(e) + "\n")
                else:
                    print("Invalid command.\n")
            case "filter":
                if len(word) == 2:
                    try:
                        category = word[1]
                        filter_expenses_category(expenses, category, history)
                        print(f"Filtered expenses in category {category}.\n")
                    except ValueError as e:
                        print(str(e) + "\n")
                elif len(word) == 4:
                    try:
                        category = word[1]
                        symbol = word[2]
                        money = int(word[3])
                        filter_expenses_advanced(expenses, category, symbol, money, history)
                        print(f"Filtered expenses in category {category}, having the amount of money {symbol} {money} RON.\n")
                    except ValueError as e:
                        print(str(e) + "\n")
                else:
                    print("Invalid command.\n")
            case "undo":
                if len(word) == 1:
                    try:
                        undo_operation(expenses, history)
                        print("Reversed to the last operation.\n")
                    except IndexError as e:
                        print(str(e) + "\n")
                else:
                    print("Invalid command.\n")
            case "exit":
                if len(word) == 1:
                    return
                else:
                    print("Invalid commnad.\n")
            case _:
                print("Invalid command.\n")


def cmd_guide() -> None:
    print("In order to manage your expenses you need to use the following commands:\n\n" +
          "add <sum> <category> -> add to the current day an expense of <sum> RON for <category>\n" +
          "insert <day> <sum> <category> -> insert to day <day> a new expense of <sum> RON for <category>\n" +
          "remove <day> -> remove all expenses for day <day>\n" +
          "remove <start day> to <end day> -> remove all expenses between days <start day> and <end day>\n" +
          "remove <category> -> remove all expenses for <category>\n" +
          "list -> display all expenses\n" +
          "list <category> -> display all expenses for <category>\n" + 
          "list <category> [ < | = | > ] <value> -> display all expenses for <category> with an amount of money [ < | = | > ] to/than <value> RON\n" +
          "filter <category> -> keep only expenses in category <category>\n" +
          "filter <category> [ < | = | > ] <value> -> keep only expenses in category <category> with amount of money [ < | = | > ] to/than <value> RON\n" +
          "undo -> the last operation that modified program data is reversed\n\n" +
          "List of valid categories: housekeeping, food, transport, clothing, internet, others\n" +
          "The days of the expenses should be between 1 and 30.\n\n"
          "You can write commands below:\n")