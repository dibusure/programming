#include <stdio.h>
#include <stdlib.h>

int* Allocate(int len)
{
    int *array = calloc(len, sizeof(int));
    if (array == NULL)
        return NULL;


    return array;
}

int main()
{
    int len = 3;
    int *array = Allocate(len);

    for (int i = 0; i < len; ++i)
        printf("%d", array[i]);

    printf("\n");

    free(array);
}