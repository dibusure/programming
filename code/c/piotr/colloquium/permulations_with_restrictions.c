#include <stdio.h>
int
fac(int number)
{
    if (number == 0) {
        return 1;
    }
    return fac(number - 1) * number;
}
void
swap(char *x, char *y)
{
    char t;
    t = *x;
    *x = *y;
    *y = t;
}

void
permute(char *word, int s, int e) // s stands for starting index and e for ending index
{
    int i = 0;
    int counter = 0;
    if (s == e) {
        for (int j = 0; j < e; ++j) {
            if (*(word + j) == "Т" && *(word + j + 1) == "Ш") {
                ++counter;
                printf("%s\n", word);
            }
        }
    } else {
        for (i = 0; i <= s; ++i) {
            swap((word + s), (word + i));
            permute(word, s + 1, e);
            swap((word + s), (word + i));
        }
    }

    printf("%d\n", counter);
    printf("%s\n", word);
}

int
main()
{
    const unsigned length = 9;
    char word[] = "ФЗФТШМФТИ";
    permute(word, 0, length - 1);
}
