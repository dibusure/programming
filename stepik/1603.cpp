// Дано положительное действительное число X. Выведите его дробную часть.
#include <iostream>
#include <math.h>

int main()
{
    float a;
    scanf("%f", &a);
    printf("%g\n", a - trunc(a));
}