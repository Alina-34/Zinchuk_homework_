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

    double a, b, c, r;

    std::cout << "Введіть перший кут (у градусах): ";
    std::cin >> a;
    std::cout << "Введіть другий кут (у градусах): ";
    std::cin >> b;
    std::cout << "Введіть третій кут (у градусах): ";
    std::cin >> c;
    std::cout << "Введіть радіус вписаного кола: ";
    std::cin >> r;

    if (std::abs(a + b + c - 180.0) > 0.001) {
        std::cout << "Помилка: сума кутів трикутника повинна дорівнювати 180 градусам!" << std::endl;
    }
    else if (a <= 0 || b <= 0 || c <= 0 || r <= 0) {
        std::cout << "Помилка: значення повинні бути більшими за 0!" << std::endl;
    }
    else {
        double radA = a * 3.141592653589793 / 180.0;
        double radB = b * 3.141592653589793 / 180.0;
        double radC = c * 3.141592653589793 / 180.0;

        double ctgA = 1.0 / std::tan(radA / 2.0);
        double ctgB = 1.0 / std::tan(radB / 2.0);
        double ctgC = 1.0 / std::tan(radC / 2.0);

        double area = r * r * (ctgA + ctgB + ctgC);

        std::cout << std::fixed << std::setprecision(3);
        std::cout << "Площа трикутника: " << area << std::endl;
    }

    return 0;
}