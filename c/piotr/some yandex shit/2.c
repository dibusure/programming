/*2. Sum Array Elements Using Pointers
Write a function that takes an array and its size, and returns the sum of its elements using pointers.*/


#include <stdio.h>

int sum(int *a, int n) {
    int sum = 0;

    for (int i = 0; i < n; ++i)
        sum += *(a+i);

    return sum;
}

int main() {
    int a[] = { 3, 3, 3, 3, 3, 3, 3, 3, 3 };

    printf("%d\n", sum(a, 9));
}