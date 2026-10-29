#include <stdio.h>

int main() {
    int min, hours;
    scanf("%d", &min);
    hours = min / 60;
    min = min % 60;
    printf("%d %d\n", hours % 24, min);
}