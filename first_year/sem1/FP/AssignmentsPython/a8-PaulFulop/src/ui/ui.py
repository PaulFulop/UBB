import sys, os
sys.path.append("./src")
from services.student_services import StudentServices
from services.discipline_services import DisciplineServices
from services.grade_services import GradeServices
from domain.student import Student
from domain.discipline import Discipline
from domain.grade import Grade
from repository.repo_exceptions import InvalidGradeValueError, IDNotFoundError, DuplicateIDError, NegativeIDError

class UI:
    def __init__(self, stud_repo, disc_repo, grade_repo):
        self.__stud_serv = StudentServices(stud_repo, grade_repo)
        self.__disc_serv = DisciplineServices(disc_repo, grade_repo)
        self.__grade_serv = GradeServices(grade_repo, disc_repo, stud_repo)

    def main_menu(self):
        self.choose_menu()

    def stud_menu(self):
        message = "\n"
        while True:
            os.system("cls")
            self.display_stud_cmds()
            print(message)
            cmd = input("> ")
            match cmd:
                case "1":
                    try:
                        stud_id = int(input("Insert the id of the new student here: "))
                        stud_name = input("Insert the name of the new student here: ")

                        self.__stud_serv.add_stud(Student(stud_id, stud_name))
                        message = "The student has been added.\n"
                    except NegativeIDError as nie:
                        message = str(nie) + "\n"
                    except DuplicateIDError as die:
                        message = str(die) + "\n"
                    except ValueError as ve:
                        message = str(ve) + "\n"
                case "2":
                    try:
                        stud_id = int(input("Insert the id of the student here: "))
                        self.__stud_serv.remove_stud(stud_id)
                        message = f"The student with id {stud_id} has been removed.\n"
                    except IDNotFoundError as infe:
                        message = str(infe) + "\n"
                    except ValueError as ve:
                        message = str(ve) + "\n"
                case "3":
                    try:
                        stud_id = int(input("Insert the id of the student here: "))
                        new_name = input("Insert the new name of the student here: ")
                        self.__stud_serv.update_stud(stud_id, new_name)
                        message = f"The name of the student with id {stud_id} has been changed to {new_name}.\n"
                    except IDNotFoundError as infe:
                        message = str(infe) + "\n"
                    except ValueError as ve:
                        message = str(ve) + "\n"    
                case "4":
                    if not self.__stud_serv.list_students().rows:
                        message = "The list of students is currently empty.\n"
                    else:
                        message = str(self.__stud_serv.list_students()) + "\n"
                case "5":
                    try:
                        stud_id = int(input("Insert the id of the student here: "))
                        message = self.__stud_serv.search_stud_by_id(stud_id) + "\n"
                    except IDNotFoundError as infe:
                        message = str(infe) + "\n"
                    except ValueError as ve:
                        message = str(ve) + "\n" 
                case "6":
                    stud_name = input("Search for students by name: ")
                    if not self.__stud_serv.search_stud_by_name(stud_name).rows:
                        message = "No students mathcing with this name.\n"
                    else:
                        message = str(self.__stud_serv.search_stud_by_name(stud_name)) + "\n"
                case "7":
                    os.system("cls")
                    self.choose_menu()
                case "8":
                    print("Exiting...\n")
                    sys.exit()

    def disc_menu(self):
        message = "\n"
        while True:
            os.system("cls")
            self.display_disc_cmds()
            print(message)
            cmd = input("> ")
            match cmd:
                case "1":
                    try:
                        disc_id = int(input("Insert the id of the new discipline here: "))
                        disc_name = input("Insert the name of the new discipline here: ")

                        self.__disc_serv.add_disc(Discipline(disc_id, disc_name))
                        message = "The discipline has been added.\n"
                    except NegativeIDError as nie:
                        message = str(nie) + "\n"
                    except DuplicateIDError as die:
                        message = str(die) + "\n"
                    except ValueError as ve:
                        message = str(ve) + "\n"
                case "2":
                    try:
                        disc_id = int(input("Insert the id of the discipline here: "))
                        self.__disc_serv.remove_disc(disc_id)
                        message = f"The discipline with id {disc_id} has been removed.\n"
                    except IDNotFoundError as infe:
                        message = str(infe) + "\n"
                    except ValueError as ve:
                        message = str(ve) + "\n"
                case "3":
                    try:
                        disc_id = int(input("Insert the id of the discipline here: "))
                        new_name = input("Insert the new name of the discipline here: ")
                        self.__disc_serv.update_disc(disc_id, new_name)
                        message = f"The name of the discipline with id {disc_id} has been changed to {new_name}.\n"
                    except IDNotFoundError as infe:
                        message = str(infe) + "\n"
                    except ValueError as ve:
                        message = str(ve) + "\n"    
                case "4":
                    if not self.__disc_serv.list_disciplines().rows:
                        message = "The list of disciplines is currently empty.\n"
                    else:
                        message = str(self.__disc_serv.list_disciplines()) + "\n"
                case "5":
                    try:
                        disc_id = int(input("Insert the id of the student here: "))
                        message = self.__disc_serv.search_disc_by_id(disc_id) + "\n"
                    except IDNotFoundError as infe:
                        message = str(infe) + "\n"
                    except ValueError as ve:
                        message = str(ve) + "\n" 
                case "6":
                    disc_name = input("Search for disciplines by name: ")
                    if not self.__disc_serv.search_disc_by_name(disc_name).rows:
                        message = "No disciplines mathcing with this name.\n"
                    else:
                        message = str(self.__disc_serv.search_disc_by_name(disc_name)) + "\n"
                case "7":
                    os.system("cls")
                    self.choose_menu()
                case "8":
                    print("Exiting...\n")
                    sys.exit()

    def grades_menu(self):
        message = "\n"
        while True:
            os.system("cls")
            self.display_grades_cmds()
            print(message)
            cmd = input("> ")
            match cmd:
                case "1":
                    try:
                        disc_id = int(input("Insert the id of the discipline here: "))
                        stud_id = int(input("Insert the id of the student here: "))
                        grade = int(input("Insert the grade here: "))
                        self.__grade_serv.grade_student(Grade(disc_id, stud_id, grade))
                        message = f"The student with id {stud_id} has got a {grade} at discipline with id {disc_id}.\n"
                    except InvalidGradeValueError as igve:
                        message = str(igve) + "\n"
                    except IDNotFoundError as infe:
                        message = str(infe) + "\n"
                    except ValueError as ve:
                        message = str(ve) + "\n"
                case "2":
                    if not self.__grade_serv.list_grades().rows:
                        message = "The list of grades is currently empty.\n"
                    else:
                        message = str(self.__grade_serv.list_grades()) + "\n"
                case "3":
                    os.system("cls")
                    self.choose_menu()
                case "4":
                    print("Exiting...\n")
                    sys.exit()

    
    def choose_menu(self):
        data = self.startup_message()
        os.system("cls")

        match data.lower():
            case "s":
                self.stud_menu()
            case "d":
                self.disc_menu()
            case "g":
                self.grades_menu()
            case _:
                pass

    def startup_message(self):
        data = ""
        while data.lower() not in ["s", "d", "g"]:
            data = input("\nSelect which data you want to manage (s -> students, d -> disciplines, g -> grades): ")
            if data.lower() not in ["s", "d", "g"]:
                print(f"{data} is not a valid option.")
        return data
    
    def display_stud_cmds(self):
        print("List of commands for managing students data:\n\n"
              "1 -> Add a new student.\n"
              "2 -> Remove a student.\n"
              "3 -> Update the name of a student.\n"
              "4 -> List all students.\n"
              "5 -> Search for a student by id.\n"
              "6 -> Search for students by name.\n"
              "7 -> Select different data to manage.\n"
              "8 -> Exit the app.\n")
        
    def display_disc_cmds(self):
        print("List of commands for managing disciplines data:\n\n"
              "1 -> Add a new discipline.\n"
              "2 -> Remove a discipline.\n"
              "3 -> Update the name of a discipline.\n"
              "4 -> List all disciplines.\n"
              "5 -> Search for a discipline by id.\n"
              "6 -> Search for disciplines by name.\n"
              "7 -> Select different data to manage.\n"
              "8 -> Exit the app.\n")
        
    def display_grades_cmds(self):
        print("List of commands for managing grades:\n\n"
              "1 -> Assign grade at a certain discipline to a student.\n"
              "2 -> List all grades for all students.\n"
              "3 -> Select different data to manage.\n"
              "4 -> Exit the app.\n")