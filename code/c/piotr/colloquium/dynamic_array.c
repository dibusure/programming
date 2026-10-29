#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

void pop(int *array, unsigned *len_ptr);
void add(int number, int **array_ptr, unsigned *len_ptr, unsigned *capacity_ptr);

int
main()
{
    size_t buf_size = 26;
    const unsigned MIN_SIZE = 4;

    char *buffer = calloc(buf_size, sizeof(char));
    ssize_t characters;
    unsigned len = 0;
    unsigned capacity = MIN_SIZE;

    int *array = (int *) calloc(capacity, sizeof(int));
    if (array == NULL) {
        return 1;
    }

    while (1) {
        characters = getline(&buffer, &buf_size, stdin);
        if ((int) characters == -1) {
            break;
        }
        size_t last = strcspn(buffer, "\n");
        buffer[last] = '\0';

        if (strstr(buffer, "pop") != NULL) {
            if (len != 0) {
                pop(array, &len);
            }
        } else if (strstr(buffer, "add ") != NULL) {
            int index = 0;
            sscanf(buffer + 4, "%d", &index);
            add(index, &array, &len, &capacity);
        } else if (strstr(buffer, "read ") != NULL) {
            int index = 0;
            sscanf(buffer + 5, "%d", &index);
            printf("%d\n", array[index]);
        } else if (strstr(buffer, "len") != NULL) {
            printf("%d\n", len);
        } else if (strstr(buffer, "mem") != NULL) {
            printf("%d\n", capacity);
        }
    }

    free(buffer);
    free(array);
    return 0;
}

void
pop(int *array, unsigned *len_ptr)
{
    *len_ptr = *len_ptr - 1;
    printf("%d\n", array[*len_ptr - 1]);
}

void
add(int number, int **array_ptr, unsigned *len_ptr, unsigned *capacity_ptr)
{
    int len = *len_ptr;
    int capacity = *capacity_ptr;
    int *array = *array_ptr;

    *len_ptr = len + 1;

    array[len] = number;
    if (capacity - len == 1) {
        *capacity_ptr *= 2;
        *array_ptr = (int *) realloc(array, 2 * capacity * sizeof(int));
        if (*array_ptr == NULL) {
            exit(1);
        }
    }
}
