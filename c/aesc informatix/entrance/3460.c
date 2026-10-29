#include <stdio.h>

int main()
{
    int v, t = 0;
    scanf("%d %d", &v, &t);
    printf("%d\n", (v * t) % 109);
}
