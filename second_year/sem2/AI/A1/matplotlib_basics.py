import matplotlib.pyplot as plt
import numpy as np

# basic example
# x = [1,2]
# y = [1,5]
# plt.plot(x, y)
# plt.show();

# The plot() function is used to draw points (markers) in a diagram. By default, the plot() function draws a line from point to point.
# The function takes parameters for specifying points in the diagram. Parameter 1 is an array containing the points on the x-axis.
# Parameter 2 is an array containing the points on the y-axis.

x = np.random.randint(low=1, high=20, size=30)
plt.plot(x, color = 'blue', linewidth=3, linestyle='dashed')
plt.show()
