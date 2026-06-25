#define NOMINMAX
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <windows.h>

void setupLocale() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
}

std::string toLower(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) {
        return std::tolower(c);
        });
    return str;
}

class Book {
private:
    std::string title;
    std::string author;
    int pages;
    int year;

public:
    Book() : title(""), author(""), pages(0), year(0) {}

    Book(std::string t, std::string a, int p, int y)
        : title(t), author(a), pages(p), year(y) {
    }

    std::string getTitle() const { return title; }
    std::string getAuthor() const { return author; }
    int getPages() const { return pages; }
    int getYear() const { return year; }

    void print() const {
        std::cout << "\"" << title << "\" | Автор: " << author
            << " | Сторінок: " << pages << " | Рік: " << year << std::endl;
    }

    void saveToFile(std::ofstream& out) const {
        out << title << "\n" << author << "\n" << pages << "\n" << year << "\n";
    }

    bool loadFromFile(std::ifstream& in) {
        if (!std::getline(in, title)) return false;
        if (!std::getline(in, author)) return false;
        in >> pages;
        in >> year;
        in.ignore();
        return true;
    }
};

void createSampleCatalog(const std::string& filename) {
    std::ofstream out(filename);
    if (out.is_open()) {
        Book b1("Kobzar", "Taras Shevchenko", 450, 1840);
        Book b2("Tyhrolovy", "Ivan Bahrianyis", 320, 1944);
        Book b3("Lisova Pisnia", "Lesia Ukrainka", 180, 1911);
        Book b4("Zahar Berkut", "Ivan Franko", 280, 1883);

        b1.saveToFile(out);
        b2.saveToFile(out);
        b3.saveToFile(out);
        b4.saveToFile(out);
        out.close();
    }
}

int main() {
    setupLocale();

    std::string filename = "catalog.txt";
    createSampleCatalog(filename);

    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cout << "Помилка: не вдалося відкрити файл каталогу!" << std::endl;
        return 0;
    }

    std::vector<Book> catalog;
    Book temp;
    while (temp.loadFromFile(in)) {
        catalog.push_back(temp);
    }
    in.close();

    std::cout << "=== Каталог книг успішно завантажено з файлу (" << catalog.size() << " книг) ===" << std::endl;

    std::string searchAuthor;
    std::cout << "\nВведіть автора для пошуку (або його частину): ";
    std::getline(std::cin, searchAuthor);
    searchAuthor = toLower(searchAuthor);

    std::cout << "Результати пошуку за автором:" << std::endl;
    bool foundAuthor = false;
    for (const auto& book : catalog) {
        if (toLower(book.getAuthor()).find(searchAuthor) != std::string::npos) {
            book.print();
            foundAuthor = true;
        }
    }
    if (!foundAuthor) std::cout << "Книг цього автора не знайдено." << std::endl;

    std::string searchTitle;
    std::cout << "\nВведіть назву книги для пошуку (або її частину): ";
    std::getline(std::cin, searchTitle);
    searchTitle = toLower(searchTitle);

    std::cout << "Результати пошуку за назвою:" << std::endl;
    bool foundTitle = false;
    for (const auto& book : catalog) {
        if (toLower(book.getTitle()).find(searchTitle) != std::string::npos) {
            book.print();
            foundTitle = true;
        }
    }
    if (!foundTitle) std::cout << "Книг з такою назвою не знайдено." << std::endl;

    return 0;
}