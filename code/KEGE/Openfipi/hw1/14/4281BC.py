a = 9**7 + 3**21 - 9
def to_the_third(n):
    arr = []
    while n != 0:
        arr.append(str(n%3))
        n //= 3
    arr.reverse()
    return "".join(arr)

print(to_the_third(a).count("2"))
