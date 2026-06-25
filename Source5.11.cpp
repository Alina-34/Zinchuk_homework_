#define NOMINMAX
#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <windows.h>

void setupLocale() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
}

int main() {
    setupLocale();

    int n;
    std::cout << "Введіть значення n: ";
    std::cin >> n;

    if (n <= 0) {
        std::cout << "Помилка: n має бути більшим за 0!" << std::endl;
        return 0;
    }

    std::vector<double> a(n + 1);

    if (n >= 1) a[1] = 0.0;
    if (n >= 2) a[2] = 1.0;

    for (int k = 3; k <= n; ++k) {
        a[k] = a[k - 1] + k * a[k - 2];
    }

    double sum = 0.0;
    for (int k = 1; k <= n; ++k) {
        sum += std::pow(2, k) * a[k];
    }

    std::cout << std::fixed << std::setprecision(5);
    std::cout << "Результат суми Sn = " << sum << std::endl;

    return 0;
}