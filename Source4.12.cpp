#define NOMINMAX
#include <iostream>
#include <cmath>
#include <iomanip>
#include <windows.h>

void setupLocale() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
}

double calculatePolynomial(double x, int n) {
    double sum = 1.0;
    for (int i = 1; i <= n; ++i) {
        sum += std::pow(x, 3 * i);
    }
    return sum;
}

int main() {
    setupLocale();

    double x;
    int n;

    std::cout << "Введіть значення аргументу x: ";
    std::cin >> x;
    std::cout << "Введіть значення n: ";
    std::cin >> n;

    if (n < 0) {
        std::cout << "Помилка: n має бути невід'ємним числом!" << std::endl;
    }
    else {
        double result = calculatePolynomial(x, n);
        std::cout << std::fixed << std::setprecision(5);
        std::cout << "Значення многочлена y = " << result << std::endl;
    }

    return 0;
}