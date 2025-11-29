
class Sentence:
    def __init__(self, text:str):
        self.text = text
        self.h_text = self.hidden_text()
        self.remaining_letters = []
        self.get_letters()

    def hidden_text(self):
        h_txt = ""
        words = self.text.split()
        letters = [word[0] for word in words] + [word[-1] for word in words]

        for l in self.text:
            if l not in letters and l != ' ':
                h_txt += "_"
            else:
                h_txt += l
        return h_txt
    
    def get_letters(self):
        self.remaining_letters.clear()
        for i in range(len(self.text)):
            if self.h_text[i] == '_':
                self.remaining_letters.append(self.text[i])
    
    def place_letter(self, pos:int):
        if pos < 0 or pos > len(self.text):
            raise ValueError
        
        text_cpy1 = self.h_text[:pos]
        text_cpy2 = self.h_text[pos+1:]

        self.h_text = text_cpy1
        self.h_text += self.text[pos]
        self.h_text += text_cpy2
        self.remaining_letters.remove(self.text[pos])
    
    def verify_complete_word(self):
        return self.h_text == self.text

    def verify_present_letter(self, letter:str):
        return letter in self.remaining_letters
    
    def place_letters(self, letter:str):
        for i in range(len(self.text)):
            if self.text[i] == letter:
                self.place_letter(i)

    def __str__(self):
        return self.h_text
