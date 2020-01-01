
"""
This is the implementation of extended Euclid algorithm.
The original Euclid alogrithm allows to the GCD.
Its extended version searches for coefficients x and y so that:
a*x + b*y = gcd(a, b)
"""

def extended_gcd(a, b, x=None, y=None): 
    # Base Case 
    if a == 0 :  
        x = 0
        y = 1
        return b, x, y
          
    gcd, x1, y1 = extended_gcd(b%a, a) 
  
    # Update x and y using results of recursive 
    # call 
    x = y1 - (b/a) * x1 
    y = x1 
  
    return gcd, x, y

if __name__ == '__main__':
    a = 35
    b = 15
    g, x, y = extended_gcd(a, b)
    print(g, x, y) 
