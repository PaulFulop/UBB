#
# Write the implementation for A5 in this file
#

# 
# Write below this comment 
# Functions to deal with complex numbers -- list representation
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#

import math

# def create_complex_number(x:int, y:int) -> list:
#     return [x, y]

# def get_real_part(c:list) -> int:
#     return c[0]

# def get_img_part(c:list) -> int:
#     return c[1]

# def set_real_part(c:list, x:int) -> None:
#     c[0] = x

# def set_img_part(c:list, x:int) -> None:
#     c[1] = x

# def transform_complex_number(c:list) -> str:
#     if c[0] == 0:
#         return f"{c[1]}i"
#     elif c[1] < 0:
#         return f"{c[0]} - {c[1] * -1}i"
#     elif c[1] > 0:
#         return f"{c[0]} + {c[1]}i"
#     elif c[1] == 0:
#         return f"{c[0]}"

#
# Write below this comment 
# Functions to deal with complex numbers -- dict representation
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#

def create_complex_number(x:int, y:int) -> dict:
    return {"real": x, "img": y}

def get_real_part(c:dict) -> int:
    return c["real"]

def get_img_part(c:dict) -> int:
    return c["img"]

def set_real_part(c:dict, x:int) -> None:
    c["real"] = x

def set_img_part(c:dict, x:int) -> None:
    c["img"] = x

def transform_complex_number(c:dict) -> str:
    if c["real"] == 0:
        return f"{c["img"]}i"
    elif c["img"] < 0:
        return f"{c["real"]} - {c["img"] * -1}i"
    elif c["img"] > 0:
        return f"{c["real"]} + {c["img"]}i"
    elif c["img"] == 0:
        return f"{c["real"]}"

#
# Write below this comment 
# Functions that deal with subarray/subsequence properties
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#

#O(n)
def setA(c:list) -> list:
    longest_subarray, subarray = [],[]

    for i in range(len(c)):
        c_mod = modulus(c[i])
        if c_mod >= 0 and c_mod <= 10:
            subarray.append(c[i])
        else:
            if len(subarray) > len(longest_subarray):
                longest_subarray = subarray.copy()
            subarray.clear()
    
    if len(subarray) > len(longest_subarray): #if the whole list is valid then we dont update longest_sbarray
        return subarray

    return longest_subarray

#O(n^2)
def setB(c:list) -> list:
    n = len(c)

    L = [] #L[i] = LIS that ends with c[i]
    for i in range(n):
        L.append([])

    L[0].append(c[0])
    for i in range(1, n):
        lis = 1 #length of the longest increasing subsequence 

        for j in range(i):
            if get_real_part(c[j]) < get_real_part(c[i]) and lis < len(L[j]) + 1:
                L[i] = L[j].copy()
                lis = len(L[j]) + 1
    
        L[i].append(c[i])
    
    max_lis = L[0]
    for l in L:
        if len(l) > len(max_lis):
            max_lis = l

    return max_lis

def modulus(c:list) -> float:
    x, y = get_real_part(c), get_img_part(c)
    return math.sqrt(x * x + y * y)
 
#
# Write below this comment 
# UI section
# Write all functions that have input or print statements here
# Ideally, this section should not contain any calculations relevant to program functionalities
#

def print_functionalities() -> None:
    print(  "\n1 -> Read a list of complex numbers.\n"  +
            "2 -> Display the list.\n" +
            "3 -> Display the longest subarray with modulus in [0, 10] and the longest increasing subsequence by real part (including length).\n" +
            "4 -> Exit the application.\n") 

def main_menu() -> None:
    running = True
    nums = []
    while running == True:
        print_functionalities()
        option = input("> ")

        if option == "1":
            read_numbers(nums)
        elif option == "2":
            write_list(nums)
        elif option == "3":
            print_sets(nums)
        elif option == "4":
            running = False
        else:
            print("Invalid option!") 

def read_numbers(nums:list) -> None:
    input_str = input("Enter complex numbers separated by spaces (e.g., 3+4i -2+5i 6-7i etc): ")
    complex_nums = input_str.split()

    nums.clear()

    for complex_num in complex_nums:
        try:
            complex_num = complex_num.strip()
            if 'i' not in complex_num:
                nums.append(create_complex_number(int(complex_num), 0))
            else:
                complex_num = complex_num[:-1]  # Remove the 'i'
                if '+' in complex_num:
                    real_part, img_part = complex_num.split('+')
                    nums.append(create_complex_number(int(real_part), int(img_part)))
                elif '-' in complex_num[1:]:
                    real_part, img_part = complex_num.rsplit('-', 1)
                    if complex_nums[0] == '-':
                        real_part = complex_num[1]
                        nums.append(create_complex_number(-int(real_part), -int(img_part)))
                    else:
                        nums.append(create_complex_number(int(real_part), -int(img_part)))
                else:
                    nums.append(create_complex_number(0, int(complex_num)))
        except ValueError:
            print(f"Invalid input for complex number: {complex_num}.")
    
    print("The list of complex numbers has been created!")

def write_list(nums:list) -> None:
    if len(nums) == 0:
        print("The list has not been created yet!")
        return

    print(transform_output(nums))

def print_sets(nums:list) -> None:
    if len(nums) == 0:
        print("The list has not been created yet!")
        return

    print("Set A:")
    print_setA(nums)
    print("Set B:")
    print_setB(nums)

def print_setA(nums:list) -> None:
    longest_subarray = setA(nums)
    if len(longest_subarray) == 0:
        print("There is no such subarray.\n")
        return
    
    print(f"The longest subarray with modulus in [0, 10]: {transform_output(longest_subarray)}")
    print(f"The length of the subarray is {len(longest_subarray)}.\n")

def print_setB(nums:list) -> None:
    longest_inc_subsequence = setB(nums)
    if len(longest_inc_subsequence) == 0:
        print("There is no such subsequence.")
        return

    print(f"The longest  increasing subsequence, when considering each number's real part: {transform_output(longest_inc_subsequence)}")
    print(f"The length of the subsequence is {len(longest_inc_subsequence)}")

def transform_output(nums):
    str_nums = ""
    for num in nums:
        str_nums += transform_complex_number(num) + ', '

    str_nums = str_nums[:len(str_nums) - 2]
    return str_nums

if __name__ == "__main__":
    print("Make magic happen")
    main_menu()