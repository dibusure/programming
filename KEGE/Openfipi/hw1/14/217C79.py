realx = 0
nineteenth = "0123456789ABCDEFGHI"
for x in nineteenth:
    a = f"98{x}79731"
    b = f"36{x}14"

    if (int(a, 19) + int(b,19)) % 18 == 0: # brackets matter
        realx = x
        break

a = f"98{realx}79731"
b = f"36{realx}14"
br = int(a, 19) + int(b,19)
print(br//18)
