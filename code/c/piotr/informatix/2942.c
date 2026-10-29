#include <stdio.h>

int main() {
    int num;
    scanf("%d", &num);
    printf("%d\n", (num-num%10)/10);
}