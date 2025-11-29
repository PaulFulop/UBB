# Solve the problem from the second set here
n = int(input("Read a number: "))

def isPrime(n):
    if n < 2:
        return False
    if n == 2:
        return True
    if n % 2 == 0:
        return False

    i = 3
    while i * i <= n:
        if(n % i == 0):
            return False
        i += 2
    
    return True

def productOfProperFactors(n):
    if(n == 1 or isPrime(n)):
        return 0
    
    p = 1
    d = 2
    while d * d <= n:
        if n % d == 0:
            p *= d * (n / d)
        if(d * d  == n):
            p //= d
        d = d + 1
    
    return p

print("The product of all the proper factors of n is", int(productOfProperFactors(n)))