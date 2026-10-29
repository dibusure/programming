/*
N кеглей выставили в один ряд, занумеровав их слева направо числами от 1 до N. Затем по этому ряду бросили K шаров, при этом i-й шар сбил все кегли с номерами от l_i до r_i включительно. Определите, какие кегли остались стоять на месте.
Формат входных данных
Программа получает на вход количество кеглей N и количество бросков K. Далее идет K пар чисел l_i, r_i, при этом 1 ≤ l_i, r_i ≤ N.
Формат выходных данных
Программа должна вывести последовательность из N символов, где j-й символ есть “I”, если j-я кегля осталась стоять, или “.”, если j-я кегля была сбита.
*/
#include <vector>
#include <iostream>

int main()
{
    int N = 0, K = 0, start_of_range = 0, end_of_range = 0;
    scanf("%d %d", &N, &K);
    std::vector<char> skittles(N, 'I'); // сразу можно заполнить вектор!

    for (int i = 0; i < K * 2; ++i)
    {
        if (i % 2 == 0)
        {
            start_of_range = 0;
            scanf("%d", &start_of_range);
        }
        else
        {
            end_of_range = 0;
            scanf("%d", &end_of_range);

            if (start_of_range != 0 && end_of_range != 0)
            {
                for (int i = start_of_range - 1; i < end_of_range; ++i)
                {
                    skittles[i] = '.';
                }
            }
        }
    }

    for (int i = 0; i < N; ++i)
    {
        printf("%c", skittles[i]);
    }
    printf("\n");
}