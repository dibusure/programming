f = open("./demo_17.txt")
a, b = 0, 0
min_n = 100001
ans = 0

for x in f:
    min_n = min(int(x), min_n)


f.seek(0)

sum = 0

for x in f:
    b = int(x)

    if a == 0:
        a = b
        continue

    if b % 33 == min_n or a % 33 == min_n:
        ans += 1
        sum = max(a+b, sum)


    a = b

print(ans, sum)
