#include <stdio.h>
#include <stdlib.h>

void permulate(unsigned **numbers_ptr, unsigned len, unsigned len_abs);
void swap(unsigned **numbers_ptr, unsigned len, unsigned first_index, unsigned second_index);
void print_array(unsigned *numbers, unsigned len);

int
main()
{
    unsigned n = 0;
    scanf("%u", &n);

    unsigned *numbers = (unsigned *) calloc(n, sizeof(unsigned *));

    for (unsigned i = 0; i < n; ++i) {
        numbers[i] = i + 1;
    }

    permulate(&numbers, n, n);

    free(numbers);
}

void
permulate(unsigned **numbers_ptr, unsigned len, unsigned len_abs)
{
    unsigned *numbers = *numbers_ptr;

    if (len < 2) {
        print_array(numbers, len_abs);
    } else {
        for (int i = len - 1; i >= 0; --i) {
            if (i == (int) len - 1) {
                permulate(numbers_ptr, len - 1, len_abs);
            } else {
                swap(numbers_ptr, len, i, len - 1);
                permulate(numbers_ptr, len - 1, len_abs);
                swap(numbers_ptr, len, i, len - 1);
            }
        }
    }
}

void
swap(unsigned **numbers_ptr, unsigned len, unsigned first_index, unsigned second_index)
{
    unsigned *numbers = *numbers_ptr;

    if (first_index < len && second_index < len) {
        unsigned tmp = numbers[second_index];
        numbers[second_index] = numbers[first_index];
        numbers[first_index] = tmp;
    }
}

void
print_array(unsigned *numbers, unsigned len)
{
    for (unsigned i = 0; i < len; ++i) {
        printf("%u ", numbers[i]);
    }
    printf("\n");
}
