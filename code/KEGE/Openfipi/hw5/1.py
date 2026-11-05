#!/usr/bin/env python3

S = 100_000_000
def count_odd_divisors(n):
    cunt = 0
    cunt_max = 0
    for x in range(3, n, 1): # all odd
       if n % x == 0:
           cunt += 1
           if cunt > 5: # an optimization for current problem
               return [0, 0]

           cunt_max = x

    return [cunt, cunt_max] # this is a list

count = 0
for n in range(S, 100*S):
    odd_divisors, max_odd_divisor = count_odd_divisors(n)
    if odd_divisors == 5:
        print(n, max_odd_divisor)
        count += 1

    if count > 4:
        break
