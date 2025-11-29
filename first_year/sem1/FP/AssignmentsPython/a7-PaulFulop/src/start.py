from ui.ui_expenses import UI_Expenses
from domain.expense import Expense
import random

def generate_expenses(n:int):
    types = ["housekeeping", "food", "transport", "clothing", "internet", "others"]
    expenses = []
    for _ in range(n):
        expenses.append(Expense(random.randint(1, 30), random.randint(0, 1000), random.choice(types)))
    
    return expenses


def start_app():
    expenses = generate_expenses(10)
    ui = UI_Expenses(expenses)

    ui.display_commands()
    ui.start_menu()

if __name__ == "__main__":
    start_app()