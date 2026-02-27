# load and show an image with Pillow
from PIL import Image

# load the image
image = Image.open('cat.jpg')
# summarize some details about the image
print(image.format)
print(image.mode)

# show the image
# image.show()

# Resize an image to a specific dimension:

print("RESIZE IMAGE: ")
# report the size of the image
print(f"Image size before: {image.size}")
# create a thumbnail and preserve aspect ratio
image.thumbnail((100,100))
# report the size of the thumbnail
print(f"Image size after: {image.size}") # it prints (100, 67) because it keeps aspect ratio, the image was initially stretched a bit,
# it would display (100, 100) if the image was initially a square (height = width)

# convert image into a numpy array:

# load and display an image with Matplotlib
from matplotlib import image
from matplotlib import pyplot

# load image as pixel array
data = image.imread('cat.jpg')
# summarize shape of the pixel array
print(data.dtype)
print(data.shape) # 3 values: width, height, color channels (R,G,B so 3)
# display the array of pixels as an image
pyplot.imshow(data)
pyplot.show()
