#include <iostream>
#include <cmath>
#include <iomanip>
#include <windows.h>

void setupLocale() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
}

double sigmoid(double x) {
    return 1.0 / (1.0 + std::exp(-x));
}

double sigmoid_derivative(double x) {
    double fx = sigmoid(x);
    return fx * (1.0 - fx);
}

int main() {
    setupLocale();

    double x;
    std::cout << "Введіть значення x: ";
    std::cin >> x;

    double fx = sigmoid(x);
    double gx = sigmoid_derivative(x);

    std::cout << std::fixed << std::setprecision(5);
    std::cout << "Значення функції f(x) = " << fx << std::endl;
    std::cout << "Значення похідної g(x) = " << gx << std::endl;

    return 0;
}