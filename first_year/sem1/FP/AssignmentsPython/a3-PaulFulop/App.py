import random
import time
import prettytable

def show_text():
    print("\nHello! This app is able to search an item from a sorted list and illustrates 2 ways of sorting a list in python.\n" +
            "In order to make the app work you need to use theese 5 options:\n\n" +
            "1 -> Generate a list of n random natural numbers (between 0 and 1000).\n" +
            "2 -> Search for an item in the list using the binary search (recursive implementation).\n" +
            "3 -> Sort the list using the Exchange Sort.\n" +
            "4 -> Sort the list using the Heap Sort\n" +
            "5 -> Exit the app.\n" +
            "6 -> Illustrate runtime of the implemented sorting algorithms for BEST case.\n" +
            "7 -> Illustrate runtime of the implemented sorting algorithms for AVERAGE case.\n" +
            "8 -> Illustrate runtime of the implemented sorting algorithms for WORST case.\n")


def choose_options():
    app_running = True
    list = []
    best = 1
    worst = 2
    average = 3

    while(app_running == True):      
        option = input("\nPlease choose an option from 1 to 8: ")
        if option == "1":
            n = 0
            while n <= 0:     
                n = int(input("Please specify the length of the list: "))
                if n <= 0:
                    print("The length is not valid!")

            list = generate_random_list(n, 1000)

            print("The list has been created / recreated:", list)
        elif option == "2":
            if len(list) == 0:
                print("The list has not been created yet!")
            elif sortedList(list) == False:
                print("Cannot search if the list is not sorted!")
            else:
                print("In order to search an item from the list, you first need to provide it`s value.")
                x = int(input("Please choose an item from the list that you created: "))
                if binary_search(list, x) == -1:
                    print("Item not found!")
                else:
                    print("The position of the value you wanted is", binary_search(list, x))
        elif option == "3":
            if len(list) == 0:
                print("The list has not been created yet!")
            else:
                steps = 0
                while steps <= 0:    
                    steps = int(input("Please specify the number of steps we should take before printing the partially sorted list: "))
                    if steps <= 0:
                        print("Invalid number of steps!")

                print("Before exchange sort -> ", list)
                exchange_sort(list, steps, True)
                print("After exchange sort -> ", list)
        elif option == "4":
            if len(list) == 0:
                print("The list has not been created yet!")
            else:
                steps = 0
                while steps <= 0:
                    steps = int(input("Please specify the number of steps we should take before printing the partially sorted list: "))
                    if steps <= 0:
                        print("Invalid number of steps!")
                
                print("Before heap sort ->", list)
                heap_sort_ascending(list, steps, True)
                print("After heap sort ->", list)
        elif option == "5":
            app_running = False
        elif option == "6":
            measure_runtime(best)
        elif option == "7":
            measure_runtime(average)
        elif option == "8":
            measure_runtime(worst)
        else:
            print("Invalid option!\n")

#Time complexity: O(log2(n)), where n = length of the list.
#We cut the searching range in half everytime and we compare the element in the middle with the value we're searching for.
#Best case: the element we're searching for is in the middle of the sorted list -> O(1)
#Worst case: the element we're searching for is not in the list -> O(log2(n))
def binary_search(list: list, value: int) -> int:
        
    return aux_function(list, 0, len(list) - 1, value)

def aux_function(list: list, left: int, right: int, value: int) -> int:
        if left > right:
            return -1

        middle = (left + right) // 2
        if list[middle] == value:
            return middle
        elif value < list[middle]:
            return aux_function(list, left, middle - 1, value)
        else:
            return aux_function(list, middle + 1, right, value)
        

#Time complexity: O(n^2)
#Outer loop -> we go from 0 to n - 2, where n is the length of the list => n - 1 iterations.
#Inner loop -> we go from i + 1 to n - 1.
#Loops are nested => we could have (n - 1) + (n - 2) + ... + 1 operations.
#1 + 2 + ... + (n - 2) + (n - 1) = (n - 1) * (n) / 2 = 1/2 * (n - 1) * n
# O(1/2 * (n - 1) * n) = O((n - 1) * n) = O(n^2)
#The algorithm doesn't know that when the elements are sorted, so best case = worst case = O(n^2) time complexity, only the number of swaps might change.
def exchange_sort(list: list, steps: int, show_steps: bool): 
    step = 0
    for i in range(0, len(list) - 1):
        for j in range(i + 1, len(list)):
            if list[i] > list[j]:
                list[j], list[i] = list[i], list[j]

                step += 1
                if step % steps == 0 and show_steps == True:
                    print("step", step, "->", list, "( we swap", list[j], "and", list[i], ")")             

#Time complexity: O(nlog(n))
#Going through the list -> O(n)
#Reshaping the binary tree -> O(log(n))
#We go through every element in the list and reshape the binary tree everytime => O(nlog(n))
#Generally, the complexity is the same no matter what because the swap between the root and last node will always "destroy" the max-heap.
#Best case = Worst case = O(nlog(n)), but when the array is already built like a max-heap/min-heap we might have less/more operations and function calls.
def heap_sort_ascending(list: list, steps: int, show_steps: bool):
    step = 0
    n = len(list)

    build_max_heap(list)

    for i in range(n - 1, 0, -1):
        list[0], list[i] = list[i], list[0]

        step += 1
        if step % steps == 0 and show_steps == True:
            print("step", step, "->", list, "(", list[i], "is the current root and was swapped with", list[0], ")")

        heapify_max(list, i, 0)

