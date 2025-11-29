# 1 - 1/2 + 1/3 - 1/4 + 1/5 ... (-1)^(n+1) / n = ln2, n >= 1
# ln2 is approx. 0.69314718056

import prettytable

def ex3():
    n = int(input("Insert the start value value of n: "))
    tests = int(input("Insert the number of tests we should use to compute the sum: "))

    table1 = prettytable.PrettyTable()
    table1.field_names = ["Length of n", "partial_sum"]

    test_list = []
    for pow in range(1, tests + 1):  #creating p tests 
        test_list.append(n**pow)
    
    illustrate_partial_sums1(test_list, table1) # original order -> as n gets larger, the value of partial_sum gets closer to ln2

    print("\nChanging the order of summation in the series by adding the first p positive elements, then adding the first q negative elements...\n")

    p = int(input("Insert the start value of p: "))
    q = int(input("Insert the start value of q: "))

    table2 = prettytable.PrettyTable()
    table2.field_names = ["Length of p", "Length of q", "partial_sum"]

    test_list.clear()
    for pow in range(1, tests + 1):
        test_list.append([p**pow, q**pow])
    
    illustrate_partial_sums2(test_list, table2) # different order -> if p > q or q > p => the result will diverge from ln2 even if both p and q go to infinity

def illustrate_partial_sums1(test_list:list, table: prettytable):
    for test in test_list:
        table.add_row([test, calculate_og_sum(test, 0, 1)])

    print(table)
    print("ln2 = 0.69314718056")

def illustrate_partial_sums2(test_list:list, table: prettytable):
    
    for test in test_list:
        table.add_row([test[0], test[1], calculate_diff_sum(test[0], test[1], 0)])

    print(table)
    print("ln2 = 0.69314718056")


def calculate_og_sum(n:int, partial_sum: int, sign:int) -> int:   
    for x in range(1, n + 1):
        partial_sum += sign * (1 / x)
        sign *= -1

    return partial_sum

def calculate_diff_sum(p:int, q:int, partial_sum: int) ->int: 
    for x in range(1, 2 * p, 2):
        partial_sum += 1 / x 
    
    for x in range(2, 2 * q + 1, 2):
        partial_sum -= 1 / x
    
    return partial_sum

ex3()