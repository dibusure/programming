/*
Вам дан словарь, состоящий из пар слов. Каждое слово является синонимом к парному ему слову. Все слова в словаре различны. Для одного данного слова определите его синоним.
Программа получает на вход количество пар синонимов N. Далее следует N строк, каждая строка содержит ровно два слова-синонима. После этого следует одно слово.
*/
#include <map>
#include <string>
#include <iostream>

int main()
{
    int n = 0;
    std::cin >> n;
    std::map<std::string, std::string> dict;
    std::string word1, word2;

    for (int i = 0; i < n; ++i)
    {
        std::cin >> word1 >> word2;
        dict[word1] = word2;
        dict[word2] = word1;
    }

    std::string query;
    std::cin >> query;
    std::cout << dict[query] << std::endl;
}