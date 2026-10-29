#include <stdio.h>
#include <string.h>

int main() {
    char a[] = "Hello";
    int alien = strlen(a)+1;
    int i = alien;
    printf("%d\n", i);

    while (i >= 0) {
        a[alien-i] = a[i];
        printf("%c", a[alien-i]);
        i--;
    }

    for (int j = 0; j <= (int)strlen(a); ++j)
        printf("%c", a[j]);

    printf("\n");
    return 0;
}