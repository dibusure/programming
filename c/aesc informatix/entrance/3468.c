#include <stdio.h>

int main() {
    int n = 0;
    scanf("%d", &n);
    printf("%d %d\n", (n/60)%24, (n%60)%1440);
}
