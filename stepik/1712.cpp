// Циклически сдвиньте элементы списка вправо (A[0] переходит на место A[1], A[1] на место A[2], ..., последний элемент переходит на место A[0]).
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

    for (int i = 1; i < size; ++i)
    {
        swap(&A[0], &A[i]);
    }

    for (int i = 0; i < size; ++i)
    {
        printf("%d ", A[i]);
    }

    printf("\n");
}