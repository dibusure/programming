#!/usr/bin/env python3

# trial division

def trial_division(n):
    factors = set()
    for x in range(2, int(n ** 0.5)+1):
        if n % x == 0:
            factors.add(x)
            n //= x
    if n != 1:
        factors.add(n)

    return factors

#print(trial_division(25), trial_division(42)) -> {5} {2, 3, 7}

def wheel_factorization(n):
    factors = set()

    if n % 2 == 0:
        factors.add(2)

    while n % 2 == 0:
        n //= 2

    for x in range(3, int(n ** 0.5)+1, 1): # starting with 3 and step is 1
        if n % x == 0:
            factors.add(x)
            n //= x
    if n != 1:
        factors.add(n)

    return factors

def count_divisors(n):
    res = 1
    for x in range(2, int(n ** 0.5)+1):
        if n % x == 0:
            p = 0
            while n % x == 0:
                p+=1
                n //= x
            res *= p+1

    if n != 1:
        res *= 2

    return res
#print(count_divisors(25), count_divisors(42)) -> 3 8

def sum_of_divisors(n):
    numerator = 1
    denominator = 1

    for x in range(2, int(n ** 0.5)+1):
        if n % x == 0:
            p = 0
            while n % x == 0:
                n //= x
                p += 1
            numerator *= x ** p - 1
            denominator *= x - 1

    return numerator//denominator

print(sum_of_divisors(24), sum_of_divisors(25))
