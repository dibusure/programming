input()

cards = input().split()
n = int(input())
rounds = []

for i in range(n):
    rounds.append(list(map(int, input().split())))

def sub(round):
    global cards

    unique = set()
    steps = 0

    for card in cards[round[0] - 1:round[1]]:
        steps += 1
        unique.add(card)

        if len(unique) == 9:
            return steps
    
    return -1

for round in rounds:
    print(sub(round))
