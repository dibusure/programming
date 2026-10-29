// Дан прямоугольный массив размером n×m. Поверните его на 90 градусов по часовой стрелке, записав результат в новый массив размером m×n.
#include <iostream>
#include <algorithm>

int main()
{
    int n = 0, m = 0;
    std::cin >> n >> m;
    double a[n][m];
    double b[m][n];

    for (int row = 0; row < n; ++row)
    {
        for (int column = 0; column < m; ++column)
        {
            std::cin >> a[row][column];
            b[column][row] = a[row][column];
        }
    }

    for (int row = 0; row < m; ++row)
    {
        for (int column = 0; column < n / 2; ++column)
        {
            std::swap(b[row][column], b[row][n - 1 - column]);
        }
    }

    for (int row = 0; row < m; ++row)
    {
        for (int column = 0; column < n; ++column)
        {
            std::cout << b[row][column] << " ";
        }
        std::cout << std::endl;
    }
}