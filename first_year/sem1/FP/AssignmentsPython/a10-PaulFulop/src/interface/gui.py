# For playing on a custom window 

import sys, pygame
sys.path.append("./src")
from services.game_init import GameInit, Players
from game_exceptions import GameOverError

class GUI:
    WHITE = (255, 255, 255)
    BACKGROUND_COLOR = (40, 44, 52)
    TABLE_COLOR = 33, 35, 41
    TEXT_COLOR = (173, 172, 172)
    HOVER_COLOR = (138, 136, 136)
    BLUE = (60, 133, 181)
    RED = (186, 17, 17)
    ORANGE = (235, 125, 52)
    GREEN = (80, 163, 83)
    BORDER_COLOR = (32, 34, 36)
    LIGHT_GREY = (212, 210, 217)

    screen_width = 850
    screen_height = 560
    startX, startY = 25, 40
    cell_size = 80
    dist = 40

    def __init__(self, firstPlayer:Players, difficulty:int):
        pygame.init()
        icon = pygame.image.load("src/explosion.png")
        pygame.display.set_icon(icon)
        pygame.display.set_caption("Obliteration Game")

        self.__game = GameInit(firstPlayer, difficulty)
        self.__screen = pygame.display.set_mode((GUI.screen_width, GUI.screen_height))
        self.__start_button_rect = pygame.Rect(6 * GUI.cell_size + GUI.startX + GUI.dist, 4 * GUI.cell_size + GUI.startY + 9, GUI.screen_width - 6 * GUI.cell_size - GUI.startX - 2 * GUI.dist, GUI.cell_size)
        self.__quit_button_rect = pygame.Rect(6 * GUI.cell_size + GUI.startX + GUI.dist, 5 * GUI.cell_size + GUI.startY + 12, GUI.screen_width - 6 * GUI.cell_size - GUI.startX - 2 * GUI.dist, GUI.cell_size)
        self.__turn_rect = pygame.Rect(6 * GUI.cell_size + GUI.startX + GUI.dist, 2 * GUI.cell_size + GUI.startY + 3, GUI.screen_width - 6 * GUI.cell_size - GUI.startX - 2 * GUI.dist, GUI.cell_size)
        self.__difficulty_rect = pygame.Rect(6 * GUI.cell_size + GUI.startX + GUI.dist, GUI.cell_size + GUI.startY, GUI.screen_width - 6 * GUI.cell_size - GUI.startX - 2 * GUI.dist, GUI.cell_size)
        self.__difficulty = difficulty
        self.__font = pygame.font.Font('src/JetBrainsMono-Bold.ttf', 25)

    def display_board(self):
        font = pygame.font.Font('src/JetBrainsMono-Bold.ttf', 50) # font that we have to use for writing on the board
        for row in range(6):
            for col in range(6):
                rect = pygame.Rect(GUI.startX + col * (GUI.cell_size + 3), GUI.startY + row * (GUI.cell_size + 3), GUI.cell_size, GUI.cell_size)
                pygame.draw.rect(self.__screen, GUI.BORDER_COLOR, rect, 3, 17)
                
                color = None
                match self.__game.board[row, col]:
                    case 'X':
                        color = GUI.BLUE
                    case 'O':
                        color = GUI.RED
                    case '*':
                        color = GUI.LIGHT_GREY
                    case _:
                        color = (255, 255, 255)
                text = font.render(self.__game.board[row, col], True, color, None)
                text_rect = text.get_rect()
                text_rect.center = rect.center
                self.__screen.blit(text, text_rect)

    def display_human_move(self, x:int, y:int):
        self.__game.human.make_move(x, y)
        self.__game.state.record_state(self.__game.board, False)
    
    def display_computer_move(self):
        self.__game.computer.make_move()
        self.__game.state.record_state(self.__game.board, True)
    
    def display_score(self, x:float, y:float):
        rect1 = pygame.Rect(x, y, 1.5 * GUI.cell_size, GUI.cell_size / 2)
        rect2 = pygame.Rect(x + rect1.width, y, 2 * GUI.cell_size, GUI.cell_size / 2)
        pygame.draw.line(self.__screen, GUI.TABLE_COLOR, (rect1.x + rect1.width, rect1.y), (rect1.x + rect1.width, rect1.y + GUI.cell_size), 4)
        pygame.draw.line(self.__screen, GUI.TABLE_COLOR, (x, y + rect2.height), (rect2.x + rect2.width, y + rect2.height), 4)

        if self.__game.flag == False:
            h_color, c_color = GUI.RED, GUI.BLUE
        else:
            h_color, c_color = GUI.BLUE, GUI.RED

        # displaying human
        text = self.__font.render("human", True, h_color, None)
        text_rect = text.get_rect()
        text_rect.center = rect1.center
        self.__screen.blit(text, text_rect)

        # displaying computer
        text = self.__font.render("computer", True, c_color, None)
        text_rect = text.get_rect()
        text_rect.center = rect2.center
        self.__screen.blit(text, text_rect)

        tokens = self.__game.state.score_serv.list_score()
        h_points, c_points = tokens[0], tokens[1]
        rect1.y += 0.5 * GUI.cell_size 
        rect2.y += 0.5 * GUI.cell_size 

        # displaying human score
        text = self.__font.render(f"{h_points}", True, GUI.TEXT_COLOR, None)
        text_rect = text.get_rect()
        text_rect.center = rect1.center
        self.__screen.blit(text, text_rect)

        # displaying computer score
        text = self.__font.render(f"{c_points}", True, GUI.TEXT_COLOR, None)
        text_rect = text.get_rect()
        text_rect.center = rect2.center
        self.__screen.blit(text, text_rect)
    
    def run(self):
        turn = self.__game.flag
        game_started = False
        
        start_text = self.__font.render("START", True, GUI.TEXT_COLOR, None)
        start_text_rect = start_text.get_rect()
        start_text_rect.center = self.__start_button_rect.center

        quit_text = self.__font.render("QUIT", True, GUI.TEXT_COLOR, None)
        quit_text_rect = quit_text.get_rect()
        quit_text_rect.center = self.__quit_button_rect.center

        diff_text = self.__font.render("Difficulty:", True, GUI.TEXT_COLOR, None)

        match self.__difficulty:
            case 1:
                diff_mode = self.__font.render("easy", True, GUI.GREEN, None)
            case 2:
                diff_mode = self.__font.render("medium", True, GUI.ORANGE, None)
            case _:
                diff_mode = self.__font.render("hard", True, GUI.RED, None)


        human_turn_text = self.__font.render("Your turn.", True, GUI.TEXT_COLOR, None)
        human_turn_text_rect = human_turn_text.get_rect()
        human_turn_text_rect.center = self.__turn_rect.center

        computer_turn_text = self.__font.render("Computer's turn.", True, GUI.TEXT_COLOR, None)
        computer_turn_text_rect = computer_turn_text.get_rect()
        computer_turn_text_rect.center = self.__turn_rect.center

        computer_win_text = self.__font.render("The computer won!", True, GUI.RED, None)
        computer_win_text_rect = computer_win_text.get_rect()
        computer_win_text_rect.center = self.__turn_rect.center

        human_win_text = self.__font.render("You won!", True, GUI.GREEN, None)
        human_win_text_rect = human_win_text.get_rect()
        human_win_text_rect.center = self.__turn_rect.center

        start_button_pressed, quit_button_pressed = False, False
        human_win, computer_win = False, False

        while True:
            self.__screen.fill(GUI.BACKGROUND_COLOR)
            self.display_board()
            self.display_score(6 * GUI.cell_size + GUI.startX + GUI.dist, GUI.startY)

            if quit_text_rect.collidepoint(pygame.mouse.get_pos()):
                pygame.mouse.set_cursor(pygame.SYSTEM_CURSOR_HAND)
                quit_text = self.__font.render("QUIT", True, GUI.HOVER_COLOR, None)
                quit_button_pressed = True
            else:
                if not start_button_pressed:
                    pygame.mouse.set_cursor(pygame.SYSTEM_CURSOR_ARROW)
                quit_text = self.__font.render("QUIT", True, GUI.TEXT_COLOR, None)  
                quit_button_pressed = False

            if not game_started:
                if start_text_rect.collidepoint(pygame.mouse.get_pos()):
                    pygame.mouse.set_cursor(pygame.SYSTEM_CURSOR_HAND)
                    start_text = self.__font.render("START", True, GUI.HOVER_COLOR, None)
                    start_button_pressed = True
                else:
                    if not quit_button_pressed:
                        pygame.mouse.set_cursor(pygame.SYSTEM_CURSOR_ARROW)
                    start_text = self.__font.render("START", True, GUI.TEXT_COLOR, None)
                    start_button_pressed = False
            else:
                if not turn:
                    mouseX, mouseY = pygame.mouse.get_pos()
                    mouseX -= GUI.startX  
                    mouseY -= GUI.startY
                    mouseX //= GUI.cell_size
                    mouseY //= GUI.cell_size

                    if (mouseY,mouseX) in self.__game.board.free_cells:
                        pygame.mouse.set_cursor(pygame.SYSTEM_CURSOR_HAND)
                    else:
                        if not quit_button_pressed:
                            pygame.mouse.set_cursor(pygame.SYSTEM_CURSOR_ARROW)

                    self.__screen.blit(human_turn_text, human_turn_text_rect)
                else:
                    self.__screen.blit(computer_turn_text, computer_turn_text_rect)

            if computer_win:
                self.__screen.blit(computer_win_text, computer_win_text_rect)
            elif human_win:
                self.__screen.blit(human_win_text, human_win_text_rect)
            
            self.__screen.blit(diff_text, (self.__difficulty_rect.x, self.__difficulty_rect.centery))
            self.__screen.blit(diff_mode, (self.__difficulty_rect.centerx + GUI.dist, self.__difficulty_rect.centery))
            self.__screen.blit(start_text, start_text_rect)
            self.__screen.blit(quit_text, quit_text_rect)

            pygame.display.update()

            if turn and game_started:
                try:
                    self.display_computer_move()
                    turn = not turn 
                    pygame.event.clear() 
                except GameOverError:
                    turn = self.__game.flag
                    game_started = False
                    computer_win = True

            for event in pygame.event.get():
                if event.type == pygame.QUIT: 
                    return
                
                if event.type == pygame.MOUSEBUTTONDOWN:
                    if event.button == 1:
                        if game_started and not turn:
                            posX, posY = event.pos
                            posX -= GUI.startX  
                            posY -= GUI.startY
                            posX //= GUI.cell_size
                            posY //= GUI.cell_size
                            try:
                                self.display_human_move(posY, posX)
                                turn = not turn
                                print("Left-click detected at", posY, posX)
                            except GameOverError:
                                turn = self.__game.flag
                                game_started = False
                                human_win = True
                            except Exception as e:
                                print(str(e))
                        elif not game_started:
                            if start_text_rect.collidepoint(event.pos):
                                self.__game.clear_board()
                                game_started = True
                                human_win, computer_win = False, False
                                start_text = self.__font.render("START", True, GUI.TEXT_COLOR, None) 

                        if quit_text_rect.collidepoint(event.pos):
                            return

                        pygame.mouse.set_cursor(pygame.SYSTEM_CURSOR_ARROW)
