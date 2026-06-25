#define NOMINMAX
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <windows.h>

void setupLocale() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
}

void printMatrix(const std::vector<std::vector<double>>& matrix) {
    if (matrix.empty()) {
        std::cout << "Масив порожній!" << std::endl;
        return;
    }
    std::cout << std::fixed << std::setprecision(2);
    for (const auto& row : matrix) {
        for (double val : row) {
            std::cout << std::setw(8) << val << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    setupLocale();
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    int n, m;
    std::cout << "Введіть кількість рядків N: ";
    std::cin >> n;
    std::cout << "Введіть кількість стовпців M: ";
    std::cin >> m;

    if (n <= 0 || m <= 0) {
        std::cout << "Помилка: розміри масиву мають бути більшими за 0!" << std::endl;
        return 0;
    }

    std::vector<std::vector<double>> matrix(n, std::vector<double>(m));

    int choice;
    std::cout << "Виберіть спосіб заповнення (1 - з консолі, 2 - випадковими числами): ";
    std::cin >> choice;

    if (choice == 1) {
        std::cout << "Введіть елементи масиву:" << std::endl;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                std::cin >> matrix[i][j];
            }
        }
    }
    else {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                matrix[i][j] = (std::rand() % 1000) / 10.0;
            }
        }
    }

    std::cout << "\nПочатковий масив:" << std::endl;
    printMatrix(matrix);

    int k1, k2;
    std::cout << "\nВведіть номер початкового рядка для видалення k1: ";
    std::cin >> k1;
    std::cout << "Введіть номер кінцевого рядка для видалення k2: ";
    std::cin >> k2;

    if (k1 < 1 || k2 > n || k1 > k2) {
        std::cout << "Помилка: некоректні межі рядків k1 та k2!" << std::endl;
        return 0;
    }

    matrix.erase(matrix.begin() + (k1 - 1), matrix.begin() + k2);

    std::cout << "\nМасив після видалення рядків від " << k1 << " до " << k2 << ":" << std::endl;
    printMatrix(matrix);

    return 0;
}