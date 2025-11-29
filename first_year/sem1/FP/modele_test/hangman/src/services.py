from repo import Repo, Sentence
import random

class Services:
    def __init__(self, file_path:str):
        self.__repo = Repo(file_path)
        self.sentence = self.choose_sentence()
        self.score = 0
    
    def add_sentence(self, new_sentence:str):
        """adds a new sentence in the text file

        :param new_sentence: the new sentence to add
        :type new_sentence: str
        """
        self.__repo.add(new_sentence)

    def choose_sentence(self):
        return random.choice(self.__repo.data)

    def fill_sentence(self, letter:str):
        if not self.sentence.verify_present_letter(letter):
            self.score += 1
            if self.score == 7:
                raise ValueError("You lost!")
        else:
            self.sentence.place_letters(letter)
            if self.sentence.verify_complete_word():
                raise ValueError("You won!")