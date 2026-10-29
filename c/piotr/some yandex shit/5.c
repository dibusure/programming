#include <stdio.h>
#include <limits.h>

int FindMax(int *a, int len) {
    int max = INT_MIN;
    printf("%d\n", INT_MIN);

    for (int i = 0; i < len; ++i) {
        if (a[i] > max)
            max = a[i];
    }

    return max;
}

int main() {
    int a[] = {-1, -2, -3};
    int len = 3;

    printf("%d\n", FindMax(a, len));
}