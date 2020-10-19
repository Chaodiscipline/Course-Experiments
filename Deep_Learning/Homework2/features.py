#!/usr/bin/env python
# coding: utf-8
# # Image features exercise 
# We have seen that we can achieve reasonable performance on an image classification task by training a linear classifier on the pixels of the input image. In this exercise we will show that we can improve our classification performance by training linear classifiers not on raw pixels but on features that are computed from the raw pixels.
# All of your work for this exercise will be done in this notebook.
import random
import numpy as np
import matplotlib.pyplot as plt
plt.rcParams['figure.figsize'] = (10.0, 8.0) # set default size of plots
plt.rcParams['image.interpolation'] = 'nearest'
plt.rcParams['image.cmap'] = 'gray'
# ## Load data
# Similar to previous exercises, we will load CIFAR-10 data from disk.
from SDUCS2019.features import color_histogram_hsv, hog_feature
from SDUCS2019.data_utils import *
def get_CIFAR10_data(num_training=49000, num_validation=1000, num_test=1000):
    # Load the raw CIFAR-10 data
    cifar10_dir = 'SDUCS2019/datasets/cifar-10-batches-py'
    X_train, y_train, X_test, y_test = load_CIFAR10(cifar10_dir)
    # Subsample the data
    mask = list(range(num_training, num_training + num_validation))
    X_val = X_train[mask]
    y_val = y_train[mask]
    mask = list(range(num_training))
    X_train = X_train[mask]
    y_train = y_train[mask]
    mask = list(range(num_test))
    X_test = X_test[mask]
    y_test = y_test[mask]
    return X_train, y_train, X_val, y_val, X_test, y_test

# Cleaning up variables to prevent loading data multiple times (which may cause memory issue)
try:
   del X_train, y_train
   del X_test, y_test
   print('Clear previously loaded data.')
except:
   pass

X_train, y_train, X_val, y_val, X_test, y_test = get_CIFAR10_data()


# ## Extract Features
# For each image we will compute a Histogram of Oriented
# Gradients (HOG) as well as a color histogram using the hue channel in HSV
# color space. We form our final feature vector for each image by concatenating
# the HOG and color histogram feature vectors.
# 
# Roughly speaking, HOG should capture the texture of the image while ignoring
# color information, and the color histogram represents the color of the input
# image while ignoring texture. As a result, we expect that using both together
# ought to work better than using either alone. Verifying this assumption would
# be a good thing to try for your interests.
# 
# The `hog_feature` and `color_histogram_hsv` functions both operate on a single
# image and return a feature vector for that image. The extract_features
# function takes a set of images and a list of feature functions and evaluates
# each feature function on each image, storing the results in a matrix where
# each column is the concatenation of all feature vectors for a single image.

from SDUCS2019.features import *

num_color_bins = 10 # Number of bins in the color histogram
feature_fns = [hog_feature, lambda img: color_histogram_hsv(img, nbin=num_color_bins)]
X_train_feats = extract_features(X_train, feature_fns, verbose=True)
X_val_feats = extract_features(X_val, feature_fns)
X_test_feats = extract_features(X_test, feature_fns)

# Preprocessing: Subtract the mean feature
mean_feat = np.mean(X_train_feats, axis=0, keepdims=True)
X_train_feats -= mean_feat
X_val_feats -= mean_feat
X_test_feats -= mean_feat

# Preprocessing: Divide by standard deviation. This ensures that each feature
# has roughly the same scale.
std_feat = np.std(X_train_feats, axis=0, keepdims=True)
X_train_feats /= std_feat
X_val_feats /= std_feat
X_test_feats /= std_feat

# Preprocessing: Add a bias dimension
X_train_feats = np.hstack([X_train_feats, np.ones((X_train_feats.shape[0], 1))])
X_val_feats = np.hstack([X_val_feats, np.ones((X_val_feats.shape[0], 1))])
X_test_feats = np.hstack([X_test_feats, np.ones((X_test_feats.shape[0], 1))])


# ## Train SVM on features
# Using the multiclass SVM code developed earlier in the assignment, train SVMs on top of the features extracted above; this should achieve better results than training SVMs directly on top of raw pixels.


# ## Neural Network on image features
# Earlier in this assigment we saw that training a three-layer neural network on raw pixels achieved better classification performance than linear classifiers on raw pixels. In this notebook we have seen that linear classifiers on image features outperform linear classifiers on raw pixels. 
# 
# For completeness, we should also try training a neural network on image features. This approach should outperform all previous approaches: you should easily be able to achieve over 55% classification accuracy on the test set; 


# Preprocessing: Remove the bias dimension
# Make sure to run this cell only ONCE
print(X_train_feats.shape)
X_train_feats = X_train_feats[:, :-1]
X_val_feats = X_val_feats[:, :-1]
X_test_feats = X_test_feats[:, :-1]
print(X_train_feats.shape)

from SDUCS2019.classifiers.neural_net import ThreeLayerNet
input_dim = X_train_feats.shape[1]
print(input_dim)
hidden_dim = 500
num_classes = 10

best_net = None

################################################################################
# TODO: Train a three-layer neural network on image features. You may want to    #
# cross-validate various parameters as in previous sections. Store your best   #
# model in the best_net variable.                                              #
################################################################################
results = {}
best_val = -1


learning_rates = [0.005,0.001]
regularization_strengths = [0.0001]
hl_size = [1024]
bach_sizes = [200,250,300] 
best_para = []


p = 0
for bs in bach_sizes:
    for hs in hl_size:
        for lr in learning_rates:
            for rs in regularization_strengths:
                # print params
                print('\nTraining params: batch size: {}, hidden size: {}, learning rate: {}, reg strength: {}'.format(bs, hs, lr, rs))

                net = ThreeLayerNet([input_dim, hs, hs, num_classes])
                v = {'dW1': np.zeros((hs, input_dim)), 'dW2': np.zeros((hs, hs)), 
                         "dW3": np.zeros((num_classes, hs)), 'db1': np.zeros((1, hs)), 
                         'db2': np.zeros((1, hs)), 'db3': np.zeros((1, num_classes))}
                stats = net.train(X_train_feats, y_train, X_val_feats, y_val, v, 
                                  num_iters=5000, batch_size=bs,
                                  learning_rate=lr, learning_rate_decay=0.95,
                                  reg=rs, verbose=True)
                

                # predict train and valid
                y_train_pred = net.predict(X_train)
                y_val_pred = net.predict(X_val)
                # visualize the weights of the best network

                # compute accuracies
                train_accuracy = np.mean(y_train == y_train_pred)
                val_accuracy = np.mean(y_val == y_val_pred)
                
                p += 1
                print(p, "train_accuracy:", train_accuracy, "val_accuracy:", val_accuracy)
                # save best network
                if val_accuracy > best_val:
                    best_val = val_accuracy
                    best_net = net
                    best_papr = [bs, hs, lr, rs]
                # store best params
                results[(bs, hs, lr, rs)] = (train_accuracy, val_accuracy)

print(best_para)
################################################################################
#                              END OF YOUR CODE                                #
################################################################################


# Run your best neural net classifier on the test set. 

test_acc = (best_net.predict(X_test_feats) == y_test).mean()
print(test_acc)
