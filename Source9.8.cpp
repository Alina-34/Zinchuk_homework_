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

    std::vector<double> all_values;
    char proceed;

    do {
        int n;
        std::cout << "\nВведіть розмірність нового вектора дійсних чисел: ";
        std::cin >> n;

        if (n <= 0) {
            std::cout << "Помилка: розмірність має бути більшою за 0!" << std::endl;
            continue;
        }

        std::cout << "Введіть елементи вектора:" << std::endl;
        for (int i = 0; i < n; ++i) {
            double val;
            std::cin >> val;
            all_values.push_back(val);
        }

        double sum = 0.0;
        for (double val : all_values) {
            sum += val;
        }
        double mean = sum / all_values.size();

        double variance_sum = 0.0;
        for (double val : all_values) {
            variance_sum += std::pow(val - mean, 2);
        }
        double variance = variance_sum / all_values.size();

        std::cout << std::fixed << std::setprecision(5);
        std::cout << "\n--- Статистика для всіх введених значень (всього елементів: " << all_values.size() << ") ---" << std::endl;
        std::cout << "Середнє арифметичне: " << mean << std::endl;
        std::cout << "Дисперсія: " << variance << std::endl;

        std::cout << "\nБажаєте ввести ще один вектор? (y/n): ";
        std::cin >> proceed;

    } while (proceed == 'y' || proceed == 'Y');

    std::cout << "Програму завершено." << std::endl;
    return 0;
}