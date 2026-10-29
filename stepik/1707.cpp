// Дан массив целых чисел. Если в нем есть два соседних элемента одного знака, выведите эти числа. Если соседних элементов одного знака нет - не выводите ничего. Если таких пар соседей несколько - выведите первую пару
#include <vector>
#include <iostream>

int main()
{
    int size = 0;
    scanf("%d", &size);
    std::vector<int> array(size);

    for (int i = 0; i < size; ++i)
    {
        scanf("%d", &array[i]);
    }

    for (int i = 1; i < size; ++i)
    {
        if ((array[i] > 0 && array[i - 1] > 0) || (array[i] < 0 && array[i - 1] < 0))
        {
            if (array[i - 1] < array[i])
            {
                printf("%d %d\n", array[i - 1], array[i]);
            }
            else
            {
                printf("%d %d\n", array[i], array[i - 1]);
            }
            return 0;
        }
    }
}