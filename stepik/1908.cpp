/*
надо проверить, входит ли точка (x;y) в эту область: https://ucarecdn.com/2b592fad-d9c1-4b91-8cac-9fc4896ad47b/
такая же тема, как и в 1907, 1906 и тп
*/
#include <math.h>
#include <iostream>

bool IsPointInArea(double x, double y)
{
    return (y >= -x && y >= 2 * x + 2 && pow(x + 1, 2) + pow(y - 1, 2) <= 4) || (y <= -x && y <= 2 * x + 2 && pow(x + 1, 2) + pow(y - 1, 2) >= 4);
}

int main()
{
    double x = 0, y = 0;
    std::cin >> x >> y;
    if (IsPointInArea(x, y))
    {
        std::cout << "YES" << std::endl;
    }
    else
    {
        std::cout << "NO" << std::endl;
    }
}