from game_init import GameInit
class UI:
    def __init__(self):
        self.game = GameInit(3)
    
    def run(self):
        while True:
            print(str(self.game.board) + "\n")

            try:
                tokens = input("> ").split()
                position = (int(tokens[0]), int(tokens[1]))
                self.game.order.make_move(position, tokens[2])
                self.game.chaos.make_move()
            except Exception as e:
                print(str(e) + '\n')

                if str(e) == "Chaos won!" or str(e) == "Order won!":
                    print(self.game.board)
                    return