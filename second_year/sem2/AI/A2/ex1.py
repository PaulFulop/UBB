# ***Exercise 1***

# Load the dataset *WA_Fn-UseC_-Telco-Customer-Churn.csv* provided. 
# Perform transformations on it so it is prepared to build a model
#  (scaling the numerical data and the cathegorical features transformed in numerical integer labels.  

import pandas as pd
from sklearn import preprocessing

df = pd.read_csv("WA_Fn-UseC_-Telco-Customer-Churn.csv")

# encode all text columns
enc = preprocessing.OrdinalEncoder(encoded_missing_value=-1) 
cat_cols = df.select_dtypes(include=['str']).columns # how pandas deals with text
df[cat_cols] = enc.fit_transform(df[cat_cols]) # df[cat_cols] = give me only data from cat_cols

# all data is now numbers => scale everything 
scaler = preprocessing.StandardScaler()
df[df.columns] = scaler.fit_transform(df)

print(df.head())