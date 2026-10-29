// Дан массив чисел. Выведите все элементы массива, которые больше предыдущего элемента.
#include <vector>
#include <iostream>

int main()
{
    int size = 0, count = 0;
    scanf("%d", &size);
    std::vector<int> array(size);

    for (int i = 0; i < size; ++i)
    {
        scanf("%d", &array[i]);
    }

    for (int i = 1; i < size; ++i)
    {
        if (array[i] > array[i - 1])
        {
            printf("%d ", array[i]);
        }
    }

    printf("\n");
}