// даны две клетки (a,b) и (c,d). Определить, можно ли так пойти слоном
#include <iostream>

int main()
{
    int a = 0, b = 0, c = 0, d = 0;
    scanf("%d %d %d %d", &a, &b, &c, &d);
    if (a + b == c + d || a + d == b + c)
    {
        printf("YES\n");
    }
    else
    {
        printf("NO\n");
    }
}