/*1. Swap Two Integers Using Pointers
Write a function that takes two integer pointers as arguments and swaps the values they point to.*/

#include <stdio.h>

void swap(int *p1, int *p2) {
    int pp1 = *p1;
    *p1 = *p2;
    *p2 = pp1;
}

int main() {
    int a = 2, b = 3;
    int *pa = &a, *pb = &b;
    swap(pa, pb);

    printf("%d %d\n", *pa, *pb);

    return 0;
}