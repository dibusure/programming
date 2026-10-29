#include <stdio.h>

// TODO: binsearch

int main()
{
    int n = 0;
    scanf("%d", &n);
    int heights[n];
    int petr = 0;

    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &heights[i]);
    }

    scanf("%d", &petr);

    for (int i = 0; i < n; ++i)
    {
        if (heights[i] < petr)
        {
            printf("%d\n", i + 1);
            return 0;
        }
        else if (i == n - 1)
        {
            printf("%d\n", n + 1);
        }
    }
}