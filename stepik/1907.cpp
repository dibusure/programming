/*
Даны пять действительных чисел: x, y, xc, yc, r. Проверьте, принадлежит ли точка (x, y) кругу с центром (xc, yc) и радиусом r. Если точка принадлежит кругу, выведите слово YES, иначе выведите слово NO.
Решение должно содержать функцию IsPointInCircle(x, y, xc, yc, r), возвращающую True, если точка принадлежит кругу и False, если не принадлежит. Основная программа должна считать координаты точки, вызвать функцию IsPointInCircle и в зависимости от возвращенного значения вывести на экран необходимое сообщение.
Функция IsPointInCircle не должна содержать инструкцию if.
*/
#include <iostream>
#include <math.h>

// (x-xc)^2 + (y-yc)^2 <= r^2

bool IsPointInCircle(double x, double y, double xc, double yc, double r)
{
    return pow(x - xc, 2) + pow(y - yc, 2) <= pow(r, 2);
}

int main()
{
    double x = 0, y = 0, xc = 0, yc = 0, r = 0;
    std::cin >> x >> y >> xc >> yc >> r;
    if (IsPointInCircle(x, y, xc, yc, r))
    {
        std::cout << "YES" << std::endl;
    }
    else
    {
        std::cout << "NO" << std::endl;
    }
}