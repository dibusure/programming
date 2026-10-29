def f(n):
    if n == 14:
        return 0
    if n == 39:
        return 1
    if n > 39:
        return 0

    ans = f(n+1) + f(n*2) + f(n*3)
    return ans


print(f(2))
