#include <stdio.h>

int main() {
    int man;
    scanf("%d", &man);
    printf("%d\n", (man%100 - man%10)/10);
}