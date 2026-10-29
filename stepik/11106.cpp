// Даны два списка чисел, которые могут содержать до 100000 чисел каждый.  Выведите все числа, которые входят как в первый, так и во второй список в порядке возрастания.
#include <set>
#include <iostream>

int main()
{
    int n = 0, m = 0, tmp = 0;
    std::set<int> num1;
    std::set<int> intersec;
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
            intersec.insert(tmp);
        }
    }

    for (int i : intersec)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}