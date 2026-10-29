dict = {"a": 1, "b": 1, "c": 1, "d": 2, "e": 2,
              "f": 3, "g": 3, "h": 3, "i": 4, "j": 4,
              "k": 5, "l": 5, "m": 5, "n": 6, "o": 6,
              "p": 7, "q": 7, "r": 7, "s": 8, "t": 8,
              "u": 9, "v": 9, "w": 9, "x": 0, "y": 0,
              "z": 0}
t = int(input())
calls = set()

while t > 0:
    call = list(input())
    for i in range(len(call)):
        call[i] = dict[call[i]]
        call[i] = str(call[i])
    call = ''.join(call)
    calls.add(call)
    t-=1

print(len(calls))