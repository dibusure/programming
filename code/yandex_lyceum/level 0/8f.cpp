#include <iostream>
#include <string.h>
#include <math.h>
#include <iomanip>

int main()
{
    std::cin.tie(0);
    std::cout.tie(0);
    double r = 0, h = 0, d = 0;
    std::string name;
    std::cin >> r >> h >> d >> name;

    double pi = 3.14159;
    double V = pi * r * r * h;

    std::cout << std::setprecision(2) << std::fixed;
    std::cout << "Объём бочки: " << V << ", фирмы: " << name << std::endl
              << std::setprecision(0) << std::fixed << "Количество бутылок: " << std::floor(V / d) << std::endl;
}