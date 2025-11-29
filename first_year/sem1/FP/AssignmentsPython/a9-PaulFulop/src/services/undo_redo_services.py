class UndoError(Exception):
    def __init__(self):
        super().__init__("No more undos.")

class RedoError(Exception):
    def __init__(self):
        super().__init__("No more redos.")

class FunctionCall:
    def __init__(self, function_name, *function_params):
        self.__function_name = function_name
        self.__function_params = function_params

    def call(self):
        self.__function_name(*self.__function_params)

    def __call__(self, *args, **kwds):
        self.call()   

class CascadeCommand:
    def __init__(self):
        self.__undo_function = []
        self.__redo_function = []

    def add_undo_function(self, undo_function: FunctionCall):
        self.__undo_function.append(undo_function)

    def add_redo_function(self, redo_function: FunctionCall):
        self.__redo_function.append(redo_function)

    def undo(self):
        for func in self.__undo_function:
            func()
    
    def redo(self):
        for func in self.__redo_function:
            func()

class Command:
    def __init__(self, undo_function:FunctionCall, redo_function:FunctionCall):
        self.__undo_function = undo_function
        self.__redo_function = redo_function
        
    def undo(self):
        self.__undo_function()
    
    def redo(self):
        self.__redo_function()

class UndoRedoServices:
    def __init__(self):
        self.__undo_stack = []
        self.__redo_stack = []
    
    def record(self, command:Command):
        self.__undo_stack.append(command)
        self.__redo_stack.clear()
    
    def undo(self):
        if len(self.__undo_stack) == 0:
            raise UndoError
        
        current_command = self.__undo_stack.pop()
        current_command.undo()
        self.__redo_stack.append(current_command)

    def redo(self):
        if len(self.__redo_stack) == 0:
            raise RedoError
        
        current_command = self.__redo_stack.pop()
        current_command.redo()
        self.__undo_stack.append(current_command)