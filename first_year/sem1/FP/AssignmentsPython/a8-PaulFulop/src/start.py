from faker.proxy import Faker
import sys, random
sys.path.append("/src")

from domain.student import Student
from domain.discipline import Discipline
from domain.grade import Grade

from repository.stud_repos.memo_repo import StudMemoRepo
from repository.stud_repos.txt_repo import StudTxtRepo
from repository.stud_repos.bin_repo import StudBinRepo

from repository.disc_repos.memo_repo import DiscMemoRepo
from repository.disc_repos.txt_repo import DiscTxtRepo
from repository.disc_repos.bin_repo import DiscBinRepo

from repository.grade_repos.memo_repo import GradeMemoRepo
from repository.grade_repos.txt_repo import GradeTxtRepo
from repository.grade_repos.bin_repo import GradeBinRepo

from ui.ui import UI


def get_repos():
    stud_repo, disc_repo, grade_repo = StudMemoRepo(), DiscMemoRepo(), GradeMemoRepo()
    try:
        file = open("src/settings.properties", "rt")
    except FileNotFoundError:
        return
    
    tokens = []
    lines = file.readlines()
    for line in lines:
        tokens.append(line.split("=")[1].removesuffix("\n").strip().lower())
    file.close()

    match tokens[0]:
        case "inmemory":
            init_repos(stud_repo, disc_repo, grade_repo, 20)
        case "txtfiles":
            stud_repo, disc_repo, grade_repo = StudTxtRepo("src/repository/stud_repos/" + tokens[1]), DiscTxtRepo("src/repository/disc_repos/" + tokens[2]), GradeTxtRepo("src/repository/grade_repos/" + tokens[3])
            #init_repos(stud_repo, disc_repo, grade_repo, 20)
        case "binfiles":
            stud_repo, disc_repo, grade_repo = StudBinRepo("src/repository/stud_repos/" + tokens[1]), DiscBinRepo("src/repository/disc_repos/" + tokens[2]), GradeBinRepo("src/repository/grade_repos/" + tokens[3])
            #init_repos(stud_repo, disc_repo, grade_repo, 20)
        case _:
            pass
    return [stud_repo, disc_repo, grade_repo]

def init_repos(stud_repo, disc_repo, grade_repo, n):
    students = generate_students(n)
    for stud in students:
        stud_repo.add(stud)

    disciplines = generate_disciplines(n)
    for disc in disciplines:
        disc_repo.add(disc)
            
    for grade in generate_grades(students, disciplines, n):
        grade_repo.add(grade)


def generate_students(n):
    fake = Faker()
    students = []
    unique_stud_ids = random.sample(range(1, 201), n)

    for id in unique_stud_ids:
        students.append(Student(id, fake.name()))
    
    return students

def generate_disciplines(n):
    fake = Faker()
    disciplines = []
    unique_disc_ids = random.sample(range(1, 201), n)

    for id in unique_disc_ids:
        disciplines.append(Discipline(id, fake.bs().title()))
    
    return disciplines

def generate_grades(students, disciplines, n):
    grades = []
    for i in range(n):
        grades.append(Grade(disciplines[i].id, students[i].id, random.randint(1, 10)))
    
    return grades

def start_program():
    repos = get_repos()
    ui = UI(repos[0], repos[1], repos[2])
    ui.main_menu()

if __name__ == "__main__":
    start_program()