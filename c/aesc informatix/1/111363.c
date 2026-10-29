#include <stdio.h>
#include <stdlib.h>

void
fill_matrix(unsigned n, char **matrix)
{
    for (unsigned i = 0; i < n; ++i) {
        for (unsigned j = 0; j < n; ++j) {
            if (i == (n - 1) / 2 || j == (n - 1) / 2 || j == i || j + i == n - 1) {
                matrix[i][j] = '*';
            }
        }
    }
}

int
main()
{
    unsigned n = 1; // n % 2 = 1
    scanf("%u", &n);

    if (n == 0) {
        return 1;
    }

    // init matrix start
    char **matrix = (char **) malloc(n * sizeof(char *));
    if (matrix == NULL) {
        return -1;
    }

    for (unsigned i = 0; i < n; ++i) {
        matrix[i] = (char *) malloc(n * sizeof(char));
        if (matrix[i] == NULL) {
            for (unsigned j = 0; j < i; ++j) {
                free(matrix[j]);
            }
            free(matrix);
            return -1;
        }
    }
    // init matrix end

    for (unsigned i = 0; i < n; ++i) {
        for (unsigned j = 0; j < n; ++j) {
            matrix[i][j] = '.';
        }
    }

    fill_matrix(n, matrix);

    for (unsigned i = 0; i < n; ++i) {
        for (unsigned j = 0; j < n; ++j) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }

    // free matrix start
    for (unsigned i = 0; i < n; ++i) {
        free(matrix[i]);
    }

    free(matrix);
    //  free matrix end
    return 0;
}