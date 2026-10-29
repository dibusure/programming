def recursive(n, cnt = 0):
    if n == 141:
        return 1
    if n > 141:
        return 0


    if (n % 100 - n % 10)//10 < n % 10:
        cnt += recursive(n - n%100 + (n%10)*10 + (n%100 - n%10)//10)

    cnt += recursive(n+1)
    return cnt

print(recursive(100))
