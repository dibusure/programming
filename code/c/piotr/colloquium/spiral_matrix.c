#include <stdio.h>
#include <stdlib.h>

void fillmatrix(unsigned ***matrix, unsigned height, unsigned width);

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
fillmatrix(unsigned ***matrix_ptr, unsigned height, unsigned width)
{
    unsigned counter = 1;
    unsigned **matrix = *matrix_ptr;
    unsigned direction = 0; // 0 -- направо; 1 -- вниз; 2 -- налево; 3 -- вверх
    unsigned i = 0, j = 0;
    unsigned flag = 0;

    while (counter != width * height) {

        switch (direction) {
        default:
            break;
        case 0:
            if (flag) {
                ++i;
                ++j;
                flag = 0;
            }
            if (j != width - 1 && matrix[i][j] == 0) {
                matrix[i][j] = counter;
                ++counter;
                ++j;
            } else {
                ++direction;
                --i;
            }
            break;
        case 1:
            if (i != height - 1 && matrix[i][j] == 0) {
                matrix[i][j] = counter;
                ++counter;
                --i;
            } else {
                ++direction;
            }

            break;
        case 2:
            if (j > 0 && matrix[i][j] == 0) {
                matrix[i][j] = counter;
                ++counter;
                --j;
            } else {
                ++direction;
            }

            break;
        case 3:
            if (i > 0 && matrix[i][j] == 0) {
                matrix[i][j] = counter;
                ++counter;
                --i;
            } else {
                direction = 0;
                printf("KRUG\n");
                flag = 1;
            }
            break;
        }
    }

    for (unsigned i = 0; i < height; ++i) {
        for (unsigned j = 0; j < width; ++j) {
            if (matrix[i][j] % 10 == matrix[i][j]) {
                printf("   %u", matrix[i][j]);
            } else if (matrix[i][j] % 100 == matrix[i][j]) {
                printf("  %u", matrix[i][j]);
            } else if (matrix[i][j] % 1000 == matrix[i][j]) {
                printf(" %u", matrix[i][j]);
            } else {
                printf("%u", matrix[i][j]);
            }
        }
        printf("\n");
    }
    printf("---- при direction = %d, i = %d, j = %d\n", direction, i, j);
}
