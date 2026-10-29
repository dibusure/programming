// Демонстрация подсветки C++. Файл можно удалить.
#include <iostream>

int main() {
    int a = 0;
    int b = 1;

    std::cout << "Hello, C++!\n";
    for (int i = 0; i < 12; ++i) {
        std::cout << a << ' ';
        const int next = a + b;
        a = b;
        b = next;
    }
    std::cout << '\n';
}
