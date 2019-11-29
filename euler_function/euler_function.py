
"""
This is the implementation of Euler functions.
phi(n) - this is the quantity of such numbers in the segment [1; n], the greatest common factor of which with n is one.
If p is prime, there p-1 primes.
If p is prime, a is Natural, then phi(p**a) = p**a - p**(a-1)
If a and b are mutually prime then phi(a*b)  = phi(a)*phi(b)
"""

if __name__ == '__main__':
    n = int(input())
    result = n
    primes = [0 for i in range(2, n)]
    for i in range(2, int(n**0.5)):
        if n % i == 0:
            j = i*i
            primes[j] = 1
            while j < n:
                n /= i
            result -= result / i
    if n > 1:
        result -= result / n
    print('Number primes', sum(primes))
        
        
        
    
