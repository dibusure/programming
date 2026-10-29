//  Известно, что на доске 8×8 можно расставить 8 ферзей так, чтобы они не били друг друга. Вам дана расстановка 8 ферзей на доске, определите, есть ли среди них пара бьющих друг друга.
// Формат ввода: 8 пар чисел [0-9]
#include <vector>
#include <iostream>

int main()
{
    std::vector<int> X(8);
    std::vector<int> Y(8);
    int counter = 0;

    while (counter < 16)
    {
        if (counter % 2 == 0)
        {
            scanf("%d", &X[counter / 2]);
            ++counter;
        }
        else // counter % 2 == 1
        {
            scanf("%d", &Y[counter / 2]);
            ++counter;
        }
    }

    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            if (i != j)
            {
                if (X[i] == X[j] || Y[i] == Y[j]) // если какие-то на одной вертикали или горизонтали
                {
                    printf("YES\n");
                    return 0;
                }
                else if (X[i] + Y[i] == X[j] + Y[j] || X[i] + Y[j] == Y[i] + X[j]) // если какие-то на одной диагонали
                {
                    printf("YES\n");
                    return 0;
                }
            }
        }
    }
    printf("NO\n");
}