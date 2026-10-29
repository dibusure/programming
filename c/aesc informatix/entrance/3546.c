#include <stdio.h>

int main()
{
    int n = 0;
    scanf("%d", &n);
    if (n <= 27)
    {
        for (int x = 1; x <= 9; ++x)
        {
            for (int y = 0; y <= 9; ++y)
            {
                for (int z = 0; z <= 9; ++z)
                {
                    if (x + y + z == n)
                        printf("%d\n", x * 100 + y * 10 + z);
                }
            }
        }
    }
}