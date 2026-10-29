#!/usr/bin/env python3
from math import ceil, sqrt

def prime_divisors_powers(n):
    div = []
    powers = []

    for x in range(2, ceil(sqrt(n))+1):
        if (n%x == 0):
            div.append(x)
            ind = len(powers)
            powers.append(1)
            n/=x

            while n%x == 0:
                powers[ind] += 1
                n/=x
    #return list(zip(div, powers))
    return powers

def tau(n): # amount of all positive divisors — there's a formula
    res = 1
    for x in prime_divisors_powers(n):
        res *= (1+x)
    return res
def sigma(n): # sum of all positive divisors
    sum = 0
    for x in range(1, n+1):
        if n%x == 0:
            sum += x
    return sum


n = int(input())
print(tau(n), sigma(n))

#print(prime_divisors_powers(n))
