# добавить 3 камня
# удвоить

# петя не за 1 ход
# обязан выиграть за 2

# s1+s2 >= 135
# s1 = 13
# s2 <= 121



def game(s1, s2, h):
    condit = s2*2 + s1 >= 135 or s1*2 + s2 >= 135 or s1 + s2 + 3 >= 135

    if (h == 1 or h == 2) and condit:
        return 0
    if h == 3 and condit:
        return 1
    if h > 3:
        return 0

    if h == 2: # Петя ~~может~~ должен выиграть своим вторым ходом независимо от того, как будет ходить Ваня.
        return game(s1*2,s2,h+1) * game(s1,s2*2,h+1) * game(s1+3,s2,h+1) * game(s1,s2+3,h+1)
    else:
        return game(s1*2,s2,h+1) + game(s1,s2*2,h+1) + game(s1+3,s2,h+1) + game(s1,s2+3,h+1)

for s in range(1, 121):
    if game(13, s, 1):
        print(s)
