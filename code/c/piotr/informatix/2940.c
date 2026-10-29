#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main() {
    int v,t;
    scanf("%d %d", &v, &t);
    int r = abs((v*t)%109);
    printf("%d\n", (109*r+(v*t))%109);
}