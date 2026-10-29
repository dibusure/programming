// две шахматные клетки (a, b) и (c, d). Определить, можно ли попасть из первой клетки во вторую ходом короля
// видимо, если (a,b) = (c,d), то NO
#include <iostream>

int main()
{
    int a = 0, b = 0, c = 0, d = 0;
    scanf("%d %d %d %d", &a, &b, &c, &d);
    if (b + 1 == d || b - 1 == d)
    {
        if (a + 1 == c || a == c || a - 1 == c)
        {
            printf("YES\n");
        }
        else
        {
            printf("NO\n");
        }
    }
    else if (b == d)
    {
        if (a - 1 == c || a + 1 == c)
        {
            printf("YES\n");
        }
        else
        {
            printf("NO\n");
        }
    }
    else
    {
        printf("NO\n");
    }

    return 0;
}