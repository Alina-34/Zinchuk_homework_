#include <iostream>
#include <iomanip>
#include <string>

void setupLocale() {
    std::setlocale(LC_ALL, "UKR");
#ifdef _WIN32
    system("chcp 1251 > nul");
#endif
}

int main() {
    setupLocale();

    int x[5] = { 1, 2, 3, 4, 5 };
    double y[5] = { 3.0, 1.0, 5.0, 4.0, 2.1 };
    int width = 5;

    std::cout << "x |";
    for (int i = 0; i < 5; ++i) {
        std::cout << std::setw(width) << x[i] << " |";
    }
    std::cout << std::endl;

    std::cout << "- |";
    for (int i = 0; i < 5; ++i) {
        std::cout << std::string(width, '-') << " |";
    }
    std::cout << std::endl;

    std::cout << "y |";
    std::cout << std::fixed;
    for (int i = 0; i < 5; ++i) {
        std::cout << std::setw(width) << std::setprecision(1) << y[i] << " |";
    }
    std::cout << std::endl;

    return 0;
}