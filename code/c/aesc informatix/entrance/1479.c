#include <stdio.h>
#include <math.h>

int main() {
    int k, n = 0;
    scanf("%d %d", &k, &n);
    int string = n%k + k*(int)(pow(0,n%k));
    int page = (n+k-1)/k;
    printf("%d %d\n", page, string);

    //tests: 50 1 -> 1 1
    //       20 25 -> 2 5
    //       15 43 -> 3 13
}