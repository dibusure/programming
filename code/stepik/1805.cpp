// Дано число n, не превышающее 100. Создайте массив размером n×n и заполните его по следующему правилу. На главной диагонали должны быть записаны числа 0. На двух диагоналях, прилегающих к главной, числа 1. На следующих двух диагоналях числа 2, и т.д. Выведите полученный массив на экран, разделяя элементы массива пробелами.
#include <iostream>

int main()
{
    int n = 0;
    scanf("%d", &n);

    int a[n][n];
    for (int row = 0; row < n; ++row)
    {
        for (int column = 0; column < n; ++column)
        {
            if (row >= column)
            {
                a[row][column] = row - column;
            }
            else
            {
                a[row][column] = -row + column;
            }
        }
    }

    for (int row = 0; row < n; ++row)
    {
        for (int column = 0; column < n; ++column)
        {
            printf("%d ", a[row][column]);
        }
        printf("\n");
    }
}