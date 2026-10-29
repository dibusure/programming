// Дан список, упорядоченный по неубыванию элементов в нем. Определите, сколько в нем различных элементов.
#include <vector>
#include <iostream>

int main()
{
    int size = 0, various_elements = 0;
    scanf("%d", &size);
    std::vector<int> array(size);

    for (int i = 0; i < size; ++i)
    {
        scanf("%d", &array[i]);
    }

    if (size == 1)
    {
        various_elements = 1;
    }
    else
    {
        for (int i = 0; i < size; ++i)
        {
            if ((i == 0 && array[i] != array[i + 1]) || (array[i] != array[i - 1]))
            {
                ++various_elements;
            }
        }
    }

    printf("%d\n", various_elements);
}