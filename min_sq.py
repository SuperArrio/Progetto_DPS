#Import scikit-learn dataset library
from sklearn import datasets

#Load dataset
cancer = datasets.load_breast_cancer()

from sklearn.model_selection import train_test_split
# Split dataset into training set and test set
X_train, X_test, y_train, y_test = train_test_split(cancer.data, cancer.target, test_size=0.3,random_state=109) # 70% training and 30% test

import numpy as np

X_train=np.append(X_train,np.ones([ X_train.shape[0] ,1 ]) ,axis=1)
X_test =np.append(X_test ,np.ones([ X_test.shape[0] ,1 ])  ,axis=1)

W=np.dot( np.dot( np.linalg.inv(np.dot(np.transpose(X_train),X_train)) , np.transpose(X_train)) , y_train)


y_pred_hand=[]

for i in X_test:
 	if sum(i*W) > 0.5:
 		y_pred_hand.append(1)
 	else:
 		y_pred_hand.append(0)
y_pred_hand=np.array(y_pred_hand)


#Import scikit-learn metrics module for accuracy calculation
from sklearn import metrics

print("********TEST MIN-SQUARES**********")
# Model Accuracy: how often is the classifier correct?
print("Accuracy:",metrics.accuracy_score(y_test, y_pred_hand))

# Model Precision: what percentage of positive tuples are labeled as such?
print("Precision:",metrics.precision_score(y_test, y_pred_hand))

# Model Recall: what percentage of positive tuples are labelled as such?
print("Recall:",metrics.recall_score(y_test, y_pred_hand))

