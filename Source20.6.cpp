#define NOMINMAX
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <windows.h>

void setupLocale() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
}

bool tryParseInt(const std::string& str, int& outValue) {
    std::stringstream ss(str);
    // Зчитуємо ціле число
    if (!(ss >> outValue)) {
        return false;
    }
    // Перевіряємо, чи не залишилося в рядку зайвих нечислових символів (наприклад, "123a")
    char extra;
    if (ss >> extra) {
        return false;
    }
    return true;
}

int main() {
    setupLocale();

    std::string filename = "numbers.txt";
    std::vector<int> V;

    std::cout << "Спроба зчитати дані з файлу \"" << filename << "\"..." << std::endl;

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Помилка: Не вдалося відкрити або знайти файл \"" << filename << "\"!" << std::endl;
        return 1;
    }

    std::string token;
    int lineCount = 0;

    // Зчитуємо кожне окреме слово/токен з файлу
    while (file >> token) {
        int number;
        if (!tryParseInt(token, number)) {
            std::cerr << "\n[КРИТИЧНА ПОМИЛКА]: Виявлено некоректні дані у файлі!" << std::endl;
            std::cerr << "Неможливо інтерпретувати елемент \"" << token << "\" як ціле число." << std::endl;
            std::cerr << "Роботу програми завершено аварійно." << std::endl;
            file.close();
            return 1;
        }
        V.push_back(number);
    }

    file.close();

    // Якщо файл виявився порожнім
    if (V.empty()) {
        std::cout << "Попередження: Файл порожній або не містить жодних даних." << std::endl;
        return 0;
    }

    std::cout << "\nДані успішно зчитано та перевірено! Кількість елементів: " << V.size() << std::endl;
    std::cout << "Виведення чисел у вихідному (зворотному) порядку:" << std::endl;

    // Виводимо вектор у зворотному порядку за допомогою reverse-ітераторів
    for (auto it = V.rbegin(); it != V.rend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}