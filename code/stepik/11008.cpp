// Найдите в данной строке самое длинное слово и выведите его.
#include <string.h>
#include <iostream>

int main()
{
    std::string str;
    std::getline(std::cin, str);
    str += ' ';

    int tmp_len = 0, max_len = 0, max_len_index = 0;

    for (int i = 0; i < str.length(); ++i)
    {
        if (str[i] == ' ')
        {
            if (tmp_len > max_len)
            {
                max_len = tmp_len;
                max_len_index = i - tmp_len;
            }

            tmp_len = 0;
        }
        else
        {
            ++tmp_len;
        }
    }

    for (int i = max_len_index; i < max_len_index + max_len; ++i)
    {
        std::cout << str[i];
    }

    std::cout << std::endl;
}