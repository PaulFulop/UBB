import numpy as np
import scipy as sp
import matplotlib as mpl
import matplotlib.cm as cm
import matplotlib.pyplot as plt
import pandas as pd
from sklearn import preprocessing

X_train = np.array([[ 1., -1.,  2.],[ 2.,  0.,  0.],[ 0.,  1., -1.]])

# standardization / mean removal and variance scaling
scaler = preprocessing.StandardScaler().fit(X_train) # the scaler looks at my data and learns the statistics it needs
                                              # (mean, std, min, max etc)
                                              
X_scaled = scaler.transform(X_train) # .transform actually does the job (scales the dataset)

# I can also use fit_transform directly

print("STANDARDIZATION:\n")
print(scaler.mean_) # average of each COLUMN, not row -> (1 + 2 + 0) / 3 and so on
print(scaler.scale_)  # standard deviation of each column
print(X_scaled)
print()


# scaling features to a range

print("SCALING FEATURES TO A RANGE:\n")
min_max_scaler = preprocessing.MinMaxScaler() # scaling to [0, 1]
X_scaled_min_max = min_max_scaler.fit_transform(X_train)
print(X_scaled_min_max)

# i can test with new unseen data
# I SHOULD NOT CALL .fit again, only transform
# same instance of transform should be a pplied to new usneen test data during the ft call
# scaling and shifting will be applied to be consistent with the transformation performed on the TRAINED data 
X_test = np.array([[-3., -1.,  4.]])
X_test_min_max = min_max_scaler.transform(X_test)
print(X_test_min_max)
print()

# MinMaxScaler also allows an explicit min and max 
# MaxAbsScaler works the same but shrinks data in the range [-1, 1]


print("NORMALIZATION:\n")
X_normalized = preprocessing.normalize(X_train, norm='l2')
print(X_normalized)
print()

print("ENCODING FEATURES:\n")
# basically when we deal with non-numbers, we want to (obviously) transofrm them into numbers

enc = preprocessing.OrdinalEncoder()
X_train1 = [['male', 'from US', 'uses Safari'], ['female', 'from Europe', 'uses Firefox']]
enc.fit(X_train1) # scans each column and builds a sorted list of all unique categories it finds

# For each column it learns:
# col1: ['female', 'male']        → sorted alphabetically → female=0, male=1
# col2: ['from Europe', 'from US'] → sorted alphabetically → from Europe=0, from US=1
# col3: ['uses Firefox', 'uses Safari'] → sorted alphabetically → uses Firefox=0, uses Safari=1


# 'female'      → 0
# 'from US'     → 1
# 'uses Safari' → 1

# result: [[0., 1., 1.]]
print(enc.transform([['female', 'from US', 'uses Safari']]))

# OrdinalEncoder will also pass through missing values that are indicated by np.nan
X_train1 = [['male'], ['female'], [np.nan], ['female']]
print(enc.fit_transform(X_train1)) # returns an array
print()

# OrdinalEncoder provides a parameter encoded_missing_value
# to encode the missing values without the need to create a pipeline and using SimpleImputer.
enc = preprocessing.OrdinalEncoder(encoded_missing_value=-1) # basically I can specify what value to be put if it's missing
X_train1 = [['male'], ['female'], [np.nan], ['female']]
print(enc.fit_transform(X_train1))
print()