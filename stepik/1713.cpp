// Дан массив чисел. Посчитайте, сколько в нем пар элементов, равных друг другу. Считается, что любые два элемента, равные друг другу образуют одну пару, которую необходимо посчитать.
#include <vector>
#include <iostream>

int main()
{
    int size = 0, pairs = 0;
    scanf("%d", &size);
    std::vector<int> array(size);

    for (int i = 0; i < size; ++i)
    {
        scanf("%d", &array[i]);
    }

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            if (array[i] == array[j] && i != j)
            {
                ++pairs;
            }
        }
    }

    pairs = pairs / 2; // очевидно, почему каждая пара посчитана дважды

    printf("%d\n", pairs);
}