# Solve the problem from the third set here
[year1, month1, day1] = list(map(int, input("Insert date of birth:").split()))
[year2, month2, day2] = list(map(int, input("Insert current date:").split()))
dateOfBirth = [year1, month1, day1]
currentDate = [year2, month2, day2]

def isLeapYear(year):
    if(year % 4 == 0 and year % 100 != 0) or (year % 400 == 0):
        return True
    return False

def partialSum(list, p):
    sum = 0
    for i in range(p):
        sum += list[i]
    return sum

def determineAge(dateOfBirth, currentDate):
    months = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]

    if(dateOfBirth[0] == currentDate[0]):
        if isLeapYear(dateOfBirth[0]):
            months[1] = 29
        ageInDays = partialSum(months, currentDate[1] - 1) + currentDate[2] - partialSum(months, dateOfBirth[1] - 1) - dateOfBirth[2]
        return ageInDays

    ageInDays = 0
    for i in range(dateOfBirth[0] + 1, currentDate[0]):
        ageInDays += 365
        if(isLeapYear(i)):
            ageInDays += 1
        
    if isLeapYear(dateOfBirth[0]):
        months[1] = 29
    ageInDays += partialSum(months, 12) - partialSum(months, dateOfBirth[1] - 1) - dateOfBirth[2]

    if isLeapYear(currentDate[0]) == False:
        months[1] = 28
    ageInDays += partialSum(months, currentDate[1] - 1) + currentDate[2]
    
    return ageInDays

print(determineAge(dateOfBirth, currentDate))
