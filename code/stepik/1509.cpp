// Последовательность состоит из натуральных чисел и завершается числом 0. Определите значение наибольшего элемента последовательности.
#include <iostream>
#include <limits.h>

int main()
{
    int i = INT_MIN, max = INT_MIN;
    while (i != 0)
    {
        scanf("%d", &i);
        if (i > max)
        {
            max = i;
        }
    }
    printf("%d\n", max);
    return 0;
}