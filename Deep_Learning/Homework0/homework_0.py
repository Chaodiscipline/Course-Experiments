import numpy as np
import torch

###################################
# 2 Vectorization
###################################


def vectorize_sumproducts(a, b):
    """
     Takes two 1-dimensional arrays and sums the products of all the pairs.
    """
    return np.dot(a, b)


def vectorize_Relu(a):
    """
    Takes one 2-dimensional array and apply the relu function on all the values of the array.
    """
    return (a > 0)*a


def vectorize_PrimeRelu(a):
    """
    Takes one 2-dimensional array and apply the derivative of relu function on all the values of the array.
    """
    return (a > 0)*a


# test
print("vectorization test\n")
x1 = np.array([1, 2, 3, 4])
y1 = np.array([2, 2, 3, 3])
print("x1 = ", x1, ", y1 = ", y1)
print("vectorize_sumproducts of x1 and y1: \n", vectorize_sumproducts(x1, y1))

z1 = np.array([[1, -1], [-3, 4]])
print("z1 = ", z1)
print("vectorize_Relu of z1: \n", vectorize_Relu(z1))
print("vectorize_PrimeRelu of z1: \n", vectorize_PrimeRelu(z1))
print("\n\n")


######################################
# 3 Variable length
######################################

# Slice

def Slice_fixed_point(data, a, b):
    """
    Takes one 3-dimensional array with the starting position and the length of the output instances.
    Your task is to slice the instances from the same starting position for the given length.
    b is the starting position and a is the length.
    """
    return data[:, b:b+a]


def slice_last_point(data, a):
    """
     Takes one 3-dimensional array with the length of the output instances.
     Your task is to keeping only the l last points for each instances in the dataset.
    """
    # s = []
    # for i in data:
    #     s.append(i[-a:])
    # return s
    return data[:, -a:]


def slice_random_point(data, a):
    """
     Takes one 3-dimensional  array  with  the  length  of the output instances.
     Your task is to slice the instances from a random point in each of the utterances with the given length.
     Please use function numpy.random.randint for generating the starting position.
    """
    b = np.random.randint(0, data.shape[1])
    print("starting point:", b)
    return data[:, b:b + a]


# test
print("slicing test\n")
x2 = np.arange(1, 37).reshape(3, 4, 3)
print('x2 = ', x2)
print("Slice_fixed_point of x2 with start 1 and length 2: \n", Slice_fixed_point(x2, 2, 1))
print("slice_last_point of x2 with length 2: \n", slice_last_point(x2, 2))
print("slice_random_point of x2 with length 2: \n", slice_random_point(x2, 2))
print("\n\n")


# Padding

def pad_pattern_end(data):
    """
    Takes one 3-dimensional array.
    Your task is to pad the instances from the end position as shown in the example below.
    That is, you need to pad the reflection of the utterance mirrored along the edge of the array.
    """
    ymax = 0
    zmax = 0
    for j in data:
        if (len(j) > ymax):
            ymax = len(j)
        for k in j:
            if (len(k) > zmax):
                zmax = len(k)
    # print("ymax: ", ymax)
    # print("zmax: ", zmax)

    for m in range(len(data)):
        for n in range(len(data[m])):
            data[m][n] = np.pad(data[m][n], (0, zmax - len(data[m][n])), 'symmetric')
            # print(data[m][n])
        data[m] = np.pad(data[m], ((0, ymax - len(data[m])), (0, 0)), 'symmetric')
        # print(data[m])
    return data


def pad_constant_central(data, cval):
    """
     Takes one 3-dimensional array with the constant value of padding.
     Your task is to pad the instances with the given constant value while maintaining the array at the center of the padding.
    """
    ymax = 0
    zmax = 0
    for j in data:
        if (len(j) > ymax):
            ymax = len(j)
        for k in j:
            if (len(k) > zmax):
                zmax = len(k)
    # print("ymax: ", ymax)
    # print("zmax: ", zmax)

    for m in range(len(data)):
        for n in range(len(data[m])):
            if (zmax - len(data[m][n]))%2==0:
                l = r = (zmax - len(data[m][n]))//2
            else:
                l = (zmax - len(data[m][n])-1)//2
                r = zmax - len(data[m][n]) - l
            data[m][n] = np.pad(data[m][n], (l, r), 'constant', constant_values=cval)
            # print(data[m][n])

        if (ymax - len(data[m])) % 2 == 0:
            l = r = (ymax - len(data[m])) // 2
        else:
            l = (ymax - len(data[m]) - 1) // 2
            r = ymax - len(data[m]) - l
        data[m] = np.pad(data[m], ((l, r), (0, 0)), 'constant', constant_values=cval)
        # print(data[m])
    return data


# test
print("padding test\n")
x3 = np.array([[[1, 2, 3, 4],
                [5, 6, 7]],
              [[8, 9],
               [10, 11],
               [12, 13],
               [14, 15]]])
print("x3 = \n", x3)
print("pad_pattern_end of x3: \n", pad_pattern_end(x3))
x3 = np.array([[[1, 2, 3, 4],
                [5, 6, 7]],
              [[8, 9],
               [10, 11],
               [12, 13],
               [14, 15]]])
print("pad_constant_central of x3 with cval = 0: \n", pad_constant_central(x3, 0))
print("\n\n")


#######################################
# PyTorch
#######################################

# numpy&torch

def numpy2tensor(a):
    """
    Takes a numpy ndarray and converts it to a PyTorch tensor.
    Function torch.tensor is one of the simple ways to implement it but please do not use it this time.
    """
    return torch.from_numpy(a)


def tensor2numpy(a):
    """
    Takes a PyTorch tensor and converts it to a numpy ndarray.
    """
    return a.numpy()


# test
print("numpy&torch test\n")
x4 = np.array([[1, 2, 3], [4, 5, 6]])
tensor_x4 = numpy2tensor(x4)
print("x4 = \n", x4)
print("convert x4 to tensor: tesor_x4 = \n", tensor_x4)
print("convert tensor_x4 to numpy: numpy_x4 = \n", tensor2numpy(tensor_x4))
print("\n\n")


# Tensor Sum-products

def Tensor_Sumproducts(a,b):
    """
    you are to implement the function tensor sumproducts that takes two tensors as input.
    returns the sum of the element-wise products of the two tensors.
    """
    return a.dot(b)

# test
print("tensor_sumproducts test\n")
x5 = torch.Tensor([-1, 2, 3])
x6 = torch.Tensor([4, 5, 6])
print("x5 = \n", x5)
print("x6 = \n", x6)
print("Tensor_Sumproducts of x5 and x6: ", Tensor_Sumproducts(x5, x6))
print("\n\n")


# Tensor ReLu and ReLu prime


def Tensor_Relu(s):
    """
    Takes one 2-dimensional tensor and apply the relu function on all the values of the tensor.
    """
    s[s < 0] = 0
    return s


def Tensor_Relu_prime(s):
    """
    Takes one 2-dimensional tensor and apply the derivative of relu function on all the values of the tensor.
    """
    s[s <= 0] = 0
    s[s > 0] = 1
    return s


# test
print("relu test\n")
x6 = torch.Tensor([[4, 5, -9],
                   [7, -1, 6]])
print("x6 = \n", x6)
print("Tensor_Relu of x6:\n", Tensor_Relu(x6))
print("Tensor_Relu_prime of x6: ", Tensor_Relu_prime(x6))

