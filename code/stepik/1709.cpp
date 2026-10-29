// Выведите значение наименьшего нечетного элемента списка, а если в списке нет нечетных элементов - выведите число 0.
#include <iostream>
#include <vector>
#include <math.h>

int main()
{
    int size = 0, min_odd = 0;
    scanf("%d", &size);
    std::vector<int> array(size);

    for (int i = 0; i < size; ++i)
    {
        scanf("%d", &array[i]);
    }

    for (int i = 0; i < size; ++i)
    {
        if (min_odd == 0 && array[i] % 2 == 1)
        {
            min_odd = array[i];
        }

        if (abs(array[i]) % 2 == 1 && array[i] < min_odd)
        {
            min_odd = array[i];
        }
    }

    printf("%d\n", min_odd);
}