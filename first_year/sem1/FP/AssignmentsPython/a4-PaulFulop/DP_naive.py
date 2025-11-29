def maximize_sum():
    A = [30, 5, 15, 18, 30, 40]
    m = int()
    n = int()
    p = int()
    q = int()
    #m > n > p > q
    
    max_sum = -(2**32 + 1)
    length = len(A)

    #O(n^4)
    for i in range(length):
        for j in range(i):
            for k in range(j):
                for l in range(k):
                    if A[i] - A[j] + A[k] - A[l] > max_sum:
                        max_sum = A[i] - A[j] + A[k] - A[l]
                        m, n, p, q = i, j, k, l

    print(f"The maximum value is {max_sum}, and the expression used to calculate it is {A[m]} - {A[n]} + {A[p]} - {A[q]}")

maximize_sum()