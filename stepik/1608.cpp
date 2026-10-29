// Определите среднее значение всех элементов последовательности, завершающейся числом 0.
#include <iostream>

int main()
{
    int i = 0, quantity = 0, sum = 0;
    scanf("%d", &i);
    sum += i;
    while (i != 0)
    {
        scanf("%d", &i);
        ++quantity;
        sum += i;
    }

    printf("%.11lf\n", (double)sum / (double)quantity);
    return 0;
}