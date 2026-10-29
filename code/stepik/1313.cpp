// Задача про МКАД. Дано: v, t. Найти на каком километре мкада будет машина. Магическое число -- 109

#include <iostream>
using namespace std;

int main()
{
    int mkad = 109;
    int v = 0, t = 0;
    cin >> v >> t;
    cout << (((v * t) % mkad) + 109) % 109 << endl;
}