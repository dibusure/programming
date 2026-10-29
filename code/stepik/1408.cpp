// 4 числа: (a, b), (c,d). Нужно определить можно ли из (a, b) ладьёй одним ходом попасть в (c, d)
#include <iostream>

int main()
{
    int a = 0, b = 0, c = 0, d = 0;
    scanf("%d %d %d %d", &a, &b, &c, &d);
    if (a == c || b == d)
    {
        printf("YES\n");
    }
    else
    {
        printf("NO\n");
    }

    return 0;
}