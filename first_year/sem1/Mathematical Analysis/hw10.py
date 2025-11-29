# Ex: 3, point b

import matplotlib.pyplot as plt
import numpy as np

k = 5 # iterations
cont_lines = 16 # the number of contour lines
x = np.linspace(-10, 10, num=300) # values of x
y = x # values of y
xk, yk = 7.5, 6.5 # starting point

# f(x, y)
def f(x, y, b):
    return (x**2 + b * y**2)

# the gradient of f(x, y) = (x, by) (proof in a)
def gradient(x, y, b):
    return [x, b * y]

# sk (step size) does not appear because it is equal to 1 (proof in a)
def gradient_descent(k, ax, xk, yk, b):
    list_xk, list_yk = [xk], [yk]
    ax.plot(xk, yk, 'ro')
    while k != 0 and (xk != 0 or yk != 0):
        xk = xk - xk 
        yk = (1 - b) * yk
        ax.plot(xk, yk, 'ro')

        list_xk.append(xk)
        list_yk.append(yk)

        k -= 1
    
    ax.plot(list_xk, list_yk, marker='o', linestyle=':', color='r')

X, Y = np.meshgrid(x, y)
fig, ax = plt.subplots(2, 2, figsize=(12, 6), constrained_layout=True)

# Plot for b = 1
ax[0][0].set_title("When b = 1")
CS = ax[0][0].contour(X, Y, f(X, Y, 1), levels=cont_lines)
ax[0][0].clabel(CS, inline=True, fontsize=10)
gradient_descent(k, ax[0][0], xk, yk, 1)

# Plot for b = 1/2
ax[0][1].set_title("When b = 1/2")
CS = ax[0][1].contour(X, Y, f(X, Y, 1/2), levels=cont_lines)
ax[0][1].clabel(CS, inline=True, fontsize=10)
gradient_descent(k, ax[0][1], xk, yk, 1/2)

# Plot for b = 1/5
ax[1][0].set_title("When b = 1/5")
CS = ax[1][0].contour(X, Y, f(X, Y, 1/5), levels=cont_lines)
ax[1][0].clabel(CS, inline=True, fontsize=10)
gradient_descent(k, ax[1][0], xk, yk, 1/5)

# Plot for b = 1/10
ax[1][1].set_title("When b = 1/10")
CS = ax[1][1].contour(X, Y, f(X, Y, 1/10), levels=cont_lines)
ax[1][1].clabel(CS, inline=True, fontsize=10)
gradient_descent(k, ax[1][1], xk, yk, 1/10)

plt.gcf().canvas.manager.set_window_title("Homework 10")
plt.show()