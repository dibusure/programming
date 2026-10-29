# 18 = 10 digits + 8 letters ('H')
for p in range (18, 100):
    a = int('22A12E', p) + int('2F1391', p) - int('1H05D0', p)

    if (a%19) == 0:
        print(a//19)
        break