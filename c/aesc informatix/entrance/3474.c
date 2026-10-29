#include <stdio.h>

int main() {
    int h1, m1, s1, h2, m2, s2 = 0;
    scanf("%d %d %d %d %d %d", &h1, &m1, &s1, &h2, &m2, &s2);
    int firstsec = 3600*h1 + 60*m1 + s1;
    int secondsec = 3600*h2 + 60*m2 + s2;
    printf("%d\n", secondsec-firstsec);
}
