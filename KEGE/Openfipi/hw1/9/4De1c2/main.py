f = open("./img1_1786621824.csv")
counter = 0
for x in f:
    arr = []
    for a in x.split(","):
        arr.append(int(a))
    if len(set(arr)) == len(arr) and 2*(min(arr) + max(arr)) > sum(arr) - min(arr) - max(arr):
        counter += 1

print(counter)
