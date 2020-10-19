import numpy as np
from random import shuffle

def softmax_loss_naive(W, X, y, reg):
  """
  Softmax loss function, naive implementation (with loops)

  Inputs have dimension D, there are C classes, and we operate on miniwbatches
  of N examples.

  Inputs:
  - W: A numpy array of shape (D, C) containing weights.
  - X: A numpy array of shape (N, D) containing a minibatch of data.
  - y: A numpy array of shape (N,) containing training labels; y[i] = c means
    that X[i] has label c, where 0 <= c < C.
  - reg: (float) regularization strength

  Returns a tuple of:
  - loss as single float
  - gradient with respect to weights W; an array of same shape as W
  """
  # Initialize the loss and gradient to zero.
  loss = 0.0
  dW = np.zeros_like(W)

  N = X.shape[0]

  for i in range(N):
    l = np.dot(X[i, :], W)
    l_softmax = np.exp(l)/np.sum(np.exp(l))
    loss -= np.log(l_softmax[y[i]])

    for j in range(W.shape[0]):
      for k in range(W.shape[1]):
        if k != y[i]:
          dW[j, k] += np.dot(X.T[j, i], l_softmax[k])
        else:
          dW[j, k] += np.dot(X.T[j, i], l_softmax[k] - 1)

  loss /= N
  loss += 0.5 * reg * np.sum(W**2)

  dW /= N
  dW += reg * W
  
  
  return loss, dW


def softmax_loss_vectorized(W, X, y, reg):
  """
  Softmax loss function, vectorized version.

  Inputs and outputs are the same as softmax_loss_naive.
  """
  # Initialize the loss and gradient to zero.
  loss = 0.0
  dW = np.zeros_like(W)
  num_train = X.shape[0]  #N

  scores = np.dot(X, W) # N*C 的矩阵 表示每个example被label为Ci的score
  exp_scores = np.exp(scores)
  prob_scores = exp_scores/np.sum(exp_scores, axis=1, keepdims=True)  # softmax 
  correct_log_probs = -np.log(prob_scores[range(num_train), y])  # 交叉熵损失函数 
  loss = np.sum(correct_log_probs)
  loss /= num_train
  loss += 0.5 * reg * np.sum(W**2)  # 正则化

  # grads
  dscores = prob_scores
  dscores[range(num_train), y] -= 1
  dW = np.dot(X.T, dscores)
  dW /= num_train
  dW += reg * W

  return loss, dW

