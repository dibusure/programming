// Дана строка, содержащая пробелы. Найдите, сколько в ней слов (слово – это последовательность непробельных символов, слова разделены одним пробелом, первый и последний символ строки – не пробел).
#include <iostream>
#include <string.h>

int main()
{
    std::string line;
    int counter = 0;
    std::getline(std::cin, line);
    for (auto c : line)
    {
        if (c == ' ')
            ++counter;
    }
    ++counter;
    std::cout << counter << std::endl;
}