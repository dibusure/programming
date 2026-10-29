#include <stdio.h>
#include <stdlib.h>

void fill_matrix(unsigned n, unsigned **matrix);

int
main()
{
    unsigned n = 1;
    scanf("%u", &n);

    // init matrix start
    unsigned **matrix = (unsigned **) malloc(n * sizeof(unsigned *));
    if (matrix == NULL) {
        return -1;
    }

    for (unsigned i = 0; i < n; ++i) {
        matrix[i] = (unsigned *) malloc(n * sizeof(unsigned));
        if (matrix[i] == NULL) {
            for (unsigned j = 0; j < i; ++j) {
                free(matrix[j]);
            }
            free(matrix);
            return -1;
        }
    }
    // init matrix end

    fill_matrix(n, matrix);

    for (unsigned i = 0; i < n; ++i) {
        for (unsigned j = 0; j < n; ++j) {
            printf("%u ", matrix[i][j]);
        }
        printf("\n");
    }
    // free matrix start
    for (unsigned i = 0; i < n; ++i) {
        free(matrix[i]);
    }

    free(matrix);
    //  free matrix end
}

void
fill_matrix(unsigned n, unsigned **matrix)
{
    for (unsigned i = 0; i < n; ++i) {
        for (unsigned j = 0; j < n; ++j) {
            if (j >= i) {
                matrix[i][j] = j - i;
            } else {
                matrix[i][j] = i - j;
            }
        }
    }
}
