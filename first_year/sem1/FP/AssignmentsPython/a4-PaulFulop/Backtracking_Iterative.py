def solve():
    n = int(input("Insert the number of points to consider: "))
    points = []

    print("Read the points: ")
    for i in range(n):
        x, y = input().split() #split str based on whitespace
        x = int(x)
        y = int(y)
        points.append([x, y])
    
    determine_subsets(n, points)

#If the slope btween p1 and p2 = with the slope between p2 and p3 => points are collinear 
def verify_collinear(p1: list, p2: list, p3: list) -> bool:
    #p[0] = x, p[1] = y
    x1, y1 = p1[0], p1[1]
    x2, y2 = p2[0], p2[1]
    x3, y3 = p3[0], p3[1]

    #True if slopes are equal, False otherwise
    return (y2 - y1) * (x3 - x2) == (y3 - y2) * (x2 - x1)

#True if all the points in the list are collinear
def collinear_points(pos:list, points: list) -> bool:
    for i in range(len(pos) - 2):
        if not verify_collinear(points[pos[i]], points[pos[i + 1]], points[pos[i + 2]]):
            return False
    return True

#backtracking -> Generating combinations of 3, ....  n positions
def determine_subsets(n: int, points: list): 
    none_collinear = True   
    #About O(n * 2^n) -> n * (combinations n, 3) + ... + n * (combinations n, n) is about n * 2^n, we're excluding for k = 0, 1, 2
    for p in range(3, n + 1):
        found = [False]

        print("Subsets with", p,  "elements formed by collinear points:")
        backtracking_iterative(n, p, points, found) #generate all subsets of length p included in {1, 2, ..., n}

        if found[0] == False:
            print("None")
        else:
            none_collinear = False

        print()
    
    if none_collinear == True:
        print("No points are collinear.")

#O(n * combinations n, k)
def backtracking_iterative(n:int, p:int, points: list, found_collinear: list):
    stack = [(0, [], p)] #start index, the current combination, and the number of elements needed to complete a combination

    while len(stack) > 0:
        start, combination, k = stack.pop() #last object in the stack
        
        if k == 0:
            display(combination, points)
            found_collinear[0] = True
        else:
            for i in range(start, n - k + 1): #n - k + 1 prevents cases where adding more elements would be impossible
                    if len(combination) < 2 or collinear_points(combination + [i], points) == True:
                        stack.append((i + 1, combination + [i], k - 1))

def display(pos: list, points: list):
    valid_subset = []
    for i in pos:
        valid_subset.append(points[i])

    print(valid_subset)
        
solve()