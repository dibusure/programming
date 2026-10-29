#include <stdio.h>
#include <stdlib.h>

int main() {
    int *array = malloc(5*sizeof(int));

    free(array);
    return 0;
}
