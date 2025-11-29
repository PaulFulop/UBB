def maximize_sum():
    A = [30, 5, 15, 18, 30, 40] 
    print(f"The input list: {A}\n")

    inf = 2**32 + 1
    length = len(A)
    m, n, p, q = int(), int(), int(), int()
    partial_min, partial_max = [None] * length, [None] * length

    first_diff = [-inf] * length #first_diff[i] = largest difference of 2 elements between position i and n - 1 (max value of A[m] - A[n])
    second_diff = [-inf] * length #second_diff[i] = largest difference of 2 elements between position 0 and i (max value of A[p] - A[q])
    max_sum = -inf

    #partial_min[i] = the current minimum value (up to i)
    partial_min[0] = A[0]
    for i in range(1, length):
        partial_min[i] = min(partial_min[i - 1], A[i])

    #partial_max[i] = the current maximum value (starting from i)
    partial_max[-1] = A[-1]
    for i in range(length - 2, -1, -1):
        partial_max[i] = max(partial_max[i + 1], A[i])

    for i in range(length - 2, 0, -1):
        first_diff[i] = max(first_diff[i + 1], partial_max[i - 1] - A[i])
        print(f"first_diff[{i}] = {first_diff[i]} -> the largest difference of 2 elements in range {i} - {len(A) - 1} (where m > n) is {first_diff[i]}")

    print()

    for i in range(1, length):
        second_diff[i] = max(second_diff[i - 1], A[i] - partial_min[i - 1])
        print(f"second_diff[{i}] = {second_diff[i]} -> the largest difference of 2 elements in range 0 - {i} (where p > q) is {second_diff[i]}")
    
    print()
    for i in range(length - 1):
        if max_sum < second_diff[i] + first_diff[i + 1]:
            max_sum = second_diff[i] + first_diff[i + 1]
            m, n, p, q = partial_max[i + 1], partial_max[i + 1] - first_diff[i + 1], second_diff[i] + partial_min[i], partial_min[i]


    # print(f"The first_diff list is used to find the maximum difference A[m] - A[n]: {first_diff}")
    # print(f"The second_diff list is used to find the maximum difference A[p] - A[q]: {second_diff}\n")
    print(f"The maximum value is {max_sum}, and the expression used to calculate it is {m} - {n} + {p} - {q}")

maximize_sum() #Time complexity: O(n) where n = length of the input list