// Реализовать алгоритм Евклида
#include <iostream>

int main()
{
    long long a = 0, b = 0;
    scanf("%lf %lf", &a, &b);
    if (a < b)
    {
        b = a + b;
        a = b - a;
        b = b - a;
    }
    printf("Sorted: (a;b)=(%lf;%lf)\n", a, b);

    while (a != 0 || b != 0)
    {
    }

    return 0;
}