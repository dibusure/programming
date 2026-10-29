from itertools import product

for x in product(range(10), repeat=5):
    a,b1,b2,b3,c = x
    if int(f"89{a}6{b1}7{b2}9{b3}") % 9874 == 0:
        print(f"89{a}6{b1}7{b2}9{b3}", int(f"89{a}6{b1}7{b2}9{b3}") // 9874)
    if int(f"89{a}{c}6{b1}7{b2}9{b3}") % 9874 == 0:
        print(f"89{a}{c}6{b1}7{b2}9{b3}", int(f"89{a}{c}6{b1}7{b2}9{b3}") // 9874)
    if int(f"896{b1}7{b2}9{b3}") % 9874 == 0:
        print(f"896{b1}7{b2}9{b3}", int(f"896{b1}7{b2}9{b3}") // 9874)
