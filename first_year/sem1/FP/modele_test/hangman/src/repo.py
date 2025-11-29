from sentence import Sentence

class Repo:
    def __init__(self, file_path:str):
        self.file_path = file_path
        self.data = []
        self.__load()
    
    def add(self, new_sentence:str):
        """adds a new sentence to the text file and updates the data

        :param new_sentence: the new sentence to add
        :raises ValueError: if the length of a word in the sentence is not greater than 3
        :raises ValueError: if the sentence already exists
        """

        words = new_sentence.split()
        for word in words:
            if len(word.strip()) < 3:
                raise ValueError("Invalid sentence.")
        
        for sentence in self.data:
            if sentence.text == new_sentence:
                raise ValueError("Duplicate sentence.")

        self.data.append(Sentence(new_sentence))
        self.__save()
    
    def __save(self):
        try:
            with open(self.file_path, "wt") as file:
                for sentence in self.data:
                    file.write(sentence.text + '\n')
        except FileNotFoundError:
            pass

    def __load(self):
        self.data.clear()
        try:
            with open(self.file_path, "rt") as file:
                lines = file.readlines()
                for line in lines:
                    self.data.append(Sentence(line.removesuffix('\n')))
        except FileNotFoundError:
            pass