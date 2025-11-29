import prettytable
import numpy as np

"""

f(x) = e^(-x^2)

Let [-a, a] be the chosen interval where a > 0, n = the number of trapeziums.
Using trapezium rule => ∫ from -a to a f(x) dx = (2a / n) * (f(a) / 2 + f(-a) / 2 + Σ from i=1 to n-1 of f(x(i)).

x(k) - x(k-1) = 2a/n => x(k) = 2a/n + x(k-1) for any k = 1...n
A larger n means a more precise result since we take the area of more trapeziums.

√π = 1.77245385091

"""


def f(x): # e^(-x^2)
    return np.exp(-x**2)

def series(a, n):
    sum = 0
    x = -a + 2 * a / n

    for i in range(1, n):
        sum += f(x)
        x += 2 * a / n
    
    return sum

def trapezium_rule(a, n):
    return (2 * a / n) * (f(-a)/2 + f(a)/2 + series(a, n))

def compute_areas(a, n, tests):
    table = prettytable.PrettyTable()
    table.field_names = ["Test", "Interval", "Area under the bell curve"]
    for test in range(1, tests + 1):
        area = trapezium_rule(a, n)
        table.add_row([test, f"{-a} to {a}", area])
        a *= 1.2 # gradual growth of the interval [-a, a]
    
    return table

n = int(input("Insert the number of trapeziums: "))
a = float(input("Insert value of a: "))
tests = int(input("Insert the number of tests we should use: "))

print(compute_areas(a, n, tests))
print("√π = 1.77245385091")
