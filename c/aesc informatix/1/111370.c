#include <stdio.h>
#include <stdlib.h>

int
main()
{
    unsigned m, n;
    m = n = 0;
    scanf("%u %u", &n, &m);

    // init matrix start
    unsigned **matrix = (unsigned **) malloc(n * sizeof(unsigned *));
    if (matrix == NULL) {
        return -1;
    }

    for (unsigned i = 0; i < n; ++i) {
        matrix[i] = (unsigned *) malloc(m * sizeof(unsigned));
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
        for (unsigned j = 0; j < m; ++j) {
            scanf("%u", &matrix[i][j]);
        }
    }

    for (unsigned i = 0; i < m; ++i) {
        for (unsigned j = 0; j < n; ++j) {
            printf("%u ", matrix[j][i]);
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
