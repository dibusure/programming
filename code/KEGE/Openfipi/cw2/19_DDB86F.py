def f(s, h): # h is hod
    if s > 442 and h == 1: # петька выиграл
        return 0
    if s > 442 and h == 2: # выиграл ванька
        return 1
    if h > 2:
        return 0
    if h % 2 == 1: # ходит петька
        return f(s+1, h+1) + f(s+3, h+1) + f(2*s, h+1)
    else:
        return f(s+1, h+1) * f(s+3, h+1) * f(2*s, h+1)


if __name__ == "__main__":
    for s in range(1, 443):
        if f(s, 0):
            print(s)
            break
