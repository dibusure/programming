f = open("./table.csv")
count = 0

def is_possible(arr):
    # li = [
    #     arr[0] + arr[1],
    #     arr[0] + arr[2],
    #     arr[0] + arr[3]
    # ]

    # for x in li:
    #     if x == sum(arr)//2:
    #         return True
    # return False


    # на самом деле всё намного легче
    a, b, c, d = arr[0], arr[1], arr[2], arr[3]

    return(a + b == c + d) or (a + c == b + d) or (a + d == b + c)

    # контрпример к штуке снизу:
    # 1 2 2 5
    # arr[0] + arr[1] = arr[0] + arr[2]
    # при этом эту штуку нельзя разбить на две пары чисел с равными суммами

    #return len(set(li)) != len(li)
    # ^ подсказка зеда: моё тоже сработало бы,
    # но так же красивее ёпта
    #if len(set(li)) == len(li):
    #    return False
    #else:
    #    return True

for x in f:
    arr = []
    for a in x.split(";"):
        arr.append(int(a))
    if max(arr) < sum(arr) - max(arr) and not(is_possible(arr)):
        count += 1


print(count)
