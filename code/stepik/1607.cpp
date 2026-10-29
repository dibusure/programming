// Процентная ставка по вкладу составляет P процентов годовых, которые прибавляются к сумме вклада через год. Вклад составляет X рублей Y копеек. Определите размер вклада через K лет.
#include <math.h>
#include <iostream>

int main()
{
    int p = 0, k = 0, x = 0, y = 0;

    scanf("%d %d %d %d", &p, &x, &y, &k);
    double sum = 100 * x + y;

    for (int i = 0; i < k; ++i)
    {
        sum += sum * ((double)p / 100);
        sum = trunc(sum);
    }

    x = sum / 100;
    y = sum - x * 100;
    printf("%d %d\n", x, y);
}