// По данным числам n и m заполните двумерный массив размером n×m числами от 1 до n×m по спирали, выходящей из левого верхнего угла и закрученной по часовой стрелке, как показано в примере.
#include <iostream>
#include <algorithm>
#include <iomanip>

int main()
{
    int n = 0, m = 0, counter = 1;
    std::cin >> n >> m;
    int a[n][m];
    std::fill(a[0], a[0] + n * m, 0);

    int row = 0, column = 0;

    while (counter <= m * n)
    {
        for (; a[row][column] == 0 && column < m; ++counter)
        {
            a[row][column] = counter;
            ++column;
        }
        --column;
        ++row;

        for (; a[row][column] == 0 && row < n; ++counter)
        {

            a[row][column] = counter;
            ++row;
        }
        --row;
        --column;

        for (; a[row][column] == 0 && column >= 0; ++counter)
        {
            a[row][column] = counter;
            --column;
        }
        ++column;
        --row;

        for (; a[row][column] == 0 && row >= 0; ++counter)
        {
            a[row][column] = counter;
            --row;
        }
        ++row;
        ++column;
    }

    for (int row_n = 0; row_n < n; ++row_n)
    {
        for (int column_n = 0; column_n < m; ++column_n)
        {
            std::cout << std::setw(4) << a[row_n][column_n];
        }
        std::cout << std::endl;
    }
}