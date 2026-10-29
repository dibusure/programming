// поменять столбцы i и j местами

#include <iostream>
#include <algorithm>

int main()
{
    int n = 0, m = 0, i = 0, j = 0;
    std::cin >> n;
    std::cin >> m;
    int a[n][m];

    for (int row = 0; row < n; ++row)
    {
        for (int column = 0; column < m; ++column)
        {
            std::cin >> a[row][column];
        }
    }

    std::cin >> i >> j;

    for (int row = 0; row < n; ++row)
    {
        std::swap(a[row][i], a[row][j]);
    }

    for (int row = 0; row < n; ++row)
    {
        for (int column = 0; column < m; ++column)
        {
            std::cout << a[row][column] << " ";
        }
        std::cout << std::endl;
    }
}