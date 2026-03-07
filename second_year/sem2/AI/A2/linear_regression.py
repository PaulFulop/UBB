# Linear regression is defined as an algorithm that provides a linear relationship between an independent variable
#  and a dependent variable to predict the outcome of future events.

import numpy as np
import matplotlib.pyplot as plt
from sklearn import linear_model
import statsmodels.api as sm
import pandas as pd

x_train = np.array([1,2,3]) # predictors
y_train = np.array([2,3,6]) # responses

print(x_train.shape)
x_train = x_train.reshape([3,1])
print(x_train) # i can reshape the array, now it is basically a matrix with 3 rows, having 1 column
print(x_train.shape)

# Make a simple scatterplot
# plt.scatter(x_train,y_train)

# check dimensions 
print(x_train.shape,y_train.shape)

def nice_scatterplot(x, y, title):
    # font size
    f_size = 18
    
    # make the figure
    fig, ax = plt.subplots(1,1, figsize=(8,5)) # Create figure object

    # set axes limits to make the scale nice
    ax.set_xlim(np.min(x)-1, np.max(x) + 1)
    ax.set_ylim(np.min(y)-1, np.max(y) + 1)

    # adjust size of tickmarks in axes
    ax.tick_params(labelsize = f_size)
    
    # remove tick labels
    ax.tick_params(labelbottom=False,  bottom=False)

        # adjust size of axis label
    ax.set_xlabel(r'$x$', fontsize = f_size)
    ax.set_ylabel(r'$y$', fontsize = f_size)
    
    # set figure title label
    ax.set_title(title, fontsize = f_size)

    # you may set up grid with this 
    ax.grid(True, lw=1.75, ls='--', alpha=0.15)

    # make actual plot (Notice the label argument!)
    #ax.scatter(x, y, label=r'$My points$')
    #ax.scatter(x, y, label='$My points$')
    ax.scatter(x, y, label=r'$my\,points$')
    ax.legend(loc='best', fontsize = f_size)
    
    return ax

#nice_scatterplot(x_train, y_train, 'A nice plot')
# plt.show()

# BUILDING A MODEL FROM SCRATCH
print("BUILDING A MODEL FROM SCRATCH\n")

# We will solve the equations for simple linear regression and find the best fit solution to our simple problem.
# We basically need to find the best-fit line y = ax + b, => we need to find a and b

# we have to re-shape our arrays to 2D
x_train = x_train.reshape(x_train.shape[0], 1)
y_train = y_train.reshape(y_train.shape[0], 1)

# the following formula has to be computed (see the ipynb file):

# first, compute means
y_bar = np.mean(y_train)
x_bar = np.mean(x_train)

# build the two terms
numerator = np.sum( (x_train - x_bar)*(y_train - y_bar) )
denominator = np.sum((x_train - x_bar)**2)

print(numerator.shape, denominator.shape) #check shapes -> prints (), () which is good because those are just scalars

#slope a
a = numerator/denominator

#intercept b
b = y_bar - a * x_bar

print("The best-fit line is {0:3.2f} + {1:3.2f} * x".format(b, a))
print(f'The best fit is {b}')

# we can make a function out of the things above:
def simple_linear_regression_fit(x_train: np.ndarray, y_train: np.ndarray) -> np.ndarray:
    """
    Inputs:
    x_train: a (num observations by 1) array holding the values of the predictor variable
    y_train: a (num observations by 1) array holding the values of the response variable

    Returns:
    beta_vals:  a (num_features by 1) array holding the intercept and slope coeficients
    """
    
    # Check input array sizes
    if len(x_train.shape) < 2:
        print("Reshaping features array.")
        x_train = x_train.reshape(x_train.shape[0], 1)

    if len(y_train.shape) < 2:
        print("Reshaping observations array.")
        y_train = y_train.reshape(y_train.shape[0], 1)

    # first, compute means
    y_bar = np.mean(y_train)
    x_bar = np.mean(x_train)

    # build the two terms
    numerator = np.sum( (x_train - x_bar)*(y_train - y_bar) )
    denominator = np.sum((x_train - x_bar)**2)
    
    #slope a
    a = numerator/denominator

    #intercept b
    b = y_bar - a * x_bar

    return np.array([b,a])

