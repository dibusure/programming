//  Выведите значение наименьшего из всех положительных элементов в массиве. Известно, что в массиве есть хотя бы один положительный элемент.
#include <iostream>
#include <vector>

int main()
{
    int size = 0, min_natural = 0;
    scanf("%d", &size);
    std::vector<int> array(size);
    for (int i = 0; i < size; ++i)
    {
        scanf("%d", &array[i]);
    }

    for (int i = 0; i < size; ++i)
    {
        if (min_natural == 0 && array[i] > 0)
        { // capture the first natural
            min_natural = array[i];
        }

        if (array[i] < min_natural && array[i] > 0)
        {
            min_natural = array[i];
        }
    }

    printf("%d\n", min_natural);
}