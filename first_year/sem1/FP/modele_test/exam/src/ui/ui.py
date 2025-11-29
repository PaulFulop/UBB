import sys
sys.path.append("./src")
from domain.student import Student
from services.exam_services import ExamServices

class UI:
    def __init__(self):
        self.__serv = ExamServices()
    
    @staticmethod
    def display_commands():
        print("List of commands:\n"
              "1 -> add a new student\n"
              "2 -> display all students decreasing by grade or alphabetically if grades are equal\n"
              "3 -> give bonuses to all students having at least some amount of attendances\n"
              "4 -> find all students having a certain string in their name\n"
              "5 -> exit\n")
        
    def run(self):
        UI.display_commands()

        while True:
            cmd = input("> ")
            match cmd:
                case "1":
                    id = input("Insert the id here: ")
                    name = input("Insert the name here: ")
                    att_count = input("Insert the attedance count here: ")
                    grade = input("Insert the grade here: ")

                    try:
                        new_stud = Student(int(id), name, int(att_count), int(grade))
                        self.__serv.add_stud(new_stud)
                        print("New student was added.")
                    except Exception as e:
                        print(str(e) + '\n')
                case "2":
                    print(self.__serv.list_students())
                case "3":
                    p = input("Insert the minimum number of attendances here: ")
                    b = input("Insert the number of bonus points here: ")

                    try:
                        self.__serv.give_bonus(int(p), int(b))
                        print("The bonuses were given.")
                    except Exception as e:
                        print(str(e) + '\n')
                case "4":
                    string = input("Insert a string here: ")
                    print(self.__serv.find_students(string))
                case "5":
                    print("Exiting...\n")
                    return
                case _:
                    print("Invalid data.\n")