/* даны n чисел в формате:
    n
    числа
    надо найти сколько повторок в этом массиве
*/
//
//
//
// !TODO: использовать unordered_set
//
//
//

const int INT_MIN = -2147483648;

#include <iostream>
int main()
{
    int n = 0, counter = 0;
    scanf("%d", &n);
    int arr[n];
    int repeats[n];

    // fill the arrrays
    for (unsigned i = 0; i < n; ++i)
    {
        scanf("%d", &arr[i]);
    }

    for (unsigned i = 0; i < n; ++i)
    {
        repeats[i] = INT_MIN;
    }

    // detect repeats
    for (unsigned i = 0; i < n; ++i)
    {
        for (unsigned j = 0; j < n; ++j)
        {
            if (arr[i] == arr[j] && i != j)
            {
                repeats[i] = arr[i];
            }
        }
    }

    // count repeats
    for (unsigned i = 0; i < n; ++i)
    {
        if (repeats[i] != INT_MIN)
        {
            ++counter;
        }
    }

    // print repeats
    printf("%d\n", counter);
    return 0;
}