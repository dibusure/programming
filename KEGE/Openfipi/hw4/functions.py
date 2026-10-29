#!/usr/bin/env python3
from math import sqrt, ceil
def is_prime(n):
    for x in range(2, ceil(sqrt(n))):
        if n % x == 0:
            return 0

    return 1

def find_all_divisors(n):
    a = []
    for x in range (1,n+1):
        if n % x == 0:
            a.append(x)
    return a

print(str(find_all_divisors(14))[1:-1])
print("Yep" if is_prime(25) else "Nope")
