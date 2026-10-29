# теперь играем за ваньку
def d(s, h): # h is hod
#   if s > 442 and h == 2: # выиграл ванька
#       return 0
    if h % 2 == 0 and s > 442: # ямыванька выиграли
        return 1
    if h % 2 == 1 and s > 442: # выиграл петька
        return 0
    if h > 4:
        return 0
    if h % 2 == 1: # ходит петька
        return d(s+1, h+1) + d(s+3, h+1) + d(2*s, h+1)
    else:
        return d(s+1, h+1) * d(s+3, h+1) * d(2*s, h+1)

from importlib import import_module
module = import_module("19_DDB86F")


for s in range(1, 443):
    if d(s, 0) and not(module.f(s, 0)):
        print(s)
