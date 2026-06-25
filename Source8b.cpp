#define NOMINMAX
#include <iostream>
#include <vector>
#include <cmath>
#include <windows.h>

void setupLocale() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
}

bool isEvenPerfectCube(int num) {
    if (num % 2 != 0) {
        return false;
    }

    int root = static_cast<int>(std::round(std::cbrt(num)));
    return (root * root * root == num);
}

int main() {
    setupLocale();

    int n;
    std::cout << "Введіть розмір масиву N: ";
    std::cin >> n;

    if (n <= 0) {
        std::cout << "Помилка: розмір масиву має бути більшим за 0!" << std::endl;
        return 0;
    }

    int count = 0;
    for (int i = 0; i < n; ++i) {
        int val;
        std::cout << "Введіть число [" << i + 1 << "]: ";
        std::cin >> val;

        if (val <= 0) {
            std::cout << "Помилка: число має бути натуральним (більшим за 0)!" << std::endl;
            --i;
            continue;
        }

        if (isEvenPerfectCube(val)) {
            count++;
        }
    }

    std::cout << "Кількість парних повних кубів: " << count << std::endl;

    return 0;
}