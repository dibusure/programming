// По данным числам n и m заполните двумерный массив размером n×m числами от 1 до n×m “змейкой”, как показано в примере.
#include <iostream>
#include <iomanip>

int main()
{
    int n = 0, m = 0, counter = 1;
    std::cin >> n >> m;
    int a[n][m];

    for (int row = 0; row < n; ++row)
    {
        if (row % 2 == 0) // default order
        {
            for (int column = 0; column < m; ++column)
            {
                a[row][column] = counter;
                ++counter;
            }
        }
        else // reverse order
        {
            for (int column = m - 1; column >= 0; --column)
            {
                a[row][column] = counter;
                ++counter;
            }
        }
    }

    for (int row = 0; row < n; ++row)
    {
        for (int column = 0; column < m; ++column)
        {
            std::cout << std::setw(4) << a[row][column];
        }
        std::cout << std::endl;
    }
}