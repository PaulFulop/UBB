# For playing in the console

import sys, os, time
sys.path.append("./src")
from services.game_init import GameInit, Players
from prettytable import PrettyTable
from game_exceptions import GameOverError
from rich.console import Console

class UI:
    def __init__(self, firstPlayer:Players, difficulty:int):
        self.__game = GameInit(firstPlayer, difficulty)
        self.__first_player_info = "(you will play first)" if self.__game.flag == False else "(the computer will play first)"
        self.__console = Console()
        
        match difficulty:
            case 1:
                self.__difficulty_mode = "[bold #50a353]easy[/bold #50a353]"
            case 2:
                self.__difficulty_mode = "[bold #eb7d34]medium[/bold #eb7d34]"
            case _:
                self.__difficulty_mode = "[bold red]hard[/bold red]"

    def display_commands(self):
        self.__console.print("[bold underline #327fc7]OBSTRUCTION[/bold underline #327fc7]\n\n"
              "List of commands:\n\n"
              f"start -> start a new round {self.__first_player_info}\n"
              "score -> show the score\n"
              "exit -> exit the game\n\n"
              f"Difficulty: {self.__difficulty_mode}\n") 
    
    @staticmethod
    def clear_console():
        os.system("cls")

    def redraw_console(self, message:str):
        UI.clear_console()
        self.display_commands()
        self.__console.print(message + '\n')

    def redraw_board(self):
        UI.clear_console()
        self.display_commands()
        print(str(self.__game.board) + '\n')

    def display_human_move(self):
        self.redraw_board()
        pos = input("Insert the position you want to mark here: ")
        tokens = pos.split()
        x = int(tokens[0].strip())
        y = int(tokens[1].strip())
        self.__game.human.make_move(x, y)
        self.__game.state.record_state(self.__game.board, False)

    def display_computer_move(self):
        self.redraw_board()
        with self.__console.status("Computer thinking..."):
            self.__game.computer.make_move()

        self.__game.state.record_state(self.__game.board, True)
    
    def run(self):
        message = ""
        should_redraw = True

        while True:
            if should_redraw == True:
                self.redraw_console(message)
            else:
                should_redraw = True
            cmd = input("> ")

            match cmd.lower().strip():
                case "start":
                    if self.__game.flag == False:
                        while True:
                            try:
                                self.display_human_move()
                                self.display_computer_move()
                            except GameOverError as goe:
                                self.redraw_board()

                                wl_color = "#50a353" if str(goe).split()[0].strip() == "You" else "#e83b35"
                                self.__console.print(f"[bold {wl_color}]{goe}\n[/bold {wl_color}]")

                                self.__game.clear_board()
                                should_redraw = False
                                break
                            except Exception as e:
                                self.__console.print(f"[bold red]{e}[/bold red]")
                                time.sleep(2.25)
                    else:
                        while True:
                            try:
                                self.display_computer_move()
                                self.display_human_move()
                            except GameOverError as goe:
                                self.redraw_board()

                                wl_color = "#50a353" if str(goe).split()[0].strip() == "You" else "#e83b35"
                                self.__console.print(f"[bold {wl_color}]{goe}\n[/bold {wl_color}]")

                                self.__game.clear_board()
                                should_redraw = False
                                break
                            except Exception as e:
                                self.__console.print(f"[bold red]{e}[/bold red]")
                                time.sleep(2.25)
                                while True:
                                    try:
                                        self.display_human_move()
                                        break
                                    except Exception as e:
                                        self.__console.print(f"[bold red]{e}[/bold red]")
                                        time.sleep(2.25)
                case "score":
                    try:
                        tokens = self.__game.state.score_serv.list_score()
                        h_points, c_points = tokens[0], tokens[1]
                        
                        table = PrettyTable(("human", "computer"))
                        table.add_row([h_points, c_points])
                        message = str(table)
                    except ValueError as ve:
                        message = f"[red bold]{str(ve)}[/red bold]"
                case "exit":
                    self.__console.print("[bold #144575]Exiting...\n[/bold #144575]")
                    break
                case _:
                    message = "[bold red]Invalid command.[/bold red]"