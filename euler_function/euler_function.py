
"""
This is the implementation of Euler functions.
phi(n) - this is the quantity of such numbers in the segment [1; n], the greatest common factor of which with n is one.
If p is prime, there p-1 primes.
If p is prime, a is Natural, then phi(p**a) = p**a - p**(a-1)
If a and b are mutually prime then phi(a*b)  = phi(a)*phi(b)
"""

if __name__ == '__main__':
    n = int(input())
    # Find canonical form of n where n = p1**a1 * p2**a2 ...
    canonical = {}
    for i in range(2, n+1):
        if n % i == 0:
            canonical[i] = 0
            while n % i == 0:
                n /= i
                canonical[i] += 1
            if n == 1:
                break
    phi_n = 1
    # Calculate Euler function
    for k,v in canonical.items():
        phi_n *= (k**v-k**(v-1))
    print("Canonical form:", canonical)
    print("Euler function:", phi_n)



