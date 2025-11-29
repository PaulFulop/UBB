import sys
import pymssql
sys.path.append("./src")
from domain.expense import Expense
from repository.memory_repo import ExpenseMemoryRepository

class ExpenseDataBaseRepository(ExpenseMemoryRepository):
    def __init__(self, initial_list:list, server:str, username:str, password:str, database:str, table_name:str):
        super().__init__(initial_list)
        self.__server = server
        self.__user = username
        self.__password = password
        self.__database = database
        self.__table = table_name

        conn = self.connect()
        cursor = conn.cursor()
        cursor.execute("SELECT COUNT(*) FROM ExpensesTable")
        length = cursor.fetchone()[0]

        if not length:
            for exp in self._data:
                cursor.execute(f"INSERT INTO {self.__table} VALUES (%s, %s, %s)", [exp.day, exp.money, exp.type])
                conn.commit()
        else:  
            self.__load()

        cursor.close()
        conn.close()
    
    def connect(self):
        connection = pymssql.connect(server=self.__server, user=self.__user, password=self.__password, database=self.__database)
        return connection

    def add(self, new_expense:Expense):
        super().add(new_expense)
        conn = self.connect()
        cursor = conn.cursor()

        cursor.execute(f"INSERT INTO {self.__table} VALUES (%s, %s, %s)", [new_expense.day, new_expense.money, new_expense.type])
        conn.commit()
        cursor.close()
        conn.close()
    
    def filter(self, value:int):
        super().filter(value)
        conn = self.connect()
        cursor = conn.cursor()

        cursor.execute(f"DELETE FROM {self.__table} WHERE money <= %s", [value])
        conn.commit()
        cursor.close()
        conn.close()
    
    def undo(self):
        super().undo()
        conn = self.connect()
        cursor = conn.cursor()
        cursor.execute(f"DELETE FROM {self.__table}")

        for exp in self._data:
            cursor.execute(f"INSERT INTO {self.__table} VALUES (%s, %s, %s)", [exp.day, exp.money, exp.type])
        conn.commit()
        cursor.close()
        conn.close()
    
    def __load(self):
        expenses = []
        conn = self.connect()
        cursor = conn.cursor(as_dict=True)
        cursor.execute(f"SELECT * FROM {self.__table}")

        for line in cursor:
            expenses.append(Expense(line["day"], line["money"], line["type"].strip()))
        
        self._data = expenses[:]
