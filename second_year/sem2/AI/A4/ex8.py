import torch
import torch.nn as nn

# Define dataset
X = torch.tensor([[0,0],[0,1],[1,0],[1,1]], dtype=torch.float32)
Y = torch.tensor([[0],[1],[1],[1]], dtype=torch.float32)

class Perceptron(nn.Module):
    def __init__(self, input_dim, output_dim):
        super(Perceptron, self).__init__()
        self.linear = torch.nn.Linear(input_dim, output_dim)
        # self.activation = torch.nn.Sigmoid()
        
    def forward(self, x):
        x = self.linear(x)
        # x = self.activation(x)
        return x

    
input_size, output_size = 2, 1
model = Perceptron(input_size, output_size)
criterion = torch.nn.BCEWithLogitsLoss()  # Binary Cross-Entropy
optimizer = torch.optim.SGD(model.parameters(), lr=0.1)  # Stochastic gradient descent optimizer

# Train the model
for epoch in range(1000):
    optimizer.zero_grad()
    outputs = model(X)
    loss = criterion(outputs, Y)
    loss.backward()
    optimizer.step()
    
    if (epoch+1) % 100 == 0:
        print(f'Epoch [{epoch+1}/1000], Loss: {loss.item():.4f}')

# Evaluation
with torch.no_grad():
    predictions = (model(X) > 0).float()
    accuracy = (predictions == Y).float().mean()
    print(f'Predictions:\n{predictions}\nAccuracy: {accuracy.item()*100:.2f}%')