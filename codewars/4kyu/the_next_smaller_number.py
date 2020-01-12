#! /usr/bin/python3

def next_smaller(n):
    n = list(map(int, list(str(n))))
    # -1 if the list is in order
    if sorted(n) == n:
        return -1
    # Find a pivot point
    for i in range(len(n)-1):
        if n[len(n)-1-i] < n[len(n)-2-i]:
            break
    # Extract head and tail
    A = n[:len(n)-1-i]
    B = sorted(n[len(n)-1-i:])
    # Find the next smaller or equal digit
    j= 0
    while j < len(B) and A[-1] > B[j]:
        j += 1
    j -= 1

    A[-1], B[j] = B[j], A[-1]
    B = sorted(B, reverse=True)
    # if zero appears at the 0 position, it is not the next smaller number
    if A[0] == 0:
        return -1
    return int(''.join(list(map(str, A + B))))

if __name__ == '__main__':
    print(next_smaller(907) == 790)
    print(next_smaller(531) == 513)
    print(next_smaller(135) == -1)
    print(next_smaller(2071) == 2017)
    print(next_smaller(414) == 144)
    print(next_smaller(123456798) == 123456789)
    print(next_smaller(123456789) == -1)
    print(next_smaller(1234567908) == 1234567890)
