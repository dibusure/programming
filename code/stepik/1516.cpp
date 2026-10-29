/*
Определите наименьшее расстояние между двумя локальными максимумами последовательности натуральных чисел, завершающейся числом 0. Если в последовательности нет двух локальных максимумов, выведите число 0.

Начальное и конечное значение при этом локальными максимумами не считаются.

Расстоянием считается количество пробелов между элементами. В качестве примера смотрите первый тест.
*/
#include <iostream>
#include <limits.h>

int main()
{
    int first_maximum_index = 0, second_maximum_index = 0, space = 0, min_space = 0;
    int index = 1, i = 0, a = 0, b = 0, c = 0;
    scanf("%d", &i);
    c = i;

    while (i != 0)
    {
        a = b;
        b = i;
        scanf("%d", &i);
        ++index;
        c = i;

        if (b > a && b > c && a != 0 && c != 0)
        {
            if (first_maximum_index != 0)
            {
                second_maximum_index = index - 1; // because 'index' is c's index but maximum is b
                space = second_maximum_index - first_maximum_index;

                if (min_space == 0)
                {
                    min_space = space;
                }
                else if (min_space > space)
                {
                    min_space = space;
                }
            }

            first_maximum_index = index - 1;
        }
    }

    printf("%d\n", min_space);
    return 0;
}