// вывести количество повторяющихся чисел, если даны три
#include <iostream>

int main()
{
    int a = 0, b = 0, c = 0, counter = 0;
    scanf("%d %d %d", &a, &b, &c);
    if (a == b && a == c)
    {
        counter = 3;
    }
    else if (a == b || b == c || c == a)
    {
        counter = 2;
    }

    printf("%d\n", counter);
    return 0;
}