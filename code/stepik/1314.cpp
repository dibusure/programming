// дано число (<= 4 цифры), определить, симметричное ли оно (то есть равны ли первая и последняя цифры и серединные). В плохом случае -- вывести любое целое

#include <iostream>

int main()
{
    int number = 0, first = 0, second = 0, third = 0, fourth = 0;
    scanf("%d", &number);

    first = number % 10; // the last one i mean
    second = (number % 100 - (number % 10)) / 10;
    third = (number % 1000 - first - second) / 100;
    fourth = number / 1000;

    printf("%d %d %d %d\n", fourth, third, second, first);
    printf("%d\n", 1 + (fourth - first) * (fourth - first) + (third - second) * (third - second));
    return 0;
}