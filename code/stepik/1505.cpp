// По данному числу N распечатайте все целые степени двойки, не превосходящие N, в порядке возрастания.
#include <iostream>

int main()
{
    int n = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; i *= 2)
    {
        printf("%d ", i);
    }

    printf("\n");
    return 0;
}