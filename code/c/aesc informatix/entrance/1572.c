#include <stdio.h>

int main()
{
    int sizeOfNumbers = 0;
    scanf("%d", &sizeOfNumbers);
    int numbers[sizeOfNumbers];

    for (int i = 0; i < sizeOfNumbers; ++i)
    {
        scanf("%d", &numbers[i]);
    }
    for (int i = 0; i < sizeOfNumbers; ++i)
    {
        for (int j = 0; j < sizeOfNumbers; ++j)
        {
            if (numbers[i] == numbers[j] && i != j)
            {

                if (numbers[i] > 0)
                {
                    numbers[i] += 4269;
                }
                else
                {
                    numbers[i] -= 4269;
                }

                if (numbers[j] > 0)
                {
                    numbers[j] += 4269;
                }
                else
                {
                    numbers[j] -= 4269;
                }
            }
            else if (numbers[i] - 4269 == numbers[j] || numbers[i] + 4269 == numbers[j] && i != j)
            /* выше скобочки были не нужны, тк логические операции идут слева направо:
             сначала ИЛИ, а потом уже И*/
            {
                numbers[j] += 4269;
            }
        }
    }

    for (int i = 0; i < sizeOfNumbers; ++i)
    {
        if (numbers[i] > 0)
        {
            if (numbers[i] <= 4000)
            {
                printf("%d ", numbers[i]);
            }
            else
            {
                if (numbers[i] >= -4000)
                {
                    printf("%d ", numbers[i]);
                }
            }
        }

        printf("\n");
    }
}