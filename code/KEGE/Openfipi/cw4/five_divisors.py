#!/usr/bin/env python3

# как будто можно пойти наоборот: перебирать 5 раз все числа от 1 до 100 (допустим) и чекать, будет ли число в отрезке

# \sigma(n) = 5 = (1+4) => в этом промежутке надо искать числа в 4 степени
# sqrt(3*10**8, 4) > 131
# sqrt(5*10**8, 4) > 149
from math import sqrt, ceil, floor

def if_prime(n):
    for x in range(2,ceil(sqrt(n))+1):
        if n%x == 0:
            return 0
    return 1

for x in range(ceil(sqrt(sqrt(3*10**8))),ceil(sqrt(sqrt(5*10**8)))+1):
    if if_prime(x):
        cube = x**3
        fourth = cube*x
        print(fourth, cube)
