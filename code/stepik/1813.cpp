// По данным числам n и m заполните двумерный массив размером n×m числами от 1 до n×m “диагоналями”, как показано в примере.
/*
Sample Input:

3 5

Sample Output:

   1   2   4   7  10
   3   5   8  11  13
   6   9  12  14  15
*/
#include <iostream>
#include <algorithm>
#include <iomanip>

int main()
{
    int n = 0, m = 0, counter = 1;
    std::cin >> n >> m;
    int a[n][m];
    std::fill(a[0], a[0] + n * m, 0);

    for (int sum_of_coords = 0; sum_of_coords < n + m - 1; ++sum_of_coords)
    {
        for (int row = 0; row < n; ++row)
        {
            for (int column = 0; column < m; ++column)
            {
                if (row + column == sum_of_coords)
                {
                    a[row][column] = counter;
                    ++counter;
                }
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