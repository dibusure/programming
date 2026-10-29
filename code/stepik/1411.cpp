// даны шахматные клетки, определить может ли ферзь совершить такой ход
#include <iostream>

int main()
{
    int a = 0, b = 0, c = 0, d = 0;
    scanf("%d %d %d %d", &a, &b, &c, &d);
    if (a == c || b == d)
    { // ход ладьи
        printf("YES\n");
    }
    else if (a + b == c + d || a + d == b + c)
    { // ход слона
        printf("YES\n");
    }
    else if (b + 1 == d || b - 1 == d)
    { // этот и далее: ход короля
        if (a == c || a - 1 == c || a + 1 == c)
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