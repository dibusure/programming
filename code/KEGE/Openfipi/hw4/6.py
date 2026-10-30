#!/usr/bin/env python3
def sum_of_divisors(n):
    sum = 0
    for i in range(1, n): # меньших n
        if n % i == 0:
            sum += i
    return sum


N = int(input())
for x in range(1, N+1): # не превосходящие
    if sum_of_divisors(x) == x:
        print(x)
