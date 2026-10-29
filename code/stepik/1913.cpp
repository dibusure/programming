/*
Дана последовательность чисел, завершающаяся числом 0. Найдите сумму всех этих чисел, не используя цикл.
*/

// Первая (плохая) версия кода:

/*
#include <iostream>

void sum_of_line(int *sum)
{
    int tmp = 0;
    std::cin >> tmp;
    if (tmp == 0)
    {
        return;
    }
    else
    {
        *sum += tmp;
        sum_of_line(sum);
    }
}

int main()
{
    int sum = 0;
    sum_of_line(&sum);
    std::cout << sum << std::endl;
}*/

#include <iostream>

int sum()
{
    int tmp = 0;
    std::cin >> tmp;
    if (tmp == 0)
    {
        return 0;
    }
    else
    {
        return tmp + sum();
    }
}

int main()
{
    std::cout << sum() << std::endl;
}