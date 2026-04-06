import torch

x = torch.tensor([5., 7.], requires_grad=True)

# computing using torch
y = x
y = y.sum() # so that backward computes the derivatives in each point
y.backward()
print(f"Gradient of the linear activation function in 2 points, using pytorch: {x.grad.detach().numpy()}")

# Derivative of linear function
linear_grad = torch.ones_like(x)
print(f"Gradient of the sigmoid activation function in 2 points, using the explicit formula: {linear_grad.detach().numpy()}")

print(f"Difference: {abs(linear_grad - x.grad).detach().numpy()}")