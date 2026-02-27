import torch

# A tensor is a container of numbers arranged in dimensions.
#
# It as a generalization of numbers, lists, and tables.
#
# Object	       Dimensions	Example
# Single number	    0D tensor	5
# List of numbers	1D tensor	[1, 2, 3]
# Table / matrix	2D tensor	grid of numbers
# Stack of tables	3D tensor	image with RGB channels
# Even more axes	n-D tensor	video, batches of data, etc.

print("\nBASIC THINGS\n")

x = torch.empty(3, 4)
print(type(x))
print(x)

zeros = torch.zeros(2,3)
print(zeros)

ones = torch.ones(2, 3)
print(ones)

# same seed = same numbers geerated
torch.manual_seed(1729)
random = torch.rand(2,3)
print(random)

# Tensor Shapes:
# On performing operations on two or more tensors, they will need to be of the same shape - that is, having the same number of dimensions and
# the same number of cells in each dimension. For that, we have the torch.*_like() methods:

print("\n TENSOR SHAPES\n")
x = torch.empty(2, 2, 3)
print(x.shape)
print(x)

empty_like_x = torch.empty_like(x)
print(empty_like_x.shape)
print(empty_like_x)

zeros_like_x = torch.zeros_like(x)
print(zeros_like_x.shape)
print(zeros_like_x)

ones_like_x = torch.ones_like(x)
print(ones_like_x.shape)
print(ones_like_x)

rand_like_x = torch.rand_like(x)
print(rand_like_x.shape)
print(rand_like_x)

print("\nGPU\n")

if torch.cuda.is_available():
    print('We have a GPU!')
else:
    print('Sorry, CPU only.')

if torch.cuda.is_available():
    my_device = torch.device('cuda')
else:
    my_device = torch.device('cpu')
print('Device: {}'.format(my_device))

x = torch.rand(2, 2, device=my_device)
print(x)
