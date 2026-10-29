// Определите стандартное отклонение для данной последовательности натуральных чисел, завершающейся числом 0.
// формула: sqrt(((x1^2 + x2^2 + ... + xn^2)-(x1 + x2 + ... + xn)^2/n)/(n-1))

#include <iostream>
#include <math.h>

int main()
{
    int i = -1, count = 0;
    long long sum = 0, squares_sum = 0;

    while (i != 0)
    {
        scanf("%d", &i);
        ++count;
        sum += i;
        squares_sum += i * i;
    }
    count--;

    printf("%.11lf\n", sqrt((squares_sum - (double)(sum * sum) / (double)count) / ((double)(count)-1)));

    return 0;
}