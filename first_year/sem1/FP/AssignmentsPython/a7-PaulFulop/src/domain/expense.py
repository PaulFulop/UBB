class Expense:
    def __init__(self, day:int, amount:int, type:str):
        if day not in range(1, 31):
            raise ValueError("Invalid day.")

        if amount < 0:
            raise ValueError("Amount of money can't be negative.")
        
        if type not in ["housekeeping", "food", "transport", "clothing", "internet", "others"]:
            raise ValueError("Invalid type.")

        self.__day = day
        self.__amount = amount
        self.__type = type
    
    @property
    def day(self):
        return self.__day

    @property
    def money(self):
        return self.__amount

    @property
    def type(self):
        return self.__type

    def __str__(self):
        return f"day {self.day}, amount {self.__amount}, type {self.type}."