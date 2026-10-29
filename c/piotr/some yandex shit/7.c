#include <stdio.h>
#include <stdlib.h>

int** Init2d(int row, int columns) {
    int *array= calloc(columns, sizeof(int));
    for (int i = 0; i < row; ++i) 
        array[i] = (int) calloc(row, sizeof(int));

    for (int i = 0; i < columns; ++i)
        for (int j = 0; j < row; ++j)
            *(array+i+j) = i+j;

    return array;
}

int main() {
    int row = 3;
    int columns = 3;

    int *array = Init2d(row, columns);
    printf("%d\n", array[0][1]);
    return 0;
}