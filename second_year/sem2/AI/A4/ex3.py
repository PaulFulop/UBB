import torch

x = torch.tensor([-2, 9.], requires_grad=True)

# computing using torch
relu1 = torch.relu(x)
relu1.sum().backward() # so that backward computes the derivatives in each point
print(f"Gradient of the ReLU activation function in 2 points, using pytorch: {x.grad.detach().numpy()}")

# Derivative of ReLU
relu_grad = (x > 0).float()
print(f"Gradient of the ReLU activation function in 2 points, using the explicit formula: {relu_grad.detach().numpy()}")

print(f"Difference: {abs(relu_grad - x.grad).detach().numpy()}")