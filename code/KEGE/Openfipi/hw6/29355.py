from fnmatch import *
n = "89*6?7?9?"
for x in range(0, 10**10+1, 9874):
    if fnmatch(str(x), n) and x % 9874 == 0:
        print(x, x // 9874)
