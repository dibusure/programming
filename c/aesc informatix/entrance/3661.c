#include <stdio.h>

int main() {
    int a = 0;
    int b = 0; // a > b
    scanf("%d %d", &a, &b);
    while (b != a) {
        if (a%2 == 0 && a > 0 && a-b > a/2) {
            printf(":2\n");
            a = a/2;
        } else if (a > 0){
            printf("-1\n");
            a--;
        }
    }

    return 0;
}