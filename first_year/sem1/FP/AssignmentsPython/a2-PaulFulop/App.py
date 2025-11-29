import random

def show_text():
    print("\nHello! This app is able to search an item from a sorted list and illustrates 2 ways of sorting a list in python.\n" +
            "In order to make the app work you need to use theese 5 options:\n\n" +
            "1 -> Generate a list of n random natural numbers (between 0 and 1000).\n" +
            "2 -> Search for an item in the list using the binary search (recursive implementation).\n" +
            "3 -> Sort the list using the Exchange Sort.\n" +
            "4 -> Sort the list using the Heap Sort\n" +
            "5 -> Exit the app.\n\n")


def choose_options():
    app_running = True
    list = []

    while(app_running == True):      
        option = input("\nPlease choose an option from 1 to 5: ")
        if option == "1":
            list.clear()
            n = 0
            while n <= 0:     
                n = int(input("Please specify the length of the list: "))
                if n <= 0:
                    print("The length is not valid!")

            for i in range(0, n):
                list.append(random.randint(0, 1000))

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
                exchange_sort(list, steps)
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
                heap_sort(list, steps)
                print("After heap sort ->", list)
        elif option == "5":
            app_running = False
        else:
            print("Invalid option!\n")


def binary_search(list: list, value: list) -> int:
        
    return aux_function(list, 0, len(list) - 1, value)

def aux_function(list: list, left: int, right: int, value: int) -> int:
        #we didn't find the value
        if left > right:
            return -1

        middle = (left + right) // 2
        if list[middle] == value:
            return middle
        elif value < list[middle]:
            return aux_function(list, left, middle - 1, value) #go to the left
        else:
            return aux_function(list, middle + 1, right, value) #go to the right

def exchange_sort(list: list, steps: int): 
    step = 0
    for i in range(0, len(list) - 1):
        #search for the correct value to put at position i
        for j in range(i + 1, len(list)):
            if list[i] > list[j]:
                temp = list[i]
                list[i] = list[j]
                list[j] = temp

                step += 1
                if step % steps == 0:
                    print("step", step, "->", list, "( we swap", list[j], "and", list[i], ")")             

def heap_sort(list: list, steps: int):
    n = len(list)
    step = 0

    #ensures that we have a max-heap
    for i in range(n // 2 - 1, -1, -1): #ignore leaf nodes because they have no children
        heapify(list, n, i)

    for i in range(n - 1, 0, -1):
        #swap the root (list[0]) with the last node in the current max-heap (list[i])
        temp = list[0]
        list[0] = list[i]
        list[i] = temp

        step += 1
        if step % steps == 0:
            print("step", step, "->", list, "(", list[i], "is the current root and was swapped with", list[0], ")")

        heapify(list, i, 0) #after swap the binary tree doesn`t form a max heap anymore so the nodes must be rearranged
        #i-th node will be "ignored" / deleted from the heap since its position has been determined

#to reshape the subtree starting from node i in such a way that it becomes a max-heap
def heapify(list: list, n: int, i: int):
    largest = i
    left_child = 2 * i + 1
    right_child = 2 * i + 2

    if left_child < n and list[left_child] > list[largest]:
        largest = left_child

    if right_child < n and list[right_child] > list[largest]:
        largest = right_child
    
    if largest != i:
        temp = list[i]
        list[i] = list[largest]
        list[largest] = temp
        heapify(list, n, largest)     

def sortedList(list: list) -> bool:
    for i in range(0, len(list) - 1):
        if list[i] > list[i + 1]:
            return False
    return True

show_text()
choose_options()