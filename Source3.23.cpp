#define NOMINMAX // Захищає від конфлікту з макросом max
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
    return 0.0;
}

double onestep_derivative(double x) {
    if (x == 0.0) {
        return std::numeric_limits<double>::max();
    }
    return 0.0;
}

int main() {
    setupLocale();

    double x;
    std::cout << "Введіть значення x: ";
    std::cin >> x;

    double fx = onestep(x);
    double gx = onestep_derivative(x);

    std::cout << "Значення функції onestep(x) = " << fx << std::endl;
    std::cout << "Значення похідної в точці x = " << gx << std::endl;

    return 0;
}