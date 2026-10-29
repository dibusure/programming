#include <stdio.h>

int main() {
    int a, b, n = 0;
    scanf("%d %d %d", &a, &b, &n);
    int price = a*100 + b;// kopeyki
    int cost = price*n;
    printf("%d %d\n", cost/100, cost%100);
}
