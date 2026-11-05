#!/usr/bin/env python3
from math import isqrt

# не считаем число и единицу (видимо)
A = 32_500_000

def sum_prime_divisors(n):
    sump = 0
    for i in range(2, isqrt(n)+1):
        while (n % i == 0):
            sump += i
            n //= i
    return sump

count = 0
for i in range(A, 100*A):
    S = sum_prime_divisors(i)
    if S != 0 and S % 145 == 0:
        print(i, S)
        count+=1
    if count >= 7:
        break
