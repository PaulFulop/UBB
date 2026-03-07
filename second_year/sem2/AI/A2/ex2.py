#***Exercise 2***

#Download from https://www.kaggle.com/ the regression dataset: Student Study Hours. 
# Create a model and make 3 predictions. Make some nice graphics to depict the model (training set, test set, predictions). import numpy as np

import numpy as np
import matplotlib.pyplot as plt
from sklearn import linear_model
import pandas as pd

# the main idea would be to predict the score of a student based on study hours => predictor: study hours, response: score 

# function for plotting the results
def nice_scatterplot(x, y, a, b, title):
    # font size
    f_size = 18
    
    # make the figure
    _, ax = plt.subplots(1,1, figsize=(8,5)) # Create figure object

    # set axes limits to make the scale nice
    ax.set_xlim(np.min(x)-1, np.max(x) + 1)
    ax.set_ylim(np.min(y)-1, np.max(y) + 1)

    # adjust size of tickmarks in axes
    ax.tick_params(labelsize = f_size)

    # adjust size of axis label
    ax.set_xlabel(r'$x$', fontsize = f_size)
    ax.set_ylabel(r'$y$', fontsize = f_size)
    
    # set figure title label
    ax.set_title(title, fontsize = f_size)

    # you may set up grid with this 
    ax.grid(True, lw=1.75, ls='--', alpha=0.15)
    best_fit = b + a * x

    # make actual plot (Notice the label argument!)
    #ax.scatter(x, y, label=r'$My points$')
    #ax.scatter(x, y, label='$My points$')
    ax.scatter(x, y, s=100, label='training data')
    ax.plot(x, best_fit, ls='--', label='Best Fit Line')
    ax.legend(loc='best', fontsize = f_size)

# get data
df = pd.read_csv('score.csv')

# separate predictors and responses
X_train = np.array(df['Hours'])
y_train = np.array(df['Scores'])

# making X_train a 2d array
X_train = X_train.reshape(-1, 1)

# perform the regression
lr = linear_model.LinearRegression().fit(X_train, y_train)
# print(f"Linear Regression-Training set score: {lr.score(X_train, y_train):.2f}")
# print(f"Linear Regression-Test set score: {lr.score(X_test, y_test):.2f}")

# find the coefficients a and b
a = lr.coef_[0] 
b = lr.intercept_


pred_1 = int(lr.predict([[10]])[0]) # 10 hours of study
pred_2 = int(lr.predict([[2.7]])[0]) # 2.7 hours of study
pred_3 = int(lr.predict([[8.2]])[0]) # 8.2 hours of study

print(f"10 hours of study: approx score of {pred_1}")
print(f"2.7 hours of study: approx score of {pred_2}")
print(f"8.2 hours of study: approx score of {pred_3}")

X_train = X_train.reshape(-1,)
nice_scatterplot(X_train, y_train, a, b, 'Linear regression example')
plt.show()