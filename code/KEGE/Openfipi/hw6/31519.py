#!/usr/bin/env python3
from math import isqrt

A = 1103285717

count = 0

for n in range(A, 10*A):
    if count > 4:
        break
    divs = []
    n_orig = n
    for i in range(2, isqrt(n)+1):
        while n % i == 0:
            divs.append(i)
            n //= i
        if len(divs) > 2:
            break
    if n > 1:
        divs.append(n)

    if len(divs) != 2:
        continue
    if "16" in str(divs[0]) and "16" in str(divs[1]):
        print(n_orig, min(divs[0], divs[1]))
        count += 1
