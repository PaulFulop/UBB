from services import Services

class UI:
    hangman = "hangman"

    def __init__(self):
        self.__serv = Services("src/sentences.txt")
    
    @staticmethod
    def display_commands():
        print("1 -> add a new sentence\n"
              "2 -> start the game\n"
              "3 -> exit the game\n")
    
    def run(self):
        UI.display_commands()

        while True:
            cmd = input("> ")
            match cmd:
                case "1":
                    new_sentence = input("Insert the new sentence here: ")
                    try:
                        self.__serv.add_sentence(new_sentence)
                        print("New sentence was added.\n")
                    except Exception as e:
                        print(str(e) + '\n')
                case "2":
                    print(f"The sentence is: {self.__serv.sentence}\n")
                    game_over = False
                    letter = ""

                    while not game_over:
                        letter = input("Guess a letter: ")
                        if len(letter) != 1:
                            print("Invalid letter.It has to consist in only 1 character.\n")
                        else:
                            try:
                                self.__serv.fill_sentence(letter)
                                print(f"Sentence: {self.__serv.sentence} - {UI.hangman[:self.__serv.score]}\n")
                            except Exception as e:
                                print(f"Sentence: {self.__serv.sentence} - {UI.hangman[:self.__serv.score]}")
                                print(str(e) + '\n')
                                self.__serv.sentence = self.__serv.choose_sentence()
                                self.__serv.score = 0
                                game_over = True
                case "3":
                    print("Exiting...\n")
                    return
                case _:
                    print("Invalid command.\n")
