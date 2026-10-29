#include <stdio.h>
#include <stdlib.h>

void fill_matrix(unsigned ***matrixptr, unsigned height, unsigned width);

int
main()
{
    unsigned height = 0;
    unsigned width = 0;
    int string_length = 4;

    scanf("%u %u", &height, &width);

    // init matrix start
    unsigned long long **matrix = (unsigned long long **) calloc(height, sizeof(unsigned long long *));
    if (matrix == NULL) {
        return -1;
    }

    for (unsigned i = 0; i < height; ++i) {
        matrix[i] = (unsigned long long *) calloc(width, sizeof(unsigned long long));
        if (matrix[i] == NULL) {
            for (unsigned j = 0; j < i; ++j) {
                free(matrix[j]);
            }
            free(matrix);
            return -1;
        }
    }
    // init matrix end

    fill_matrix(&matrix, height, width);

    for (unsigned i = 0; i < height; ++i) {
        for (unsigned j = 0; j < width; ++j) {
            printf("%*llu ", string_length, matrix[i][j]); // тут должно быть %4llu
        }
        printf("\n");
    }

    // free matrix start
    for (unsigned i = 0; i < height; ++i) {
        free(matrix[i]);
    }

    free(matrix);
    //  free matrix end
}

void
fill_matrix(unsigned ***matrixptr, unsigned height, unsigned width)
{
    unsigned counter = 1;
    unsigned **matrix = *matrixptr;

    for (unsigned sum = 0; sum < width + height - 1; ++sum) {
        for (unsigned i = 0; i < height; ++i) {
            for (unsigned j = 0; j < width; ++j) {
                if (i + j == sum) {
                    matrix[i][j] = counter;
                    counter++;
                }
            }
        }
    }
}
