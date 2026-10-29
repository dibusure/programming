// вывести время так, как оно вывелось бы на часах. Дано время в секундах

#include <iostream>
using namespace std;

int main()
{
    int time = 0;
    cin >> time;
    int hours = 0, minutes = 0, seconds = 0;
    hours = (time / 3600) % 24;
    minutes = ((time - time % 60) / 60) % 60;
    seconds = time % 60;
    printf("%d:%02d:%02d\n", hours, minutes, seconds);

    return 0;
}