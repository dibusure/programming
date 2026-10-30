#!/usr/bin/env python3
from functools import cache

@cache
def gcd(a,b): # greatest common divisor/factor НОД
    # euclid algorithm — remembered it by myself!!!!
    # TODO: need to prove once again
    if a == 0 or b == 0:
        return abs(a) if b == 0 else abs(b)
    return gcd(max(a,b) - min (a,b), min(a,b))


def lcm(a,b): # least/lowest common multiple
    # lcm * gcd = ab => lcm = ab/gcd
    return (a*b)//gcd(a,b)


a, b = map(int, input().split())
print(gcd(a,b), lcm(a,b))
