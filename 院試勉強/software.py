import copy

def function(x, y, z):
    x = y
    x[0] = 5
    z[1] = y[2]

a = [1, 2, 3]
b = copy.deepcopy(a)
c = a

function(a, b, c)
print('a:', a)
print('b:', b)
print('c:', c)