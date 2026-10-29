// Последовательность состоит из натуральных чисел и завершается числом 0. Определите, какое количество элементов этой последовательности, равны ее наибольшему элементу.
#include <iostream>
#include <limits.h>

int main()
{
    int i = 0, max = INT_MIN, counter = 1;
    scanf("%d", &i);
    while (i != 0)
    {
        if (i > max)
        {
            max = i;
            counter = 1;
        }
        else if (i == max)
        {
            ++counter;
        }
        scanf("%d", &i);
    }

    printf("%d\n", counter);
    return 0;
}