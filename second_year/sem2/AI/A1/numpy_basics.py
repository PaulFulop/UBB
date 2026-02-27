import numpy as np

my_array = np.array([1, 2, 3, 4])

print(len(my_array))
print(my_array.shape)
print(my_array.dtype)
# arrays in numpy have similar functionality as lists

# OTHER USEFUL FUNCTIONS FROM NUMPY

print(my_array.mean()) # prints the mean

np.ones(10) # generates 10 floating point ones
#array([1., 1., 1., 1., 1., 1., 1., 1., 1., 1.])

np.dtype(float).itemsize # in bytes (remember, 1 byte = 8 bits)
# 8

np.ones(10, dtype='int') # generates 10 integer ones
# array([1, 1, 1, 1, 1, 1, 1, 1, 1, 1])

np.zeros(10)
# array([0., 0., 0., 0., 0., 0., 0., 0., 0., 0.])

np.random.random(10) # uniform from [0,1]
#array([0.50929916, 0.99934203, 0.02767909, 0.79934657, 0.38465927,
# 0.56439711, 0.52433838, 0.08889742, 0.18240995, 0.36137475])

#np.random.choice is also useful

normal_array = np.random.randn(1000) # generate random numbers from a normal distribution with mean 0 and variance 1
print("The sample mean and standard devation are %f and %f, respectively." %(np.mean(normal_array), np.std(normal_array)))

len(normal_array) #1000

grid = np.arange(0., 1.01, 0.1) 
print(grid) # array([0. , 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1. ])
print(np.random.choice(grid, 5, replace=False)) # choose 5 random elements from the grid (no replacemnt => we can't take the same value more times,
                                                # we'll get an error if we try to choose more elements than the size of the grid)
print(np.random.choice(grid, 20, replace=True)) # this is correct, we choose 20 elements even if 20 > size of grid (duplicates are basically allowed)

x = np.linspace(-10, 10, 1000) # linspace() returns evenly-spaced numbers over a specified interval
