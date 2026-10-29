// Определите сумму всех элементов последовательности, завершающейся числом 0.
#include <iostream>

int main()
{
    int i = 1, sum = 0;
    while (i != 0)
    {
        scanf("%d", &i);
        sum += i;
    }
    printf("%d\n", sum);
    return 0;
}