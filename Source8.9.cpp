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
    std::cout << "Введіть розмір квадратної матриці n (n < 200): ";
    std::cin >> n;

    if (n <= 0 || n >= 200) {
        std::cout << "Помилка: розмір матриці повинен бути в межах від 1 до 199!" << std::endl;
        return 0;
    }

    std::vector<std::vector<double>> a(n, std::vector<double>(2 * n, 0.0));

    std::cout << "Введіть елементи матриці рядок за рядком:" << std::endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> a[i][j];
        }
    }

    for (int i = 0; i < n; ++i) {
        a[i][n + i] = 1.0;
    }

    for (int i = 0; i < n; ++i) {
        if (std::abs(a[i][i]) < 1e-9) {
            bool swapped = false;
            for (int k = i + 1; k < n; ++k) {
                if (std::abs(a[k][i]) > 1e-9) {
                    std::swap(a[i], a[k]);
                    swapped = true;
                    break;
                }
            }
            if (!swapped) {
                std::cout << "Матриця вироджена, оберненої матриці не існує!" << std::endl;
                return 0;
            }
        }

        double pivot = a[i][i];
        for (int j = i; j < 2 * n; ++j) {
            a[i][j] /= pivot;
        }

        for (int k = 0; k < n; ++k) {
            if (k != i) {
                double factor = a[k][i];
                for (int j = i; j < 2 * n; ++j) {
                    a[k][j] -= factor * a[i][j];
                }
            }
        }
    }

    std::cout << "\nОбернена матриця:" << std::endl;
    std::cout << std::fixed << std::setprecision(5);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << std::setw(12) << a[i][n + j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}