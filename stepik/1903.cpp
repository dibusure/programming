// Напишите функцию min(a, b), вычисляющую минимум двух чисел. Затем напишите функцию min4(a, b, c, d), вычисляющую минимум 4 чисел с помощью функции min. Считайте четыре целых числа и выведите их минимум.
#include <iostream>

int min(int a, int b)
{
    if (a > b)
    {
        return b;
    }
    else
    {
        return a;
    }
}

int min4(int a, int b, int c, int d)
{
    return min(min(a, b), min(c, d));
}

int main()
{
    int a = 0, b = 0, c = 0, d = 0;
    std::cin >> a >> b >> c >> d;
    std::cout << min4(a, b, c, d) << std::endl;
}