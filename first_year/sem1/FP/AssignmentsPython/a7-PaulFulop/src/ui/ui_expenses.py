import sys
import os
sys.path.append("./src")
from services.expense_services import ExpenseServices
from domain.expense import Expense

class UI_Expenses:
    def __init__(self, expenses:list):
        self.__expense_services = ExpenseServices(expenses)
    
    def display_commands(self):
        print("\nList of commands:\n\n"
              "1 -> add a new expense\n"
              "2 -> display the list of expenses\n"
              "3 -> filter the list so that it contains only expenses above a certain value\n"
              "4 -> undo the last operation that modified the list of expenses\n"
              "5 -> exit\n")
        
    def display_expenses(self):
        print(self.__expense_services.display_expenses())
    
    def start_menu(self):
        app_running = True
        message = str()
        while app_running:
            n = input("> ")
            match n:
                case "1":
                    try:
                        day = int(input("Insert the day in which the new expense was made here: "))
                        money = int(input("Insert the amount of money for the new expense here: "))
                        type = input("Insert the type of the expense here: ")

                        self.__expense_services.add_expense(day, money, type)
                        self.display_commands()
                        message = "The new expense was added."
                    except ValueError as ve:
                        message = str(ve)
                case "2":
                    message = self.__expense_services.display_expenses()
                case "3":
                    try:
                        value = int(input("Insert the value of money used to filter the list of expenses here: "))

                        self.__expense_services.filter_expenses(value)
                        message = "The expenses list was filtered."
                    except ValueError as ve:
                        message = str(ve)
                case "4":
                    try:
                        self.__expense_services.undo_expenses()
                        message = "The last operation has been reverted."
                    except IndexError as ie:
                        message = str(ie)
                case "5":
                    message = "Exiting app..."
                    app_running = False
                case _:
                    message = "Invalid command."

            os.system("cls")
            self.display_commands()
            print(message + "\n")
