// Дано положительное действительное число X. Выведите его первую цифру после десятичной точки.
#include <iostream>
#include <math.h>

int main()
{
    double x = 0;
    scanf("%lf", &x);
    printf("%d\n", ((int)trunc(x * 10)) % 10);
}