x_train = np.array([1 ,2, 3])
y_train = np.array([2, 2, 4])

coeficients = simple_linear_regression_fit(x_train, y_train)

a = coeficients[1]
b = coeficients[0]

print("The best-fit line is {1:8.6f} * x + {0:8.6f}.".format(a, b))

# %load solutions/best_fit_scatterplot.py
fig_scat, ax_scat = plt.subplots(1,1, figsize=(10,6))

# Plot best-fit line
x_train = np.array([[1, 2, 3]]).T

best_fit = b + a * x_train

ax_scat.scatter(x_train, y_train, s=300, label='Training Data')
ax_scat.plot(x_train, best_fit, ls='--', label='Best Fit Line')

ax_scat.set_xlabel(r'$x_{train}$')
ax_scat.set_ylabel(r'$y$')
#plt.show()
print()

# BUILDING A MODEL WITH statsmodel and sklearn
print("BUILDING A MODEL WITH statsmodel and sklearn\n") # both have their advantages and vice-versa, but good overall
print("statsmodel:\n")

# create the X matrix by appending a column of ones to x_train
X = sm.add_constant(x_train)

# this is the same matrix as in our scratch problem!
print(X)

# build the OLS model (ordinary least squares) from the training data
toyregr_sm = sm.OLS(y_train, X)

# do the fit and save regression info (parameters, etc) in results_sm
results_sm = toyregr_sm.fit()

# pull the beta parameters out from results_sm
beta0_sm = results_sm.params[0]
beta1_sm = results_sm.params[1]

print(f'The regression coef from statsmodels are: beta_0 = {beta0_sm:8.6f} and beta_1 = {beta1_sm:8.6f}\n')

print("sklearn:\n")
# build the least squares model
toyregr = linear_model.LinearRegression()

# save regression info (parameters, etc) in results_skl
results = toyregr.fit(x_train, y_train)

# pull the beta parameters out from results_skl
beta0_skl = toyregr.intercept_
beta1_skl = toyregr.coef_[0]

print("The regression coefficients from the sklearn package are: beta_0 = {0:8.6f} and beta_1 = {1:8.6f}".format(beta0_skl, beta1_skl))

print("Using salary dataset as a real problem:\n")

# FLOW:
# 1. load and preprocess data
# 2. separate features and target 
# 3. split into train/test
# 4. train the model (only on training data!)
# 5. evaluate on test data (data model has never seen) -> lr.score
# 6. make predictions -> lr.predict


# HERE WE ARE NOT SCALING BECAUSE WE ONLY HAVE ONE FEATURE.
# IF WE HAD MULTIPLE FEATURES INTO ACCOUNT, WE WOULD NEED TO SCALE THEM, s.t THEY'RE VALUES ARE NUMBERS AND NOT 'TOO FAR' FROM EACH OTHER
# BECAUSE THATS HOW WE CAN FIND A GOOD LINE -> LINEAR REGRESSION
from sklearn.model_selection import train_test_split
df = pd.read_csv('Salary_dataset.csv')

X = np.array(df['YearsExperience'])
y = np.array(df['Salary'])

# we split into train dataset and test dataset (25% goes to test set and the rest to train set)
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.25, random_state=0) # fixes the random shuffle so you get the same split every time

# rember to reshape the X list in order to have a two dimensional array, because sklearn expects X to always be a table (rows = samples, columns = features)
# Since we have only one feature the reshape looks like below: 
X_train = X_train.reshape(-1, 1) # -1 basically means "figure this automatically => i dont have to explicitly type the exact number of elements everytime (number of rows in years of experiene)"
X_test = X_test.reshape(-1, 1)

# we perform the regression
lr = linear_model.LinearRegression().fit(X_train, y_train)

print(f"Linear Regression-Training set score: {lr.score(X_train, y_train):.2f}")
print(f"Linear Regression-Test set score: {lr.score(X_test, y_test):.2f}")

# to find the coefficients a and b
a = lr.coef_[0] # we have one feature with index 0

b = lr.intercept_ # a scalar
 
print(a, "* x +", b, "= y")
print(lr.predict([[20]]))
print(a * 20 + b)

# the model has predicted that we get a salary of 213643.93010646297 after 20 years