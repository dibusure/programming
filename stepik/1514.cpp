// Дана последовательность натуральных чисел, завершающаяся числом 0. Определите, какое наибольшее число подряд идущих элементов этой последовательности равны друг другу. Если не нашлось ни одной пары, тройки и т.д. элементов, равных друг другу, то программа должна вывести число 1.
#include <iostream>

int main()
{
    int n = 0, counter = 1, max_counter = 1, last_num = 0;
    scanf("%d", &n);
    last_num = n;

    while (n != 0)
    {
        scanf("%d", &n);
        if (n == last_num)
        {
            ++counter;
            if (counter > max_counter)
            {
                max_counter = counter;
            }
        }
        else
        {
            last_num = n;
            counter = 1;
        }
    }

    printf("%d\n", max_counter);
    return 0;
}