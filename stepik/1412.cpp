// даны две шахматные клетки, нужно определить, можно ли попасть из одной в другую конём в один ход
#include <iostream>

int main()
{
    int a = 0, b = 0, c = 0, d = 0;
    scanf("%d %d %d %d", &a, &b, &c, &d);

    if (a + 2 == c || a - 2 == c)
    { // вверх или вниз
        if (b + 1 == d || b - 1 == d)
        {
            printf("YES\n");
        }
        else
        {
            printf("NO\n");
        }
    }
    else if (b + 2 == d || b - 2 == d)
    { // вправо или влево
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