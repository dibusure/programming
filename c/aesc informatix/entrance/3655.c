#include <stdio.h>

int main()
{
    int n = -1;

    int max = 0;
    int pmax = 0;

    while (n != 0)
    {
        scanf("%d", &n);
        if (n != 0)
        {
            if (n > max)
            {
                pmax = max;
                max = n;
            }
            else if (n < max && n > pmax)
            {
                pmax = n;
            }
        }
    }

    printf("%d\n", pmax);
}