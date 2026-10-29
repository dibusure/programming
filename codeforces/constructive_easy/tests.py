import random
import string

t = 10
print(t)
for _ in range(t):
    n = 10000
    s = ''.join(random.choice(string.ascii_lowercase) for _ in range(n))
    print(n)
    print(s)

