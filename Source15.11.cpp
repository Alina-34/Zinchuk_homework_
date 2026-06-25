#define NOMINMAX
#include <iostream>
#include <limits>
#include <windows.h>

void setupLocale() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
}

double onestep(double x) {
    if (x >= 0.0) {
        return 1.0;
    }
    else {
        return 0.0;
    }
}

double onestepDerivative(double x) {
    if (x == 0.0) {
        return std::numeric_limits<double>::max();
    }
    return 0.0;
}

int main() {
    setupLocale();

    double x_values[] = { -5.5, -0.001, 0.0, 0.001, 10.25 };

    std::cout << "Перевірка роботи функцій:" << std::endl;
    for (double x : x_values) {
        std::cout << "x = " << x
            << " | onestep(x) = " << onestep(x)
            << " | Похідна = " << onestepDerivative(x) << std::endl;
    }

    return 0;
}