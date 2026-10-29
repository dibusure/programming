#include <stdio.h>

unsigned long long power(unsigned base, unsigned pow)
{
    unsigned long long result = 1;

    while (pow > 0) {
        if (pow % 2 == 1) {
            result *= base;
        }
        base *= base;

        pow /= 2;
    }

    return result;
}

unsigned long long getSum(unsigned long long number)
{
    unsigned long long sum = 0;

    while (number != 0) {
        sum += number % 10;
        number /= 10;
    }

    return sum;
}

unsigned long long bruteforce(unsigned number, unsigned long long tenHalf, unsigned long long tenFull)
{
    unsigned long long answer = 0;
    unsigned long long sums[8 * 9 + 1] = { 0 };

    for (unsigned i = 1; i < tenHalf; ++i) {
        ++sums[getSum(i)];
    }

    for (int i = 1; i < 8 * 9 + 1; ++i) { // тут наверное можно i <= number/2 + 1
        answer += sums[i] * sums[i];
    }

    return answer;
}

int main()
{
    unsigned number = 0;
    scanf("%u", &number);

    if (number == 1) {
        printf("9\n");
    }
    else if (number % 2 == 0) {
        unsigned long long tenHalf = power(10, number / 2);
        printf("%llu\n", bruteforce(number, tenHalf, tenHalf * tenHalf));
        return 0;
    }
    else {
        unsigned long long tenHalf = power(10, (number - 1) / 2);
        printf("%llu\n", 10 * bruteforce(number, tenHalf, tenHalf * tenHalf) + 9);
        return 0;
    }
}