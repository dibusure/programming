// По данному целому числу N распечатайте все квадраты натуральных чисел, не превосходящие N, в порядке возрастания.
#include <iostream>

int main()
{
    int n = 0;
    scanf("%d", &n);

    for (int i = 1; i * i <= n; ++i)
    {
        printf("%d ", i * i);
    }

    printf("\n");

    return 0;
}