#define NOMINMAX
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <algorithm>
#include <cctype>
#include <windows.h>

void setupLocale() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
}

// Функція для очищення слова від знаків пунктуації та приведення до нижнього регістру
std::string cleanWord(const std::string& rawWord) {
    std::string cleaned = "";
    for (char ch : rawWord) {
        // Залишаємо лише літери та цифри (можна розширити для апострофа, якщо потрібно)
        if (std::isalnum(static_cast<unsigned char>(ch)) || ch == '\'' || ch == '-') {
            cleaned += std::tolower(static_cast<unsigned char>(ch));
        }
    }
    return cleaned;
}

int main() {
    setupLocale();

    std::string sentence;
    int targetCount;

    std::cout << "Введіть речення:\n";
    std::getline(std::cin, sentence);

    std::cout << "Введіть кількість повторень для видалення слів: ";
    while (!(std::cin >> targetCount) || targetCount < 1) {
        std::cout << "Будь ласка, введіть коректне додатне число: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // Розбиваємо речення на слова та зберігаємо оригінальні токени
    std::vector<std::string> originalWords;
    std::stringstream ss(sentence);
    std::string token;

    while (ss >> token) {
        originalWords.push_back(token);
    }

    // Підраховуємо частоту зустрічання кожного очищеного слова
    std::unordered_map<std::string, int> wordFrequencies;
    for (const auto& w : originalWords) {
        std::string cleaned = cleanWord(w);
        if (!cleaned.empty()) {
            wordFrequencies[cleaned]++;
        }
    }

    // Формуємо нове речення, пропускаючи слова із заданою частотою
    std::vector<std::string> resultWords;
    for (const auto& w : originalWords) {
        std::string cleaned = cleanWord(w);

        // Якщо очищене слово має частоту, що дорівнює targetCount — ігноруємо його
        if (!cleaned.empty() && wordFrequencies[cleaned] == targetCount) {
            continue;
        }
        resultWords.push_back(w);
    }

    // Виводимо результат
    std::cout << "\n=== РЕЗУЛЬТАТ РЕДАГУВАННЯ ===" << std::endl;
    if (resultWords.empty()) {
        std::cout << "(Після видалення слів речення залишилося порожнім)" << std::endl;
    }
    else {
        for (size_t i = 0; i < resultWords.size(); ++i) {
            std::cout << resultWords[i] << (i == resultWords.size() - 1 ? "" : " ");
        }
        std::cout << std::endl;
    }

    // Інформаційне виведення частот для перевірки користувачем
    std::cout << "\n[Статистика частоти слів для довідки]:" << std::endl;
    for (const auto& pair : wordFrequencies) {
        std::cout << "  \"" << pair.first << "\" -> зустрічається " << pair.second << " раз(и)." << std::endl;
    }

    return 0;
}