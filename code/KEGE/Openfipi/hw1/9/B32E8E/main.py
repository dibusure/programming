f = open("table.csv")
count = 0
for x in f:
    arr = []
    for a in x.split(";"):
        arr.append(int(a))
    if len(set(arr)) == len(arr) and max(arr) < sum(arr) - max(arr):
        count += 1

print(count)
