#include <stdio.h>

int main() {
    int num;
    scanf("%d", &num);
    int units, tens, hundreds = 0;
    units = num%10;
    tens = (num%100-num%10)/10;
    hundreds = (num-num%100)/100; // (123-23)
    printf("%d\n", units+tens+hundreds);
}