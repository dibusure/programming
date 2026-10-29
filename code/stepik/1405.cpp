// надо найти большее из трёх данных чисел

#include <iostream>

int main()
{
    int a = 0, b = 0, c = 0;
    scanf("%d %d %d", &a, &b, &c);
    if (a >= b)
    {
        if (a >= c)
        {
            printf("%d\n", a);
        }
        else if (a < c)
        {
            printf("%d\n", c);
        }
    }
    else
    { // a < b
        if (b >= c)
        {
            printf("%d\n", b);
        }
        else if (b < c)
        {
            printf("%d\n", c);
        }
    }

    return 0;
}