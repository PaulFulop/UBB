import numpy as np
import matplotlib.pyplot as plt

# f(x) = sin(x)
def f(x):
    return np.sin(x)

# f'(x) = cos(x)
def f_exact_derivative(x):
    return np.cos(x)

def forward_difference(f, x, h):
    return (f(x + h) - f(x)) / h

def centered_difference(f, x, h):
    return (f(x + h) - f(x - h)) / (2 * h)

x = np.pi / 4  # 45 degrees
h_values = np.logspace(-8, 0, 50)  # Small values of h from 10^-8 to 1

# Compute exact derivative
exact_value = f_exact_derivative(x)

# Calculate errors
forward_errors = []
centered_errors = []

for h in h_values:
    forward_approx = forward_difference(f, x, h)
    centered_approx = centered_difference(f, x, h)
    
    forward_errors.append(abs(forward_approx - exact_value))
    centered_errors.append(abs(centered_approx - exact_value))

plt.figure(figsize=(13, 7))

# Plot error curves
plt.loglog(h_values, forward_errors, label="Forward Difference Error")
plt.loglog(h_values, centered_errors, label="Centered Difference Error")

# Plot h and h^2 curves
plt.loglog(h_values, h_values, label="h", linestyle="--", color="black")
plt.loglog(h_values, h_values**2, label="h^2", linestyle="--", color="red")

plt.xlabel("h")
plt.ylabel("Error")

plt.legend()

exp1 = "When h is very small, the difference between f(x) and f(x + h) (or between f(x + h) and f(x - h)) involves numbers that are very close to each other =>"
exp2 = "the result can be very small and the computer cannot express such numbers accurately, so the errors start increasing as h becomes smaller."
full_exp = exp1 + "\n" + exp2
plt.title(full_exp, fontsize=11)
plt.show()