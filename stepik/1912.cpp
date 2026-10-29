/*
алгос быстрого возведения в степень:
a^n = (a^2)^(n/2) при n = 0 (mod 2)
a^n = a*a^n-1 при n = 1 (mod 2)
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
    else if (n % 2 == 0)
    {
        return power(a * a, n / 2);
    }
    else
    {
        return a * power(a, n - 1);
    }
}

int main()
{
    double a = 0;
    int n = 0;
    std::cin >> a >> n;
    std::cout << power(a, n) << std::endl;
}