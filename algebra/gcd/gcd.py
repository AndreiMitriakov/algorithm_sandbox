import time

"""Euclidean algorithm for greatest common diviser searching"""

def gcd(a, b):
    print('GCD of {} and {}'.format(a, b), end = ' ')
    while b:
        a %= b
        a, b = b, a
    return a

if __name__ == '__main__':
    a = [2, 35, 466, 5411]
    b = [5, 45, 354, 2113]
    for i, j in zip(a, b):
        t0 = time.time()
        print('is {} in time {}'.format(gcd(i, j), time.time()-t0))

