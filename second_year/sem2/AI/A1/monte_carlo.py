# Monte Carlo simulation: run the experiment a lot of times, using random variables, and then analyzethe probability/result
# Compare it with the mathematically deduced probability
#Experiment: we have yard, a pipe inside it and we throw balls uniformly inside that yard: find probability that a ball falls into the pipe

import numpy as np

# fixed values
pipe_radius = 30 # area: pi * radius^2
ball_radius = 1
yard_edge = 100 # area: edge^2
center_x, center_y = 50, 50 # center of the pipe (in the middle of the yard, but can be placed anywhere inside the yard)


# 1. Deduced Probability: efficient_pipe_area / yard_area

# Using just pipe_area would be good enough when the ball is very small, but incomplete if the ball would be bigger 
# (ex: half the size of the pipe_radius => it could overlap with the pipe and not fall inside)
# In order for the ball to fully land inside the pipe, the ball should be at least 'ball_radius' cm away from the edge of the pipe
# Therefore, we should basically "shrink" the area of the pipe such that the ball will fully land inside it
# (ex: if the size of the ball is very close to the size of the pipe, there's only a few points / a very mall circle that ensure it lands fully)

efficient_pipe_radius = pipe_radius - ball_radius
efficient_pipe_area = np.pi * np.pow(efficient_pipe_radius, 2)
yard_area = np.pow(yard_edge, 2)
deduced_probability = efficient_pipe_area / yard_area
print(f"Deduced probability: {deduced_probability}")


# 2. Monte Carlo Simulation: generating random postions (x, y), x, y from [0, yard_edge]
#                            if the distance between the point (x, y) and (center_x, center_y) <= efficient_pipe_radius => inside the pipe -> success.
#                            doing this same experiment thousands / millions of times 
#                            counting the number of successes and dividiing by number of trials

# returns 1 on success, 0 otherwise
def throw_ball(allowed_bound, success_bound):
    x,y = np.random.uniform(0, allowed_bound, 2)
    
    if (np.pow((x - center_x), 2) + np.pow((y - center_y), 2) <= np.pow(success_bound, 2)): # distance from center to point (x, y) < efficient_pip_radius^2
        return 1

    return 0

trials = 1000000
simulation_probability = sum([throw_ball(yard_edge, efficient_pipe_radius) for _ in range(trials)]) / trials
print(f"Probability computed using Monte Carlo simulation: {simulation_probability}")

print(f"Error: {abs(simulation_probability - deduced_probability)}")
