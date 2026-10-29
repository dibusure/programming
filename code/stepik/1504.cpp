// Дано целое число, не меньшее 2. Выведите его наименьший натуральный делитель, отличный от 1.
#include <iostream>

int main()
{
    int a = 0;
    scanf("%d", &a);
    int i = 2;
    while (a % i != 0)
    {
        ++i;
    }
    printf("%d\n", i);
}