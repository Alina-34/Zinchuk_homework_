#define NOMINMAX
#include <iostream>
#include <vector>
#include <iomanip>
#include <windows.h>

void setupLocale() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
}

int main() {
    setupLocale();

    int n;
    std::cout << "Введіть кількість елементів n: ";
    std::cin >> n;

    if (n <= 0) {
        std::cout << "Помилка: кількість елементів має бути більшою за 0!" << std::endl;
        return 0;
    }

    double sum = 0.0;
    for (int i = 0; i < n; ++i) {
        double y;
        std::cout << "Введіть число y[" << i + 1 << "]: ";
        std::cin >> y;

        double z;
        if (y < 10.0) {
            z = y;
        }
        else {
            z = 1.0;
        }

        sum += z;
    }

    std::cout << std::fixed << std::setprecision(5);
    std::cout << "Сума елементів z1 + z2 + ... + zn = " << sum << std::endl;

    return 0;
}