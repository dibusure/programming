from sys import *
from functools import *
setrecursionlimit(99999)

@cache
def F(n):
    if n < 43:
        return G(n+4)
    elif n >= 43:
        return 2*F(n-2) - F(n-4) + 2

@cache
def G(n):
    if n < 11240:
        return G(n+3) + 2
    elif n >= 11240:
        return Q(n)

@cache
def Q(n):
    if n < 21:
        return n + 4
    elif n >= 21:
        return Q(n-4) + 2

print(F(2026))
