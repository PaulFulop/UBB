#f(x) = x^2 ->convex function (min(f) = 0)
#f'(x) = 2x
#x1 = 1 -> start value
#x(n + 1) = x(n) - (step size) * f'(x(n))  (step value > 0)

import matplotlib.pyplot as plt
import numpy as np

def seq(length:int, start_value:int, step:int, func:int) -> list:
    x = []
    x.append(start_value)
    for i in range(1, length):
        x.append(x[i - 1] - step * dx(x[i - 1], func))
    
    return x

def dx(x:int, func:int) -> int:
    if func == 1:
        return 2 * x 
    return 3 * (x**2) - 3

xpoints = np.linspace(-10, 10)
plt.figure(figsize=(10, 5))

#a
ypoints = seq(len(xpoints), 1, 0.015, 1) #very small step -> sequence converges to 0
plt.subplot(2, 2, 1)
plt.grid(True)
plt.title(r"(a) small $\eta$", fontsize=16)
plt.plot(xpoints, ypoints, label=r"$\eta$ = 0.015")
plt.legend()

#b
ypoints = seq(len(xpoints), 1, 0.50, 1) #larger step -> sequence converges to 0 faster / in fewer steps
plt.subplot(2, 2, 2)
plt.grid(True)
plt.title(r"(b) larger $\eta$", fontsize=16)
plt.plot(xpoints, ypoints, label=r"$\eta$ = 0.50")
plt.legend()

#c
ypoints = seq(len(xpoints), 1, 3, 1) #step is too large -> sequence diverges from 0
plt.subplot(2, 2, 3) 
plt.grid(True)
plt.title(r"(c) $\eta$ is too large", fontsize=16)
plt.plot(xpoints, ypoints, label=r"$\eta$ = 3")
plt.legend()

#d
#f(x)= x^3 - 3x + 1 -> nonconvex function
#f'(x) = 3 * x^2 - 3
#global min -> -inf
#local min -> -1
#step = 0.001 -> constant 

#1. start value is negative -> the method can end up in the global minimum and it goes away from -1 (blue line)
ypoints = seq(len(xpoints), -3, 0.001, 0)
plt.subplot(2, 2, 4) 
plt.plot(label=r"$\eta$ = 0.001")
plt.grid(True)
plt.title(r"(d) for a nonconvex function, the method can end up in the local minimum, depending on x1", fontsize=7)
plt.plot(xpoints, ypoints, label="starting value: -3")

#2. start value is postive -> the method can end up in the local minimum (orange line)
ypoints = seq(len(xpoints), 3, 0.001, 0)
plt.subplot(2, 2, 4) 
plt.plot(xpoints, ypoints, label="starting value: 3")
plt.legend()


plt.gcf().canvas.manager.set_window_title("Homework 5")
plt.tight_layout()
plt.show()