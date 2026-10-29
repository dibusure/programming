// дано натуральное число А, надо определить каким числом фибоначчи оно является. Если не является, вывести -1
// a > 1
#include <iostream>

int main()
{
    int a = 0, counter = 0;
    scanf("%d", &a);
    int b = 0, c = 1;

    while (b <= a && c <= a)
    {
        if (c > b)
        {
            b = b + c;
        }
        else if (b >= c)
        {
            c = b + c;
        }
        ++counter;
    }

    if (b == a)
    {
        printf("%d\n", counter);
    }
    else if (c == a)
    {
        printf("%d\n", counter);
    }
    else
    {
        printf("-1\n");
    }
}