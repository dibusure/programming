// Во входной строке записана последовательность чисел через пробел. Для каждого числа выведите слово YES (в отдельной строке), если это число ранее встречалось в последовательности или NO, если не встречалось.
#include <iostream>
#include <set>

int main()
{
    int n = 0, tmp = 0, tmps = 0;
    std::cin >> n;
    std::set<int> nums;

    for (int i = 0; i < n; ++i)
    {
        std::cin >> tmp;
        tmps = nums.size();
        nums.insert(tmp);
        if (tmps == nums.size())
        {
            std::cout << "YES" << std::endl;
        }
        else
        {
            std::cout << "NO" << std::endl;
        }
    }
}