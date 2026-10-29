/* Дан квадратный двумерный массив размером n × n и число k. Выведите элементы k-й по счету диагонали ниже главной диагонали (т.е. если k = 1, то нужно вывести элементы первой диагонали, лежащей ниже главной, если k = 2, то второй диагонали и т.д.).
Значение k может быть отрицательным, например, если k = −1, то нужно вывести значение первой диагонали лежащей выше главной. Если k = 0, то нужно вывести элементы главной диагонали.
Программа получает на вход число n, не превосходящие 10, затем массив размером n × n, затем число k.*/

#include <iostream>

int main()
{
    int n = 0, k = 0;
    std::cin >> n;
    int a[n][n];
    for (int row = 0; row < n; ++row)
    {
        for (int column = 0; column < n; ++column)
        {
            std::cin >> a[row][column];
        }
    }

    std::cin >> k;

    if (k > 0)
    {
        int row = k, column = 0;
        while (row != n && column != n)
        {
            std::cout << a[row][column] << " ";
            ++row;
            ++column;
        }
    }
    else if (k == 0)
    {
        int row = 0, column = 0;
        while (row != n && column != n)
        {
            std::cout << a[row][column] << " ";
            ++row;
            ++column;
        }
    }
    else
    {
        int row = 0, column = -k;
        while (row != n && column != n)
        {
            std::cout << a[row][column] << " ";
            ++row;
            ++column;
        }
    }

    std::cout << std::endl;
}