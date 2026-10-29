// решить квадратное уравнение с действительными коэфами, a!=0 обязательно
#include <iostream>
#include <math.h>

int main()
{
    double a = 0, b = 0, c = 0;
    scanf("%lf %lf %lf", &a, &b, &c);
    double d = b * b - 4 * a * c;

    if (d == 0)
    {
        printf("%lf\n", -b / (2 * a));
    }
    else if (d > 0)
    {
        double x1 = (-b + (double)(sqrt(d))) / (2 * a), x2 = (-b - (double)(sqrt(d))) / (2 * a);
        if (x1 < x2)
        {
            printf("%g %g\n", x1, x2);
        }
        else
        {
            printf("%g %g\n", x2, x1);
        }
    }

    return 0;
}