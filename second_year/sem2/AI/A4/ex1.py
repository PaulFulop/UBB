import torch

x = torch.tensor([5., 7.], requires_grad=True)

# computing using torch
sigma1 = torch.sigmoid(x)

#sum to make scalar for backward
sigma1.sum().backward() # so that backward computes the derivatives in each point
print(f"Gradient of the sigmoid activation function in 2 points, using pytorch: {x.grad.detach().numpy()}")

# Sigmoid
sigma2 = 1 / (1 + torch.exp(-x))

# Derivative
sigma_prime = sigma2 * (1 - sigma2)
print(f"Gradient of the sigmoid activation function in 2 points, using the explicit formula: {sigma_prime.detach().numpy()}")

print(f"Difference: {abs(sigma_prime - x.grad).detach().numpy()}")