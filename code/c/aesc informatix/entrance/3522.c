#include <stdio.h>

int main()
{
    int a, b, c, d, e = 0;
    scanf("%d %d %d %d %d", &a, &b, &c, &d, &e);

    if ((a <= d && b <= e) || (a <= d && c <= e) || (a <= e && b <= d) || (a <= e && c <= d) || (b <= d && c <= e) || (b <= e && c <= d))
        printf("YES\n");
    else
        printf("NO\n");
}