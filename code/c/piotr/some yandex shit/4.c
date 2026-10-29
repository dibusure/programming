/*4. Copy Array Using Pointers
Write a function that copies the contents of one array to another using pointers.*/

#include <stdio.h>
#include <stdlib.h>

int* CopyArray (int *startarr, int len)
{

    int *endarr = malloc(len*sizeof(int));
    for (int i = 0; i < len; ++i) {
        *(endarr+i) = *(startarr+i);
        printf("%d - %d\n", *(startarr+i), *(endarr+i));
    }

    return endarr;
}

int main() {

    int len = 3;

    int startarr[] = { 1, 2, 3 };
    int *endarr   = CopyArray(startarr, len);

    for (int i = 0; i < len; ++i)
        printf("%d", *(endarr+i));

    printf("\n");
}