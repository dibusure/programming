// Дан массив. Выведите те его элементы, которые встречаются в массиве только один раз. Элементы нужно выводить в том порядке, в котором они встречаются в списке
#include <iostream>
#include <vector>

int main()
{
    int size = 0;
    scanf("%d", &size);
    std::vector<int> A(size);
    for (int i = 0; i < size; ++i)
    {
        scanf("%d", &A[i]);
    }

    int doubles = 0;

    for (int i = 0; i < size; ++i)
    {
        doubles = 0;

        for (int j = 0; j < size; ++j)
        {
            if (A[i] == A[j] && i != j)
            {
                ++doubles;
            }
        }

        if (doubles == 0)
        {
            printf("%d ", A[i]);
        }
    }

    printf("\n");
}