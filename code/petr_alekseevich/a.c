#include <stdio.h>

int main() {
    //SeNtEnCe
    long long word = 0x65736e65746e6573;

    int a = 0;
    long long* wordptr = &word;

    printf("%7s\n", (char*)wordptr);
}
