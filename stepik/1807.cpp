/*
Дано число n, не превосходящее 10, и массив размером n × n. Проверьте, является ли этот массив симметричным относительно главной диагонали.
Выведите слово “YES”, если массив симметричный, и слово “NO” в противном случае.
*/

#include <iostream>

int main()
{
    int n = 0;
    std::cin >> n;
    int a[n][n];

    for (int row = 0; row < n; ++row)
    {
        for (int column = 0; column < n; ++column)
        {
            std::cin >> a[row][column];
        }
    }

    int counter = 0;

    for (int row = 0; row < n; ++row)
    {
        for (int column = 0; column < n; ++column)
        {
            if (column != row && a[row][column] == a[column][row])
            {
                ++counter;
            }
        }
    }

    if (counter == n * n - n)
    {
        std::cout << "YES" << std::endl;
    }
    else
    {
        std::cout << "NO" << std::endl;
    }
}