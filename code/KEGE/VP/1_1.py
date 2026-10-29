a = int('118', 9) + int('117', 8) + int('116', 7) + int('115', 6)
b = -int('112', 3) - int('113', 4) - int('114', 5) - int('10010111',2)

for x in range(1, 11):
    a_tmp = a + int('1111', x+1)
    b_tmp = b + int(f"{x}{x}1", 12)
    if a_tmp==b_tmp:
        print(x)