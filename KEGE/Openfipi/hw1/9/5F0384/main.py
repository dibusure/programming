f = open("./5F0384.csv")
count = 0
for x in f:
    arr = []
    for a in x.split(","):
        arr.append(int(a))
    #print(arr)
    if len(set(arr)) == len(arr) and 2*(max(arr) + min(arr)) > sum(arr) - min(arr) - max(arr):
        count += 1
print(count)
