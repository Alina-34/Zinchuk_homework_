#define NOMINMAX
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

    double x, eps;

    std::cout << "Введіть значення x (|x| < 1): ";
    std::cin >> x;
    std::cout << "Введіть точність eps (eps > 0): ";
    std::cin >> eps;

    if (std::abs(x) >= 1.0) {
        std::cout << "Помилка: значення x за абсолютною величиною має бути меншим за 1!" << std::endl;
        return 0;
    }
    if (eps <= 0) {
        std::cout << "Помилка: точність eps має бути більшою за 0!" << std::endl;
        return 0;
    }

    double sum = 0.0;
    double term = 1.0;
    int n = 0;

    while (std::abs(term) >= eps) {
        sum += term;
        n++;
        term = (n % 2 == 0 ? 1.0 : -1.0) * (n + 1) * std::pow(x, n);
    }

    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Наближена сума ряду: " << sum << std::endl;
    std::cout << "Точне значення 1/(1+x)^2: " << 1.0 / std::pow(1.0 + x, 2) << std::endl;
    std::cout << "Кількість врахованих доданків: " << n << std::endl;

    return 0;
}