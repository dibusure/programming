/*Дано натуральное число n > 1. Выведите его наименьший делитель, отличный от 1.
Решение оформите в виде функции MinDivisor(n). Количество операций в программе должно быть пропорционально корню из n.
Указание. Если у числа n нет делителя, меньшего n , то число n — простое и ответом будет само число n.*/
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

int main()
{
    int n = 0;
    std::cin >> n;
    std::cout << MinDivisor(n) << std::endl;
}