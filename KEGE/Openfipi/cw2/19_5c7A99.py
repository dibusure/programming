# первый ход: петя удваивает в куче, в которой больше (!)
# второй ход: ваня выигрывает <=> s1 + s2 >= 135

def f(s1, s2, h):
    if h == 1 and s2 + s1 >= 135:
        return 0
    if h == 2 and s2 + s1 >= 135:
        return 1 # наша победа
    if h > 2:
        return 0 # затянулось

    return f(s1, s2*2, h+1) + f(s1, s2 + 3, h+1) + f(s1*2, s2, h+1) + f(s1 + 3, s2, h + 1)

for s2 in range(1, 122):
    if f(13, s2, 0):
        print(s2)
        break