# O(n / 2) -> O(n) in best case, O(nlog(n)) in worst case
def build_max_heap(list: list):
    n = len(list)
    for i in range(n // 2 - 1, -1, -1):
        heapify_max(list, n, i)

def heapify_max(list: list, n: int, i: int):
    largest = i
    left_child = 2 * i + 1
    right_child = 2 * i + 2

    if left_child < n and list[left_child] > list[largest]:
        largest = left_child

    if right_child < n and list[right_child] > list[largest]:
        largest = right_child
    
    if largest != i:
        list[i], list[largest] = list[largest], list[i]
        heapify_max(list, n, largest)     

def heap_sort_descending(list: list):
    n = len(list)
    build_min_heap(list)

    for i in range(n - 1, 0, -1):
        list[0], list[i] = list[i], list[0]
        heapify_min(list, i, 0)


def build_min_heap(list: list):
    n = len(list)
    for i in range(n // 2 - 1, -1, -1):
        heapify_min(list, n, i)

#to build a min-heap
def heapify_min(list: list, n: int, i: int):
    smallest = i
    left_child = 2 * i + 1
    right_child = 2 * i + 2

    if left_child < n and list[left_child] < list[smallest]:
        smallest = left_child

    if right_child < n and list[right_child] < list[smallest]:
        smallest = right_child
    
    if smallest != i:
        list[i], list[smallest] = list[smallest], list[i]
        heapify_min(list, n, smallest)

def measure_runtime(case: int):
    test_lists1 = generate_test_lists()
    test_lists2 = test_lists1.copy()
    test_lists3 = test_lists1.copy()
    table = initalize_table()
    search_values, runtime1, runtime2, runtime3 = [], [], [], []

    #for binary search
    for test_list in test_lists3:
        heap_sort_ascending(test_lists3, 1, False)

    if case == 1:
        shuffle_best_case(test_lists1, test_lists2)
        search_values = find_values(1, test_lists3)
        print("Illustrating runtime for the best cases:")
    elif case == 2:
        shuffle_worst_case(test_lists1, test_lists2)
        search_values = find_values(2, test_lists3)
        print("Illustrating runtime for the worst cases:")
    else:
        search_values = find_values(3, test_lists3)
        print("Illustrating runtime for the average cases:")

    #measure runtime for exchange sort
    for test_list in test_lists1:
        start_time = time.perf_counter()
        exchange_sort(test_list, 1, False)
        end_time = time.perf_counter()
        runtime1.append(round(end_time - start_time, 5))

    #measure runtime for heap sort
    for test_list in test_lists2:
        start_time = time.perf_counter()
        heap_sort_ascending(test_list, 1, False)
        end_time = time.perf_counter()
        runtime2.append(round(end_time - start_time, 5))
    
    #measure runtime for bnary search
    for value in search_values:
        start_time = time.perf_counter()
        binary_search(test_list, value)
        end_time = time.perf_counter()
        runtime3.append(round(end_time - start_time, 15))
    
    for i in range(5):
        table.add_row([len(test_lists1[i]), runtime1[i], runtime2[i], runtime3[i]])
            
    print(table)

def shuffle_best_case(lists1: list, lists2: list):

    #for exchange sort
    for list in lists1:
        heap_sort_ascending(list, 1, False)

    #for heap sort
    for list in lists2:
        build_max_heap(list)

def shuffle_worst_case(lists1: list, lists2: list):
    for list in lists1:
        heap_sort_descending(list)
        
    for list in lists2:
        build_min_heap(list)

def find_values(case: int, test_lists: list) -> list:
    search_values = []

    if case == 1:
        for list in test_lists:
            search_values.append(list[(len(list) - 1) // 2])
    elif case == 2:
        for list in test_lists:
            search_values.append(-1)
    else:
        for list in test_lists:
            search_values.append(random.randint(0, 10000))
    
    return search_values

def sortedList(list: list) -> bool:
    for i in range(0, len(list) - 1):
        if list[i] > list[i + 1]:
            return False
    return True

def initalize_table() -> prettytable:
    tbl = prettytable.PrettyTable()
    tbl.field_names = ["Length of the list", "Exchange Sort (seconds)", "Heap Sort (seconds)", "Binary Search (seconds)"]
    return tbl

def generate_test_lists() -> list:
    matrix = []
    n = 0
    while n <= 0:
        n = int(input("Set the starting length: "))
        if n <= 0:
            print("The starting length is not valid!")
        
        for i in range(5):
            matrix.append(generate_random_list(n * (2 ** i), 10000))

    print("The test lists have been created / recreated!")
    return matrix

def generate_random_list(size: int, limit: int) -> list:
    list = []
    for i in range(size):
        list.append(random.randint(0, limit))
    return list

show_text()
choose_options()