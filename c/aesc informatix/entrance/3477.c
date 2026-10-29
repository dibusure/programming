#include <stdio.h>

int div_up(int x, int y)
{
    return (x + y - 1) / y;
}

int main() {
    int h, a, b = 0;
    scanf("%d %d %d", &h, &a, &b);
    // d*a - (d-1)*b = h
    // d = (h-b)/(a-b)
    //
    // 10 5 2 (test-case)
    printf("%d\n", div_up(h-b, a-b));
}
