from math import isqrt

A = 8_996_452
def f(n):
    divs = []
    for i in range(2, isqrt(n) + 1):
        if len(divs) > 2:
            return [0]

        while n % i == 0:
            if str(i).count("3") != 2:
                return [0]
            divs.append(i)
            n //= i

    if n > 1 and str(n).count("3") == 2:
        divs.append(n)

    return divs

for x in range(A, 10*A):
    li = f(x)
    if len(li) == 2:
        print(x, max(li))
