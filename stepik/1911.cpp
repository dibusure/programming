/*Дано натуральное число n > 1. Проверьте, является ли оно простым. Программа должна вывести слово YES, если число простое и NO, если число составное.
Решение оформите в виде функции IsPrime(n), которая возвращает True для простых чисел и False для составных чисел. Количество операций в программе должно быть пропорционально корню из n.*/
#include <iostream>
#include <math.h>

int MinDivisor(int n)
{
    for (int i = 2; i <= sqrt(n); ++i)
    {
        if (n % i == 0)
        {
            return i;
        }
    }

    return n;
}

bool IsPrime(int n)
{
    return MinDivisor(n) == n;
}

int main()
{
    int n = 0;
    std::cin >> n;
    if (IsPrime(n))
    {
        std::cout << "YES" << std::endl;
    }
    else
    {
        std::cout << "NO" << std::endl;
    }
}