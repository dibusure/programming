// Найдите количество положительных элементов в данном массиве.
#include <vector>
#include <iostream>

int main()
{
    int n = 0, counter = 0, temp = 0;
    scanf("%d", &n);
    // std::vector<int> arr(n);

    for (int i = 0; i < n; ++i)
    {
        // scanf("%d", &arr[i]);
        scanf("%d", &temp);
        if (temp > 0)
        {
            ++counter;
        }
    }

    printf("%d\n", counter);
}