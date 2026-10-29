#include <stdio.h>
#include <stdlib.h>

unsigned find_seats(unsigned **matrix, unsigned n, unsigned m, unsigned k);

int
main()
{
    unsigned n, m, k;
    n = m = k = 0;
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

    scanf("%u", &k);
    if (k > m) {
        printf("0\n");
        for (unsigned i = 0; i < n; ++i) {
            free(matrix[i]);
        }

        free(matrix);
        return 0;
    }

    printf("%u\n", find_seats(matrix, n, m, k));

    // free matrix start
    for (unsigned i = 0; i < n; ++i) {
        free(matrix[i]);
    }

    free(matrix);
    //  free matrix end

    return 0;
}

unsigned
find_seats(unsigned **matrix, unsigned n, unsigned m, unsigned k)
{
    --k;
    for (unsigned i = 0; i < n; ++i) {
        for (unsigned j = 0; j < m - k; ++j) {
            if (matrix[i][j] == 0) {
                if (k == 0) {
                    return i + 1;
                } else {
                    unsigned counter = 0;
                    for (unsigned l = 1; l <= k; ++l) {
                        if (matrix[i][j] == matrix[i][j + k]) {
                            ++counter;
                        }
                    }
                    if (counter == k) {
                        return i + 1;
                    }
                }
            }
        }
    }

    return 0;
}
