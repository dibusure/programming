#include <stdio.h>

int main() {
    int a;
    scanf("%d", &a);
    printf("The next number for the number %d is %d.\nThe previous number for the number %d is %d.\n", a, a+1, a, a-1);
}