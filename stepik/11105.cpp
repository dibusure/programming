// Даны два списка чисел, которые могут содержать до 100000 чисел каждый. Посчитайте, сколько чисел содержится одновременно как в первом списке, так и во втором.
#include <set>
#include <iostream>

int main()
{
    int n = 0, m = 0, tmp = 0, counter = 0;
    std::set<int> num1;
    std::cin >> n;

    for (int i = 0; i < n; ++i)
    {
        std::cin >> tmp;
        num1.insert(tmp);
    }

    std::cin >> m;
    for (int i = 0; i < m; ++i)
    {
        std::cin >> tmp;
        if (num1.count(tmp) != 0)
        {
            ++counter;
        }
    }

    std::cout << counter << std::endl;
}