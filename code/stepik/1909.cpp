/*
Дано действительное положительное число a и целоe число n.
Вычислите a^n. Решение оформите в виде рекурсивной функции power(a, n).
*/
#include <iostream>

double power(double a, int n)
{
    if (n == 0)
    {
        return 1;
    }
    else if (n == 1)
    {
        return a;
    }
    else if (n > 1)
    {
        return a * power(a, n - 1);
    }
    else
    {
        return 1 / power(a, -n);
    }
}

int main()
{
    double a = 0;
    int n = 0;
    std::cin >> a >> n;
    std::cout << power(a, n) << std::endl;
}