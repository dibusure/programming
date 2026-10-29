f = open("./table.csv")
sum_of_line = 0
for x in f:
    arr = []
    for a in x.split(","):
        arr.append(int(a))

    print(arr)
    if len(set(arr)) == len(arr) and 2*(min(arr) + max(arr)) > sum(arr) - min(arr) - max(arr):
        sum_of_line = sum(arr)
        break
print(sum_of_line)
