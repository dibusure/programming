// даны два момента времени (формат: часы, минуты, секунды). Нужно вывести, сколько секунд прошло между ними

#include <iostream>
using namespace std;

int main()
{
    int h1 = 0, m1 = 0, s1 = 0;
    int h2 = 0, m2 = 0, s2 = 0;
    cin >> h1 >> m1 >> s1;
    cin >> h2 >> m2 >> s2;

    int time1 = h1 * 3600 + m1 * 60 + s1;
    int time2 = h2 * 3600 + m2 * 60 + s2;

    printf("%d\n", time2 - time1);
}