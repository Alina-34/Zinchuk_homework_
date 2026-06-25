#include <iostream>
#include <cmath>
#include <windows.h>

void setupLocale() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
}

int main() {
    setupLocale();

    double r, a, b, c;

    std::cout << "Введіть радіус кола r: ";
    std::cin >> r;
    std::cout << "Введіть координату відрізка a (x = a): ";
    std::cin >> a;
    std::cout << "Введіть початок проміжку b: ";
    std::cin >> b;
    std::cout << "Введіть параметр c: ";
    std::cin >> c;

    if (r < 0) {
        std::cout << "Помилка: радіус кола не може бути від'ємним!" << std::endl;
        return 0;
    }

    double y_min = b;
    double y_max = b + c * c;
    int count = 0;

    double d = r * r - a * a;

    if (d > 0) {
        double y1 = std::sqrt(d);
        double y2 = -std::sqrt(d);

        if (y1 >= y_min && y1 <= y_max) {
            count++;
        }
        if (y2 >= y_min && y2 <= y_max) {
            count++;
        }
    }
    else if (std::abs(d) < 1e-9) {
        double y0 = 0.0;
        if (y0 >= y_min && y0 <= y_max) {
            count++;
        }
    }

    std::cout << "Число точок перетину: " << count << std::endl;

    return 0;
}