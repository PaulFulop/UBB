# Solve the problem from the first set here
n = int(input("Read a number: "))

def largestNum(n):
    freq = [0 for i in range(10)]
    while n > 0:
        digit = n % 10
        freq[digit] += 1
        n //= 10
    
    m = 0
    for i in range(9, -1, -1):
        if(freq[i] > 0):
            for j in range(freq[i]):
                m = m * 10 + i
    return m

print("The largest number written with the same digits of n is", largestNum(n))
