// Даны числа n и m. Заполните массив размером n × m в шахматном порядке: клетки одного цвета заполнены нулями, а другого цвета - заполнены числами натурального ряда сверху вниз, слева направо. В левом верхнем углу записано число 1.
#include <iostream>
#include <algorithm>
#include <iomanip>

int main()
{
    int n = 0, m = 0, counter = 1;
    std::cin >> n >> m;
    int a[n][m];
    std::fill(a[0], a[0] + n * m, 0);

    for (int row = 0; row < n; ++row)
    {
        for (int column = 0; column < m; ++column)
        {
            if ((row % 2 == 0 && column % 2 == 0) || (row % 2 == 1 && column % 2 == 1))
            {
                a[row][column] = counter;
                ++counter;
            }

            std::cout << std::setw(4) << a[row][column];
        }
        std::cout << std::endl;
    }
}