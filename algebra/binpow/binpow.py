import time

"""This is a realisation of pow operation with O(log(n)) time complexity.
   Realisation with complexity O(n) is also provided .
"""

def binpow(a, n):
    print('Binary pow {}**{}'.format(a, n), end = ' ')
    res = 1
    while n:
        if n & 1:
            res *= a
        a *= a
        n = n >> 1
    return res

def pow_(a, n):
    print('Linear pow {}**{}'.format(a, n), end = ' ')
    res = 1
    while n:
        res *= a
        n -= 1
    return res

if __name__ == '__main__':
    a = [2, 3, 4, 5]
    b = [5, 4, 3, 2]
    for i, j in zip(a, b):
        print(binpow(i, j))
    a = 2
    b = 10**6
    t0 = time.time()
    res = binpow(a, b)
    t1 = time.time()
    print('O(log(n)) time {}'.format(t1 - t0))
    t0 = time.time()
    res = pow_(a, b)
    t1 = time.time()
    print('O(n) time {}'.format(t1 - t0))    
    
