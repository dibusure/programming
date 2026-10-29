#include <stdio.h>

int main()
{
    char string[4]= "abca";
    int counter = 0;
    for (int x = 0; x < 4; x++) {
        if (string[x] == 'a')
            counter++;
    }

    printf("%d\n", counter);
    return 0;
}