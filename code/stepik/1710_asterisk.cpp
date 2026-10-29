// Дан список, упорядоченный по неубыванию элементов в нем. Определите, сколько в нем различных элементов. -- оригинальное задание
// Решу похожее задание: дан список; определить, сколько в нём различных элементов

#include <iostream>
#include <set>

int main()
{
    int size = 0, various_elements = 0, tmp = 0;
    scanf("%d", &size);
    std::set<int> list;

    for (int i = 0; i < size; ++i)
    {
        scanf("%d", &tmp);
        list.insert(tmp);
    }

    printf("%d\n", list.size());
}