// В кинотеатре n рядов по m мест в каждом (n и m не превосходят 20). В двумерном массиве хранится информация о проданных билетах, число 1 означает, что билет на данное место уже продан, число 0 означает, что место свободно. Поступил запрос на продажу k билетов на соседние места в одном ряду. Определите, можно ли выполнить такой запрос.
#include <iostream>

int main()
{
    int n = 0, m = 0, k = 0, res = 0;
    std::cin >> n >> m;
    int a[n][m];
    for (int row = 0; row < n; ++row)
    {
        for (int column = 0; column < m; ++column)
        {
            std::cin >> a[row][column];
        }
    }
    std::cin >> k;

    int free_spaces_tmp = 0, free_spaces_max = -666;
    for (int row = 0; row < n; ++row)
    {
        for (int column = 0; column < m; ++column)
        {
            if (a[row][column] == 0)
            {
                ++free_spaces_tmp;
                if (free_spaces_tmp > free_spaces_max)
                {
                    free_spaces_max = free_spaces_tmp;
                }
            }
            else
            {
                free_spaces_tmp = 0;
            }
        }

        if (free_spaces_max >= k)
        {
            std::cout << row + 1 << std::endl;
            return 0;
        }
        else
        {
            free_spaces_max = -666;
            free_spaces_tmp = 0;
        }
    }

    if (free_spaces_max == -666)
    {
        std::cout << "0" << std::endl;
    }
}