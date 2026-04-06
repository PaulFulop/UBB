# Import dependencies
import torch
import matplotlib.pyplot as plt
from sklearn.datasets import make_blobs
from sklearn.model_selection import train_test_split
from utils import plot_decision_boundary

# Set the hyperparameters for data creation
NUM_CLASSES = 4
NUM_FEATURES = 2
RANDOM_SEED = 42

# 1. Create multi-class data
X_blob, y_blob = make_blobs(n_samples=1000,
    n_features=NUM_FEATURES, # X features
    centers=NUM_CLASSES, # y labels 
    cluster_std=1.5, # give the clusters a little shake up (try changing this to 1.0, the default)
    random_state=RANDOM_SEED
)

# 2. Turn data into tensors
X_blob = torch.from_numpy(X_blob).type(torch.float)
y_blob = torch.from_numpy(y_blob).type(torch.LongTensor)
# print(X_blob[:5], y_blob[:5])

# 3. Split into train and test sets
X_blob_train, X_blob_test, y_blob_train, y_blob_test = train_test_split(X_blob,
    y_blob,
    test_size=0.2,
    random_state=RANDOM_SEED
)

# 4. Plot data
plt.figure(figsize=(10, 7))
plt.scatter(X_blob[:, 0], X_blob[:, 1], c=y_blob, cmap=plt.cm.RdYlBu)
# plt.show()


# 5. Create the model
class BlobModel(torch.nn.Module):
    def __init__(self, input_dim, output_dim):
        super(BlobModel, self).__init__()
        self.linear = torch.nn.Linear(input_dim, output_dim) # takes in {input_dim}  features (X), produces {output_dim} features
        
    def forward(self, x):
        return self.linear(x)
    
# moving to gpu
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")

# moving model to gpu, including data
model_blob = BlobModel(NUM_FEATURES, NUM_CLASSES).to(device)
X_blob_train = X_blob_train.to(device)
X_blob_test  = X_blob_test.to(device)
y_blob_train = y_blob_train.to(device)
y_blob_test  = y_blob_test.to(device)

# 6. Setup loss function and optimizer
loss_fn = torch.nn.CrossEntropyLoss()
optimizer = torch.optim.SGD(model_blob.parameters(), lr=0.15)

# 7. Train and Evaluate the model
for epoch in range(5000):
    # train
    model_blob.train()
    y_train_pred = model_blob(X_blob_train)
    loss = loss_fn(y_train_pred, y_blob_train)
    optimizer.zero_grad()
    loss.backward()
    optimizer.step()

    #evaluate
    model_blob.eval()
    with torch.no_grad(): # disable gradient computation
        y_test_pred = model_blob(X_blob_test)
        y_class = torch.argmax(y_test_pred, dim=1)
        accuracy = (y_class == y_blob_test).float().mean().item()
        test_loss = loss_fn(y_test_pred, y_blob_test)

    if epoch % 500 == 0:
        print(f"Epoch {epoch} | Train Loss: {loss.item():.4f} | Test Loss: {test_loss.item():.4f} | Accuracy: {accuracy:.4f}")

plot_decision_boundary(model_blob, X_blob, y_blob)
plt.show()