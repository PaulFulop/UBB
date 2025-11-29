from services import Services

class UI:
    def __init__(self, board_size:int, num_apples:int):
        self.__services = Services(board_size, num_apples)
        self.__current_dir = 1
    
    def start(self):
        game_over = False
        while not game_over:
            self.redraw_board()
            cmd = input("> ")
            tokens = cmd.split()

            match tokens[0].lower().strip():
                case "move":
                    if len(tokens) == 2:
                        try:
                            n = int(tokens[1])
                            self.__services.move(0, n)
                        except ValueError:
                            print("Game Over")
                            game_over = True
                    elif len(tokens) == 1:
                        try:
                            self.__services.move(0, 1)
                        except ValueError:
                            print("Game Over")
                            game_over = True  
                    else:
                        print("Invalid command.\n")
                case "up":
                    if self.__current_dir == 3:
                        print("Cannot rotate 180 degrees.\n")
                    else:
                        self.__current_dir = 1
                        try:
                            self.__services.move(self.__current_dir, 1)  
                        except ValueError:
                            print("Game Over")
                            game_over = True
                case "right":
                    if self.__current_dir == 4:
                        print("Cannot rotate 180 degrees.\n")
                    else:
                        self.__current_dir = 2
                        try:
                            self.__services.move(self.__current_dir, 2)  
                        except ValueError:
                            print("Game Over")
                            game_over = True
                case "down":
                    if self.__current_dir == 1:
                        print("Cannot rotate 180 degrees.\n")
                    else:
                        self.__current_dir = 3
                        try:
                            self.__services.move(self.__current_dir, 3)  
                        except ValueError:
                            print("Game Over")
                            game_over = True 
                case "left":
                    if self.__current_dir == 2:
                        print("Cannot rotate 180 degrees.\n")
                    else:
                        self.__current_dir = 4
                        try:
                            self.__services.move(self.__current_dir, 4)  
                        except ValueError:
                            print("Game Over")
                            game_over = True
                case _:
                    print("Invalid command.\n")
    
    def redraw_board(self):
        self.__services.mark_board()
        print(self.__services.board)
        print('\n')