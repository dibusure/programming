from collections import deque

n = int(input())
q = int(input())
de = deque(range(1,n+1))
while q > 0:
    i = int(input())
    de.remove(i)
    de.append(i)

    q -= 1

print(' '.join(map(str,de)))