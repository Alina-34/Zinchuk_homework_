#define NOMINMAX
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <windows.h>

void setupLocale() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
}

int main() {
    setupLocale();

    std::string inputName = "input.txt";
    std::string outputName = "output.txt";

    std::ifstream inFile(inputName);
    if (!inFile.is_open()) {
        std::cout << "Помилка: не вдалося відкрити файл " << inputName << std::endl;
        std::cout << "Будь ласка, створіть цей файл у папці з проєктом." << std::endl;
        return 0;
    }

    std::string content((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
    inFile.close();

    std::regex numberRegex(R"(-?\d+)");
    std::sregex_iterator begin(content.begin(), content.end(), numberRegex);
    std::sregex_iterator end;

    std::vector<int> validNumbers;
    for (std::sregex_iterator i = begin; i != end; ++i) {
        std::smatch match = *i;
        int num = std::stoi(match.str());
        if (num > 0) {
            validNumbers.push_back(num);
        }
    }

    std::ofstream outFile(outputName);
    if (!outFile.is_open()) {
        std::cout << "Помилка: не вдалося створити вихідний файл " << outputName << std::endl;
        return 0;
    }

    for (size_t i = 0; i < validNumbers.size(); ++i) {
        outFile << validNumbers[i];
        if (i != validNumbers.size() - 1) {
            outFile << " ";
        }
    }
    outFile.close();

    std::cout << "Файл успішно оброблено! Результат збережено в " << outputName << std::endl;

    return 0;
}