/*3. Reverse a String Using Pointers
Write a function that takes a string (character array) and reverses it in place using pointers.*/


#include <stdio.h>

void Swap(char *p1, char *p2) {
    char pp1 = *p1;
    *p1 = *p2;
    *p2 = pp1;
}

int StrLen (char *a)
{
    int lena = 0;
    while (a[lena] != '\0')
        lena++;

    return lena;
}

void Reverse(char *a)
{
    int len = StrLen(a); 

    for (int i = 0; i < len/2; ++i) {
        Swap(a+i, a+len-1-i);
    }    
}

int main()
{
    char a[] = "abcd";

    Reverse(a);
    printf("%s\n", a);
}