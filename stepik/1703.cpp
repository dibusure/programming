// Выведите все элементы массива с четными индексами (то есть A[0], A[2], A[4], ...).
#include <iostream>

int main()
{
    int n = 0;
    scanf("%d", &n);
    int arr[n];

    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &arr[i]);
    }

    for (int i = 0; i < n; ++i)
    {
        if (i % 2 == 0)
        {
            printf("%d ", arr[i]);
        }
    }

    printf("\n");
}