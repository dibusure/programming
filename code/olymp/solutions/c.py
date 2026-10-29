input()
arr = list(map(int, input().split()))
arr.sort()

s = 0

for i in range(len(arr) // 2):
    a, b = arr[i * 2], arr[i * 2 + 1]

    if a != b:
        s += b - a - 1

print(s)
