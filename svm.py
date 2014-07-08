# coding: utf-8
from sklearn.svm import LinearSVC, SVC
from sklearn.linear_model import *
import numpy as np

def estimate(estimator):
	estimator.fit(data_training, label_training)
	label_predicted = estimator.predict(data_prediction)
	# print(label_predicted)
	rate = sum([1 if q == a else 0 for q, a in zip(label_predicted, label_prediction)])
	print(float(rate) / len(label_predicted))


data_training_tmp = np.loadtxt('histograms.dat', delimiter=' ')
data_training = [x[1:64] for x in data_training_tmp]
label_training = [int(x[0]) for x in data_training_tmp]

data_prediction_tmp = np.loadtxt('histograms-prediction.dat', delimiter=' ')
data_prediction = [x[1:64] for x in data_prediction_tmp]
label_prediction = [int(x[0]) for x in data_prediction_tmp]

print("Training Data:");
print(label_training);
print("Prediction Data:");
print(label_prediction);

print("Perceptron:");
estimate(Perceptron(penalty='elasticnet', n_iter=200, shuffle=True, eta0=0.95))
print("Logistic Regression:");
estimate(LogisticRegression(C=1.0))
print("Linear Kernel SVM:");
estimate(LinearSVC(C=1.0))
print("RBF Kernel SVM (gamma=0.0001):");
estimate(SVC(kernel="rbf", gamma=0.0001))
print("RBF Kernel SVM (gamma=0.001):");
estimate(SVC(kernel="rbf", gamma=0.001))

print("Sigmoid Kernel SVM:");
estimate(SVC(kernel="sigmoid", coef0=-1.7))

print("polynomial Kernel SVM (degree=2):");
estimate(SVC(kernel="poly", degree=2))
print("polynomial Kernel SVM (degree=3):");
estimate(SVC(kernel="poly", degree=3))
print("polynomial Kernel SVM (degree=4):");
estimate(SVC(kernel="poly", degree=4))

# def my_kernel(x, y):
# 	return np.dot(x, y.T)
# print("custom Kernel SVM:");
# estimate(SVC(kernel=my_kernel))

