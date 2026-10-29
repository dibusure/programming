// Переставьте соседние элементы массива (A[0] c A[1], A[2] c A[3] и т.д.). Если элементов нечетное число, то последний элемент остается на своем месте.
#include <vector>
#include <iostream>

void swap(int *a, int *b)
{
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}

int main()
{
    int size = 0;
    scanf("%d", &size);
    std::vector<int> A(size);

    for (int i = 0; i < size; ++i)
    {
        scanf("%d", &A[i]);
    }

    for (int i = 0; i < size; ++i)
    {
        if (i % 2 == 0 && i + 1 < size)
        {
            swap(&A[i], &A[i + 1]);
        }

        printf("%d ", A[i]);
    }

    printf("\n");
}