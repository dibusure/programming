// даны три числа, упорядочить в порядке неубывания
#include <iostream>

int main()
{
    int a = 0, b = 0, c = 0;
    scanf("%d %d %d", &a, &b, &c);
    if (a < b)
    {
        if (a < c)
        {
            if (c > b)
            {
                printf("%d %d %d\n", a, b, c);
            }
            else
            {
                printf("%d %d %d\n", a, c, b);
            }
        }
        else
        {
            if (a > c)
            {
                printf("%d %d %d\n", c, a, b);
            }
            else
            {
                printf("%d %d %d\n", a, c, b);
            }
        }
    }
    else // a > b
    {
        if (b > c)
        {
            if (c > a)
            {
                printf("%d %d %d\n", a, c, b);
            }
            else // c < a
            {
                printf("%d %d %d\n", c, b, a);
            }
        }
        else
        { // b < c
            if (c > a)
            {
                printf("%d %d %d\n", b, a, c);
            }
            else
            { // c < a
                printf("%d %d %d\n", b, c, a);
            }
        }
    }

    return 0;
}