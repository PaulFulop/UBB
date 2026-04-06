# the imports:

# pandas for handling the data
import pandas as pd

import matplotlib.pyplot as plt
import numpy as np

# Seaborn is a Python data visualization library that offers a user-friendly interface 
#    for generating visually appealing and informative statistical graphics.
import seaborn as sns

# From sklearn we import some classes and functions for data handling, the tree classifier, 
#    the accuracy and the plot function to depict the tree  
from sklearn.preprocessing import LabelEncoder
from sklearn.model_selection import train_test_split 
from sklearn.tree import DecisionTreeClassifier 
from sklearn.metrics import accuracy_score 
from sklearn.tree import plot_tree 

# This class we use it to search exhaustive over specified parameter values for an estimator.
from sklearn.model_selection import GridSearchCV 

# 1
df_iris = pd.read_csv("iris_teach_2.csv")
#print(df_iris.head())

# 2
#print(df_iris.isnull().sum())

# 3
df_iris.dropna(inplace=True)

# 4
X = df_iris[["sepal length (cm)", "sepal width (cm)", "petal length (cm)", "petal width (cm)"]]
y = df_iris["iris_name"]

# 5
le = LabelEncoder()
y = le.fit_transform(y)

# 6
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.25, random_state=0) # fixes the random shuffle so you get the same split every time

# Create a decision tree classifier object 
tree_clf = DecisionTreeClassifier(criterion='entropy', random_state=42) 
# Fit the classifier to the training data 
tree_clf.fit(X_train, y_train)

# Make predictions on the test set 
y_pred = tree_clf.predict(X_test) 
# Calculate the accuracy of the model 
accuracy = accuracy_score(y_test, y_pred) 
# print("Accuracy: {:.2f}".format(accuracy))

# display the tree
# plot_tree(tree_clf)
# plt.show()

# TUNING THE MODEL
# Tune the hyperparameters of the decision tree model to improve it's performance

# Define the hyperparameters to search over 
param_grid = {"max_depth": [1, 2, 3, 4, 5, 6, 7]} 
# Create a grid search object 
grid_search = GridSearchCV(tree_clf, param_grid, cv=5) 
# Fit the grid search object to the training data 
grid_search.fit(X_train, y_train) 
# Print the best hyperparameters found by the grid search 
# print("Best hyperparameters:", grid_search.best_params_)

# Create a new decision tree classifier object with the best hyperparameters 
tree_clf_tuned = DecisionTreeClassifier(criterion='entropy', max_depth=2, random_state=42) 
# Fit the classifier to the training data 
tree_clf_tuned.fit(X_train, y_train)

# plot_tree(tree_clf_tuned)
# plt.show()

# FEATURE SELECTION

# df_clean_iris_set = X.copy()
# df_clean_iris_set['iris_name']=y
# df_clean_iris_set.head()

# Plot Pearson correlation of features 
# colormap = plt.cm.viridis
# plt.figure(figsize=(12,12))
# plt.title('Pearson Correlation of Features', y=1.05, size=15)
# sns.heatmap(df_clean_iris_set.astype(float).corr(),linewidths=0.1,vmax=1.0, square=True, cmap=colormap, linecolor='white', annot=True)
# plt.show()

# The initial observation provided by this heatmap is very valuable as it allows for a quick understanding of the predictive power of each feature.

# It is evident from the heatmap that the *petal length* and *petal width* exhibit the strongest correlations
#  (in absolute terms) with the target classes, with respective values of 0.95 and 0.96.

# However, it should be noted that these two features also have a very high correlation with each other
#  (0.96, the highest in the dataset), implying that they may be conveying the same information.
#  Consequently, utilizing both of these features as inputs for the same model might not be advisable. 

# If we look up to the example we can see that the column 2 from X (*petal length*) is in the root.
#  Therefore, further exploration and comparison of these features is required.

# 7 and 8

# Dropping the column
X.drop(columns=["petal width (cm)"], inplace=True)

# y is already encoded and does not need any changes

# Splitting data into train and test 
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.25, random_state=0)

# making the new tree
new_tree_clf = DecisionTreeClassifier(criterion='entropy', random_state=50) 
new_tree_clf.fit(X_train, y_train)

# finding the best depth
param_grid = {"max_depth": [1, 2, 3, 4, 5, 6, 7]} 
grid_search = GridSearchCV(new_tree_clf, param_grid, cv=5) 
grid_search.fit(X_train, y_train) 
best_depth = grid_search.best_params_['max_depth']


# Create a new decision tree classifier object with the best depth 
new_tree_clf_tuned = DecisionTreeClassifier(criterion='entropy', max_depth=best_depth, random_state=50) 
# Fit the classifier to the training data 
new_tree_clf_tuned.fit(X_train, y_train)
 
y_pred = new_tree_clf_tuned.predict(X_test) 
accuracy = accuracy_score(y_test, y_pred) 
print("Accuracy: {:.2f}".format(accuracy))
print("Best depth:", best_depth)
plot_tree(new_tree_clf_tuned)
plt.show()