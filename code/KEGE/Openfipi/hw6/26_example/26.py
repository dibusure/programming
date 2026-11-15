data = []
with open('26_31520.txt') as f:
#with open('./example.txt') as f:
    for line in f:
        data.append(list(map(str, line.split())))

n, buf_size= int(data[0][0]), int(data[0][1])
#print(buf_size, n)
data = data[1:] # теперь они не нужны нам в дате

# строка типа: время, id, объём данных — всё в строках для удобства времени
# строки «журнала» начинаются с первого индекса!!!


scores = {}
maxs = 0
maxid = 0
for line in data:
    if line[1] in scores:
        scores[line[1]] += int(line[2])
    else:
        scores[line[1]] = int(line[2])

    if scores[line[1]] > maxs:
        maxid = line[1]
        maxs = scores[line[1]]

print(maxid, end=" ")

# ---

backups = [] # я тут set сначала написал — не надо так делать

sum = 0
for line in range(0, n):
    if data[line][0] >= "12:00:00":
        break

    if (sum + int(data[line][2])) <= buf_size:
        sum += int(data[line][2])
    else:
        backups.append(sum)
        sum = 0
        sum += int(data[line][2])

print(sorted(backups)[-1] + sorted(backups)[-2])
