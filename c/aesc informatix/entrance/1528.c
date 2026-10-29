#include <stdio.h>

int main() {
    int n = 0;
    double sum = 0;
    int amount = 0;
    int max = 0;
    int min = 100;
    scanf("%d", &n);

    while (n>0) {
       int b = 0;
       scanf("%d", &b);
       
       ++amount;
       sum += b;

       if (b > max) { max = b; }
       if (b < min) { min = b; }
       --n;
    }

    sum = sum - max - min;

    //printf("%d %d\n", min, max);
    //printf("%f %d\n", sum, amount);
    printf("%.2f\n", sum/(amount-2));
}