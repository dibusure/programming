// посчитать число фибоначчи (с помощью циклов)
#include <iostream>

int main()
{
    int n = 0;
    scanf("%d", &n);
    int a = 0, b = 1;

    for (int i = 1; i < n; ++i)
    {
        if (b > a)
        {
            a = a + b;
        }
        else if (a >= b)
        {
            b = a + b;
        }
    }

    if (a > b)
    {
        printf("%d\n", a);
    }
    else
    {
        printf("%d\n", b);
    }

    return 0;
}