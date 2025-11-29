import sys
sys.path.append("./src")
from domain.student import Student

class ExamRepo():
    def __init__(self):
        self.__data = []

    def add(self, new_stud:Student):
        """Adds a new student to the repo.

        :param new_stud: The new student to add.
        :type new_stud: Student
        :raises ValueError: If the new students has a non-unique id.
        """
        self.__load()
        for stud in self.__data:
            if stud.id == new_stud.id:
                raise ValueError(f"ID {stud.id} already exists.")

        self.__data.append(new_stud)
        self.__save()

    def list_students(self):
        self.__load()
        return self.__data

    def update_grades(self, p:int, b:int):
        self.__load()

        for stud in self.__data:
            if stud.attendance_count >= p:
                if stud.grade + b > 10:
                    stud.grade = 10
                else:
                    stud.grade += b

        self.__save()
                

    def __load(self):
        self.__data.clear()
        with open("src/repo/students.txt", "rt") as file:
            lines = file.readlines()
            for line in lines:
                tokens = line.split(',')
                self.__data.append(Student(int(tokens[0].strip()), tokens[1].strip(), int(tokens[2].strip()), int(tokens[3].strip().removesuffix('\n'))))

    def __save(self):
        with open("src/repo/students.txt", "wt") as file:
            for stud in self.__data:
                file.write(str(stud) + '\n')