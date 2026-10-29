/* СЛАУ имеет ровно одно решение, вывести решение
 ax + by = e
 cx + dy = f

 => x = (e-by)/a
 ==> c * (e-by)/a + dy = f; ce - cby + dya = fa; y(da-cb) = fa-ce; y = (fa-ce)/(da-cb)
*/
#include <iostream>

int main()
{
    double a = 0, b = 0, c = 0, d = 0, e = 0, f = 0;
    scanf("%lf %lf %lf %lf %lf %lf", &a, &b, &c, &d, &e, &f);
    double x = 0, y = 0;

    if (a == 0)
    {
        y = e / b;
        x = (f - d * y) / c;
    }
    else
    {
        y = (f * a - c * e) / (d * a - c * b);
        x = (e - b * y) / a;
    }
    printf("%g %g\n", x, y);

    return 0;
}