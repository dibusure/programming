// По введенному символу определите, является ли он цифрой.
#include <iostream>

int main()
{
    char c;
    std::cin >> c;
    std::cout << ((c >= '0' && c <= '9') ? "yes" : "no") << std::endl;
    return 0;
}