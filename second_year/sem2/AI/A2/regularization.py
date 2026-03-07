# Regularization
# - restricting a model to avoid overfitting by shrinking the coefficient estimates to zero. 
# To avoid overfitting we control the model’s complexity by adding a penalty to the model’s loss function

import numpy as np
import matplotlib.pyplot as plt
from sklearn import linear_model
import statsmodels.api as sm
import pandas as pd
from sklearn.linear_model import Ridge
from sklearn.linear_model import Lasso
from sklearn.linear_model import ElasticNet
from sklearn.model_selection import train_test_split

df = pd.read_csv('Salary_dataset.csv')

X = np.array(df['YearsExperience'])
y = np.array(df['Salary'])

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.25, random_state=0) # fixes the random shuffle so you get the same split every time

print("L2 REGULARISATION -> RIDGE REGRESSION\n")

# rember to reshape the X list in order to have a two dimensional array. 
# Since we have only one feature the reshape looks like below: 
X_train = X_train.reshape(-1, 1)
X_test = X_test.reshape(-1, 1)

ridge = Ridge(alpha=0.7).fit(X_train, y_train) # this is where weights are calculated

print(f"Ridge Regression-Training set score: {ridge.score(X_train, y_train):.2f}")
print(f"Ridge Regression-Test set score: {ridge.score(X_test, y_test):.2f}")

print("\nL1 REGULARISATION -> LASSO REGRESSION\n")

lasso = Lasso(alpha=1.0).fit(X_train, y_train)

print(f"Lasso Regression-Training set score: {lasso.score(X_train, y_train):.2f}")
print(f"Lasso Regression-Test set score: {lasso.score(X_test, y_test):.2f}")

print("\nELASTIC NET\n")

elastic_net = ElasticNet(alpha=0.01, l1_ratio=0.01).fit(X_train, y_train) # alpha controls how strong the penalty is

print(f"Elastic Net-Training set score: {elastic_net.score(X_train, y_train):.2f}")
print(f"Elastic Net-Test set score: {elastic_net.score(X_test, y_test):.2f}")