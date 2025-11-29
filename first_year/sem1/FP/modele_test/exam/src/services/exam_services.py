import sys
sys.path.append("./src")
from domain.student import Student
from repo.exam_repo import ExamRepo


class ExamServices:
    def __init__(self):
        self.__repo = ExamRepo()
    
    def add_stud(self, new_stud:Student):
        """Adds a new student.

        :param new_stud: The new student to add.
        :type new_stud: Student
        """
        self.__repo.add(new_stud)

    def list_students(self):
        students = self.__repo.list_students()

        for i in range(len(students) - 1):
            for j in range(i + 1, len(students)):
                if students[i].grade < students[j].grade:
                    students[i], students[j] = students[j], students[i]
                elif students[i].grade == students[j].grade:
                    if students[i].name > students[j].name:
                        students[i], students[j] = students[j], students[i]
        text = ""
        for stud in students:
            text += str(stud) + '\n'
        return text

    def give_bonus(self, p:int, b:int):
        self.__repo.update_grades(p, b)

    def find_students(self, string:str):
        filtered_studs = []
        students = self.__repo.list_students()
        for stud in students:
            if string.strip().lower() in stud.name.strip().lower():
                filtered_studs.append(stud)

        for i in range(len(filtered_studs) - 1):
            for j in range(i + 1, len(filtered_studs)):
                if filtered_studs[i].name > filtered_studs[j].name:
                    filtered_studs[i], filtered_studs[j] = filtered_studs[j], filtered_studs[i]
        
        text = ""
        for stud in filtered_studs:
            text += str(stud) + '\n'
        return text