import sys
sys.path.append("./src")

from prettytable import PrettyTable

class StudentsRegisterManagementServices():
    def __init__(self, stud_repo, disc_repo, grade_repo):
        self.__stud_repo = stud_repo
        self.__disc_repo = disc_repo
        self.__grade_repo = grade_repo
    
    def list_failing_students(self):
        failing_stud_ids = []

        for grade in self.__grade_repo.data:
            if grade.grade < 5:
                failing_stud_ids.append(grade.stud_id)
                
        table = self.__initialize_table(["ID", "Student name", "Failed disciplines"])
        for stud_id in failing_stud_ids:
            table.add_row([stud_id, self.__stud_repo.find_by_id(stud_id).name, self.failing_disciplines(stud_id)], divider=True)
        
        if not table.rows:
            return "no failing students"
        return table
    
    def list_best_students_descending(self):        
        stud_ids = []
        stud_ids.extend(self.__stud_repo.data.keys())

        for i in range(len(stud_ids) - 1):
            for j in range(i + 1, len(stud_ids)):
                if self.aggregated_average(stud_ids[i]) < self.aggregated_average(stud_ids[j]):
                    stud_ids[i], stud_ids[j] = stud_ids[j], stud_ids[i]

        table = self.__initialize_table(["ID", "Student name", "Aggregate Average"])
        for stud_id in stud_ids:
            agg_avg = self.aggregated_average(stud_id)
            if agg_avg == 0:
                table.add_row([stud_id, self.__stud_repo.find_by_id(stud_id).name, "no grades given"])
            else:
                table.add_row([stud_id, self.__stud_repo.find_by_id(stud_id).name, agg_avg])
        
        if not table.rows:
            return "no students / no grades for any student"
        return table
    

    def list_active_disciplines_descending(self):
        active_disciplines = self.active_disciplines()
        active_disciplines_ids = []
        active_disciplines_ids.extend(active_disciplines.keys())

        for i in range(len(active_disciplines_ids) - 1):
            for j in range(i + 1, len(active_disciplines)):
                if self.average_disc_grade(active_disciplines_ids[i]) < self.average_disc_grade(active_disciplines_ids[j]):
                    active_disciplines_ids[i], active_disciplines_ids[j] = active_disciplines_ids[j], active_disciplines_ids[i]

        table = self.__initialize_table(["ID", "Discipline name", "Average of total grades received by students"])

        for active_discipline_id in active_disciplines_ids:
            table.add_row([active_discipline_id, self.__disc_repo.find_by_id(active_discipline_id).name, self.average_disc_grade(active_discipline_id)])

        if not table.rows:
            return "no active disciplines"
        return table
    
    def failing_disciplines(self, stud_id:int):
        output = ""
        for grade in self.__grade_repo.data:
            if grade.grade < 5 and grade.stud_id == stud_id:
                output += f"{self.__disc_repo.find_by_id(grade.disc_id).name} -> {grade.grade}\n"
        
        return output.removesuffix("\n")
    
    def active_disciplines(self):
        active_disciplines = {}
        for grade in self.__grade_repo.data:
            active_disciplines[grade.disc_id] = self.__disc_repo.find_by_id(grade.disc_id)
        
        return active_disciplines
        

    def average_grade_per_discipline(self, stud_id:int, disc_id:int):
        sum, len = 0, 0
        for grade in self.__grade_repo.data:
            if grade.stud_id == stud_id and grade.disc_id == disc_id:
                sum += grade.grade
                len += 1
        
        if len == 0:
            return 0
        return sum / len

    def aggregated_average(self, stud_id:int):
        sum, len = 0, 0
        for disc_id in self.__disc_repo.data.keys():
            avg_grade = self.average_grade_per_discipline(stud_id, disc_id)
            if avg_grade != 0: #student has at least one grade for this discipline
                sum += avg_grade
                len += 1
        if len == 0: #student has no grades for this discipline so (division error otherwise)
            return 0
        return sum / len

    def average_disc_grade(self, disc_id:int):
        sum, len = 0, 0
        for grade in self.__grade_repo.data:
            if grade.disc_id == disc_id:
                sum += grade.grade
                len += 1
        
        if len == 0:
            return 0
        return sum / len
        
    def __initialize_table(self, fields:list):
        table = PrettyTable(fields)
        return table