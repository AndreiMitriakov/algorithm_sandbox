import itertools
import time

def next_smaller_1(n):
    array = tuple([int(d) for d in list(str(n))])
    permuts = list(itertools.permutations(array))
    if len(permuts) > 1000:
        permuts = permuts[:1000]
    permuts = [int(''.join(map(str, numList))) for numList in permuts]
    permuts.sort()
    ind = permuts.index(n)
    if ind == 0:
        return -1
    if permuts[ind-1] == n:
        return -1
    return permuts[ind-1]

tests = [(907, 790),
(531, 513),
(135, -1),
(2071, 2017),
(414, 144),
(123456798, 123456789),
(123456789, -1),
(1234567908, 1234567890)]

if __name__ == '__main__':
    t0 = time.time()
    for i, sample in enumerate(tests):
        val, tr = sample
        t1 = time.time()
        res = next_smaller_1(val)
        t2 = time.time()
        print('Test {}: {}'.format(i, res == tr), t2-t1)
    
    print('Time: {}'.format(t2 - t0))
