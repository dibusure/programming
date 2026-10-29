# пришлось «вспомнить», как переводить в систему счисления..
def to_the_fifth(n):
    arr = []
    while n != 0:
       arr.append(str(n%5))
       n //= 5
    arr.reverse()
    k = int("".join(arr))
    return k

def how_many_zeros(n):
    if n % 10 != 0:
        return 0
    else:
        return 1 + how_many_zeros(n//10)

zeros_max = 0
x_max = 0

for x in range(1, 2030+1):
    a = 5**150 + 5**100 - x
    k = to_the_fifth(a)
    if (how_many_zeros(k) >= zeros_max): # тут был небольшой заёб c >=, потому что значение x нужно тоже НАИБОЛЬШЕЕ
        x_max = x
        zeros_max = how_many_zeros(k)

print(x_max)
