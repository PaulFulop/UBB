# Service for the score repository

import sys
sys.path.append("./src")
from repository.score_repo import ScoreRepo

class ScoreService:
    def __init__(self, file_path:str):
        """Class onstructor. Will create a ScoreRepo object that loads data from the txt file located at file_path upon calling. 

        :param file_path: path to the desired file
        :type file_path: str
        """
        self.__score_repo = ScoreRepo(file_path)
    
    def list_score(self):
        """Loads the data from the score_repo and returns it

        :return: list having 2 int values -> human points (how many times the human won), ai points (how many times the computer won)  
        :rtype: list
        """
        return self.__score_repo.data
    
    def update_score(self, flag:bool):
        """In case one players wins, the score will be updated according to the value of the flag

        :param flag: Used for deciding where the score should be updated
                  (+1 for human if flag = False, +1 for computer if flag = True)
        :type flag: bool
        """
        self.__score_repo.update_score(flag)