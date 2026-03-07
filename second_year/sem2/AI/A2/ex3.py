# ***Exercise 3***

# For your build previous model perform all three regularizations presented here. 

import numpy as np
from sklearn import linear_model
import pandas as pd
from sklearn.linear_model import Ridge
from sklearn.linear_model import Lasso
from sklearn.linear_model import ElasticNet
from sklearn.model_selection import train_test_split

# get data
df = pd.read_csv('score.csv')

# separate predictors and responses
X = np.array(df['Hours'])
y = np.array(df['Scores'])

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.25, random_state=0)

X_train = X_train.reshape(-1, 1)
X_test = X_test.reshape(-1, 1)

print("\nLINEAR REGRESSION\n")

lr = linear_model.LinearRegression().fit(X_train, y_train)

print(f"Linear Regression-Training set score: {lr.score(X_train, y_train):.2f}")
print(f"Linear Regression-Test set score: {lr.score(X_test, y_test):.2f}")
print()

print("L2 REGULARISATION -> RIDGE REGRESSION\n")

ridge = Ridge(alpha=0.7).fit(X_train, y_train)

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