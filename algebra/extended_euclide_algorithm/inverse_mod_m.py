
"""
Reverse element modulo m using extended gcd.
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

def reverse_modulo(a, m):
    g, x, y = extended_gcd(a, m)
    if g != 1:
        print("No solution")
        return None
    else:
        x = (x % m  + m) % m
        return x

if __name__ == '__main__':
    a = 84
    b = 53
    reverse = reverse_modulo(a, b)
    print(reverse) 
