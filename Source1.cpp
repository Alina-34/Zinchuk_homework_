#include <iostream>
#include <cmath>
#include <iomanip>
#include <windows.h>

void setupLocale() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
}

int main() {
    setupLocale();

    double number;
    std::cout << "Введіть число для обчислення десяткового логарифму: ";
    std::cin >> number;

    if (number <= 0) {
        std::cout << "Помилка: логарифм визначений тільки для чисел більших за 0!" << std::endl;
    }
    else {
        double result = std::log10(number);
        std::cout << std::fixed << std::setprecision(3);
        std::cout << "Значення функції log10: " << result << std::endl;
    }

    return 0;
}