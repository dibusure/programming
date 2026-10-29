a = int(input())
b = int(input())
c = int(input())
d = int(input())
e = int(input())

# a < d, b < e; a < d; c < e; a < e
#
#

if (a <= d and b <= e) or (a <= d and c <= e) or (a <= e and b <= d) or (a <= e and c <= d):
    print("YES")
elif (b <= d and c <= e) or (b <= e and c <= d):
    print("YES")
else:
    print("NO")