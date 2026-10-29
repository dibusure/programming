/*В сети интернет каждому компьютеру присваивается четырехбайтовый код, который принято записывать в виде четырех чисел, каждое из которых может принимать значения от 0 до 255, разделенных точками. Вот примеры правильных IP-адресов:
127.0.0.0
192.168.0.1
255.0.255.255
Напишите программу, которая определяет, является ли заданная строка правильным IP-адресом.*/
#include <iostream>
#include <string>
#include <sstream>

int main()
{
    std::string str;
    std::getline(std::cin, str);
    int dots = 0;

    for (int i = 0; i < str.length(); ++i)
    {
        if (str[i] == '.')
        {
            ++dots;
            if (dots >= 4)
            {
                std::cout << "NO" << std::endl;
                return 0;
            }
        }
    }

    std::stringstream ss(str);
    std::string str0, str1, str2, str3;
    std::getline(ss, str0, '.');
    std::getline(ss, str1, '.');
    std::getline(ss, str2, '.');
    std::getline(ss, str3, '.');

    size_t num_digits;
    int num[4] = {0, 0, 0, 0};
    try
    {
        num[0] = std::stoi(str0, &num_digits);
        if (num_digits != str0.length())
        {
            throw std::invalid_argument(str0);
        }

        num[1] = std::stoi(str1, &num_digits);
        if (num_digits != str1.length())
        {
            throw std::invalid_argument(str1);
        }

        num[2] = std::stoi(str2, &num_digits);
        if (num_digits != str2.length())
        {
            throw std::invalid_argument(str2);
        }

        num[3] = std::stoi(str3, &num_digits);
        if (num_digits != str3.length())
        {
            throw std::invalid_argument(str3);
        }

        for (int i = 0; i < 4; ++i)
        {
            if (num[i] < 0 || num[i] > 255)
            {
                throw 1;
            }
        }
    }
    catch (...)
    {
        std::cout << "NO" << std::endl;
        return 0;
    }

    std::cout << "YES" << std::endl;
}