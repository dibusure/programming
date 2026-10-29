// Даны длины сторон треугольника. Вычислите площадь треугольника.
#include <iostream>
#include <math.h>

int main()
{
    double a = 0, b = 0, c = 0;
    scanf("%lf %lf %lf", &a, &b, &c);
    double p = (a + b + c) / 2;
    printf("%g\n", sqrt(p * (p - a) * (p - b) * (p - c)));
}