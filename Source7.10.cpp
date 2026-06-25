#define NOMINMAX
#include <iostream>
#include <vector>
#include <cmath>
#include <windows.h>

void setupLocale() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
}

int main() {
    setupLocale();

    int n;
    std::cout << "Введіть натуральне число n: ";
    std::cin >> n;

    if (n <= 0) {
        std::cout << "Помилка: n має бути більшим за 0!" << std::endl;
        return 0;
    }

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cout << "Введіть ціле число a[" << i + 1 << "]: ";
        std::cin >> a[i];
    }

    int k = static_cast<int>(std::sqrt(n));
    int count = 0;

    for (int i = 1; i <= k; ++i) {
        int index = i * i;
        if (a[index - 1] % 2 == 0) {
            count++;
        }
    }

    std::cout << "Кількість парних серед елементів з квадратними індексами: " << count << std::endl;

    return 0;
}