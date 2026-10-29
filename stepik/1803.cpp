// Найдите индексы первого вхождения максимального элемента.
#include <vector>
#include <iostream>

int main()
{
    int m = 0, n = 0, max = 0, max_r = -1, max_c = -1;
    scanf("%d %d", &n, &m);
    int a[n][m];

    for (int row = 0; row < n; ++row)
    {
        for (int column = 0; column < m; ++column)
        {
            scanf("%d", &a[row][column]);

            if (max_r == -1 && max_c == -1)
            {
                max = a[row][column];
                max_r = 0;
                max_c = 0;
            }
            else if (a[row][column] > max)
            {
                max = a[row][column];
                max_r = row;
                max_c = column;
            }
        }
    }

    printf("%d %d\n", max_r, max_c);
}