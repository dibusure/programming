// Последовательность состоит из натуральных чисел и завершается числом 0. Определите значение второго по величине элемента в этой последовательности, то есть элемента, который будет наибольшим, если из последовательности удалить наибольший элемент
#include <iostream>
#include <limits.h>

int main()
{
    int i = 0, pre_max = 0;
    scanf("%d", &i);
    int max = i;
    while (i != 0)
    {
        scanf("%d", &i);

        if (i >= max)
        {
            pre_max = max;
            max = i;
        }
        else if (i >= pre_max)
        {
            pre_max = i;
        }
    }

    printf("%d\n", pre_max);
    return 0;
}