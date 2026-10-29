// дана строка сэ, надо переставить буквы так, чтобы получился палиндром. Если не получится, то -1
#include <string.h>
#include <iostream>
#include <set>

int main()
{
    std::string s;
    std::set<char> letters;
    char middle_letter = ' ';

    std::getline(std::cin, s);
    if (s.size() == 1)
    {
        std::cout << s << std::endl;
        return 0;
    }

    // first, we must check wheter the string can be palindrom:
    int pairs = 0;
    for (int i = 0; i < s.size(); ++i)
    {
        for (int j = 0; j < s.size(); ++j)
        {
            if (s[i] == s[j] && j != i)
            {
                ++pairs;
                letters.insert(s[i]);
                break;
            }
            else if (j == i)
            {
                middle_letter = s[i];
            }
        }
    }

    if (pairs == s.size() || pairs == s.size() - 1)
    {
        std::string palindrom;
        for (char i : letters)
        {
            palindrom += i;
        }

        if (s.size() % 2 == 1)
        {
            palindrom += middle_letter;
        }

        for (int i = letters.size() - 1; i >= 0; --i)
        {
            palindrom += palindrom[i];
        }

        std::cout << palindrom << std::endl;
    }
    else
    {
        std::cout << "-1" << std::endl;
    }
}