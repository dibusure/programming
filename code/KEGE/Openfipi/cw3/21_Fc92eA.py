# ваня может выиграть первым или вторым ходом

def otd(s1,s2,h): # vanya wins in any circumstances
    cond = s1+s2*2 >= 135 or s1*2+s2 >= 135 or s1+s2+3 >= 135
    if h > 2:
        return 0

    if cond:
        if h%2 == 0:
            return 1
        return 0

    if h == 2:
        return otd(s1*2,s2,h+1) * otd(s1, s2*2, h+1) * otd(s1+3, s2, h+1) * otd(s1, s2+3, h+1) # гарантированная победыа вани
    return otd(s1*2,s2,h+1) * otd(s1, s2*2, h+1) * otd(s1+3, s2, h+1) * otd(s1, s2+3, h+1) # ход петькин не контроллируем

def game(s1, s2, h):
    cond = s1+s2*2 >= 135 or s1*2+s2 >= 135 or s1+s2+3 >= 135

    if h > 4:
        return 0

    if cond:
        if h%2 == 0:
            return 1
        return 0

    if h == 2 and otd(s1,s2,h) == 1: # у Вани **есть** стратегии, которая позволит ему гарантированно выиграть первым ходом.
        return 0

    if h == 2 or h == 4:
        return game(s1*2,s2,h+1) + game(s1, s2*2, h+1) + game(s1+3, s2, h+1) + game(s1, s2+3, h+1)

    return game(s1*2,s2,h+1) * game(s1, s2*2, h+1) * game(s1+3, s2, h+1) * game(s1, s2+3, h+1) # ход пети выбирать мы не можем


for s in range(1,121):
    if game(13,s,1):
        print(s)
