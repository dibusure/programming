// Дан список целых чисел, который может содержать до 100000 чисел. Определите, сколько в нем встречается различных чисел.
#include <unordered_set>
#include <iostream>

int main()
{
    int n = 0, tmp = 0;
    std::cin >> n;
    std::unordered_set<int> nums(n);

    for (int i = 0; i < n; ++i)
    {
        std::cin >> tmp;
        nums.insert(tmp);
    }

    std::cout << nums.size() << std::endl;
}