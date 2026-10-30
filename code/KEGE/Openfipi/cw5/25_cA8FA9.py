from math import isqrt
from functools import cache
N = 2_626_695_891

@cache
def is_prime(a):
    for x in range(2, isqrt(a)):
        if a % x == 0:
            return 0

    return 1

def check(n):
    f = 0
    s = 0

    for x in range(67, isqrt(n)):
        if n%x==0: # нашли один простой делитель, в котором точно есть 67
            f = x
            break

    if str(f).count("67")!=1:
        return 0

    if f == 0:
        return 0

    s = n // f
    if is_prime(s) and str(s).count("67")==1:
        return f

    return 0


cunt = 0
for x in range(N+1, 9*10**9):
    res = check(x)
    if res != 0:
        print(x, res)
        cunt += 1

    if cunt > 5:
        break
