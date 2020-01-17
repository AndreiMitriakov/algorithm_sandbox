import numpy as np
import time

class Primes:
    @staticmethod
    def stream():
        yield 2
        pr = np.array([1, 2])
        i = 3
        while True:
            print(pr)
            pr_ = np.where(pr < np.sqrt(i)+1)
            print(pr_)
            pr_ = np.where(i % pr_[0] == 0)
            if len(pr_[0]) > 0:
                pass
            else:
                pr = np.append(pr, i)
                yield i
            i += 1
        
if __name__ == '__main__':
    t1 = time.time()
    gen = Primes.stream()
    for i in range(10):
        next(gen)
    t2 = time.time()
    print(t2 - t1)
