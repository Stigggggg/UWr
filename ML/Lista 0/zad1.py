import numpy as np

# Zad.1
# a)
a = 10
b = 2.5e23
c = 2 + 3j
d = np.exp(2j * np.pi / 3)

# b)
aVec = np.array([3.14, 15, 9, 26])
bVec = np.linspace(5, -5, 51)
cVec = np.logspace(0, 1, 100)
dVec = np.array(list("Hello"))

# c)
aMat = np.full((9, 9), 2)
bMat = np.diag(np.concatenate((np.arange(1, 6), np.arange(4, 0, -1))))
print(bMat)
cMat = np.arange(1, 101).reshape((10, 10)).T
dMat = np.full((3, 4), np.nan)
eMat = np.array(([13, -1, 5], [-22, 10, -87]))
fMat = np.floor(np.random.rand(3, 3) * 6 - 3)

# d)
multMat = np.outer(np.arange(0, 10), np.arange(0, 10))
print(multMat)

# e)
xVec = (1 / np.sqrt(2 * np.pi * 2.5 ** 2)) * np.exp(-(cVec ** 2) / (2 * np.pi * 2.5 ** 2))
yVec = np.log10(1/cVec)

# f)
xMat = np.dot(np.arange(0, 7).reshape(7, 1), np.arange(0, 61, 10).reshape(1, 7))
yMat = np.dot(np.arange(0, 61, 10).reshape(1, 7), np.arange(0, 7).reshape(7, 1))

# g)
def ismagic(A):
    s = np.sum(A, axis=1)[0]
    return (np.all(np.sum(A, axis=0) == s) and np.all(np.sum(A, axis=1) == s) and np.sum(np.diag(A)) == s and np.sum(np.diag(np.fliplr(A))) == s)

print(xVec)
print(ismagic(np.array([[2,7,6],[9,5,1],[4,3,8]])))