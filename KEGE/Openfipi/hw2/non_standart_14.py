xmax = 0

def to_dec(a):
    a = str(a)
    ans = 0
    for x in range(0,len(a)):
        ans += 40**x * int(a[x])
    return ans


for x in range(0,41):
    a = to_dec(305172) + to_dec(x) * 10**4
    b = to_dec(264035) + to_dec(x) * 10**3
    if (a+b)%29==0:
        xmax=x
print(xmax)
