#define NOMINMAX
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <windows.h>

void setupLocale() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
}

int main() {
    setupLocale();

    std::string text;
    std::cout << "Введіть рядок латинських символів: ";
    std::getline(std::cin, text);

    char targetChar;
    std::cout << "Введіть символ для пошуку: ";
    std::cin >> targetChar;

    char lowerTarget = std::tolower(static_cast<unsigned char>(targetChar));
    char upperTarget = std::toupper(static_cast<unsigned char>(targetChar));

    std::stringstream ss(text);
    std::string word;
    int wordCount = 0;

    while (ss >> word) {
        bool containsChar = false;
        for (char c : word) {
            if (c == lowerTarget || c == upperTarget) {
                containsChar = true;
                break;
            }
        }
        if (containsChar) {
            wordCount++;
        }
    }

    std::cout << "Кількість слів, що містять символ '" << targetChar << "': " << wordCount << std::endl;

    return 0;
}