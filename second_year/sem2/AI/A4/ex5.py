import torch
import matplotlib.pyplot as plt

def plot_relu(lower_bound=-10, upper_bound=10, steps=100):
    x = torch.linspace(lower_bound, upper_bound, steps, requires_grad=True)

    y = torch.relu(x)
    y.sum().backward()
    y_grad = x.grad

    plt.figure(figsize=(8,5))

    # Plot sigmoid
    plt.plot(x.detach().numpy(), y.detach().numpy(), label='ReLU', color='blue')

    # Plot gradient
    plt.plot(x.detach().numpy(), y_grad.detach().numpy(), label='ReLU Gradient', color='red')

    plt.title("Sigmoid Activation Function and Gradient")
    plt.xlabel("x")
    plt.ylabel("Value")
    plt.legend()
    plt.grid(True)
    plt.show()

plot_relu()