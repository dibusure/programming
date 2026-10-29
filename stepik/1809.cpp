/*
Дан двумерный массив размером n×m (n и m не превосходят 1000). Симметричный ему относительно главной диагонали массив называется транспонированным к данному. Он имеет размеры m×n: строки исходного массива становятся столбцами транспонированного, столбцы исходного массива становятся строками транспонированного.
*/
#include <iostream>

int main()
{
    int n = 0, m = 0;
    std::cin >> n >> m;
    int a[n][m];
    int b[m][n];

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
        for (int column = 0; column < n; ++column)
        {
            std::cout << b[row][column] << " ";
        }
        std::cout << std::endl;
    }
}