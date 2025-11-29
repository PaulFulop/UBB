import sys
sys.path.append("./src")
from domain.expense import Expense
from repository.memory_repo import ExpenseMemoryRepository
import json

class ExpenseJsonRepository(ExpenseMemoryRepository):
    def __init__(self, initial_list:list):
        if self.__file_empty() == True:
            super().__init__(initial_list)
            self.__save()
        else:
            self.__load()
            self._history = [self._data[:]]
    
    def add(self, new_expense:Expense):
        super().add(new_expense)
        self.__save()
    
    def filter(self, value:int):
        super().filter(value)
        self.__save()
    
    def undo(self):
        super().undo()
        self.__save()
    
    def __file_empty(self):
        try:
            file = open("src/repository/expenses.json", "r")
            if file.read().strip() == "":
                file.close()
                return True
            file.close()
            return False
        except FileNotFoundError as fnfe:
            print(fnfe)

    def __save(self):
        try:
            file = open("src/repository/expenses.json", "w")
            list = []

            for exp in self._data:
                list.append({"day": exp.day, "money": exp.money, "type": exp.type})
            
            json.dump(list, file, indent=4)
            file.close()
        except FileNotFoundError as fnfe:
            print(fnfe)
    
    def __load(self):
        try:
            expenses = []
            file = open("src/repository/expenses.json", "r")
            lines = json.load(file)
            for line in lines:
                line = str(line)
                line = line.replace("'", '"')
                data = json.loads(line)
                expenses.append(Expense(data["day"], data["money"], data["type"]))

            self._data = expenses[:]
            file.close()
        except FileNotFoundError as fnfe:
            print(fnfe)