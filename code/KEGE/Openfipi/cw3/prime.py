from math import sqrt, ceil
from pprint import pprint

def prime_decomposition(n):
    p = []
    a = []
    for x in range(2, ceil(sqrt(n))+1):
        while not(n % x):
            if x in p:
                a[-1]+=1
            else:
                p.append(x)
                a.append(1)

            n/=x
    return p, a
pprint(prime_decomposition(2))
