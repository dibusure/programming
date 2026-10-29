#include <stdio.h>
#include <stdlib.h>

int
main()
{
    int x = 0;
    char buf[64];
    itoa(&x, buf, 2);
    printf("%d\n", buf);
}
