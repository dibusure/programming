// По данной строке определите, является ли она палиндромом (то есть, читается одинаково как слева-направо, так и справа-налево).
#include <string.h>
#include <iostream>

int main()
{
    std::string str;
    std::getline(std::cin, str);
    int counter = 0;
    for (int i = 0; i < str.length() / 2; ++i)
    {
        if (str[i] == str[str.length() - 1 - i])
        {
            ++counter;
        }
    }

    std::cout << ((counter == str.length() / 2) ? "yes" : "no") << std::endl;
}