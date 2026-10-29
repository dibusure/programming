// Дано натуральное число N. Выведите слово YES, если число N является точной степенью двойки, или слово NO в противном случае.
#include <iostream>

int main()
{
    int n = 0;
    scanf("%d", &n);

    while (n % 2 == 0)
    {
        n /= 2;
    }

    if (n == 1)
    {
        printf("YES\n");
    }
    else
    {
        printf("NO\n");
    }

    return 0;
}