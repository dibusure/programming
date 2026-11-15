from fnmatch import fnmatch
for x in range(0, 10**8, 271):
    if fnmatch(str(x), "12??15*6") and x % 271 == 0:
        print(x, x // 271)
