# essentially a simulaiton of a roulette
# each slot of the roulette has a probability Pi from [0, 1] and the sum of all probabilities is 1 (obviously)
# function that randomly generates an index i with probability Pi from the set {0, 1, ... n }
# <=> the slot on which the roulette has stopped at

import numpy as np

# 1 -> randomly generate an index i with probability Pi from the set {0, 1 ... n}
def spinner(probabilityDistribution):
    n = len(probabilityDistribution)
    return int(np.random.choice(np.arange(n), p=probabilityDistribution)) # choose a random value out of {1...n-1} with the given probabilities

# 2 -> input is a list of natural numbers that holds how many degrees has the center angle θi corespondent to index i.
def angle_spinner(angles):
    n = len(angles)
    probabilities = np.array(angles) / np.sum(angles) # angle is proportional to 360, bigger angle => bigger probability
    return int(np.random.choice(np.arange(n), p=probabilities))

probabilityDistribution, angles = [0.1, 0.2, 0.3, 0.25, 0.15], [160, 45, 85, 70] # sum of probabilities is 1, sum of angles is 360

results1 = [spinner(probabilityDistribution) for _ in range(10)]
print(f"Spinning 10 times with slot probabilities {probabilityDistribution}:\n{results1}")
print()
results2 = [angle_spinner(angles) for _ in range(10)]
print(f"Spinning 10 times with slot angles {angles}:\n{results2}")
