#define NOMINMAX
#include <iostream>
#include <string>
#include <windows.h>

void setupLocale() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
}

struct Cost {
    int hryvnias;
    int kopecks;
};

void inputCost(Cost& c) {
    std::cout << "Введіть гривні: ";
    std::cin >> c.hryvnias;
    std::cout << "Введіть копійки: ";
    std::cin >> c.kopecks;
}

void printCost(const Cost& c) {
    std::cout << c.hryvnias << " грн. " << c.kopecks << " коп." << std::endl;
}

struct Time {
    int hour;
    int minute;
    int second;
};

void inputTime(Time& t) {
    std::cout << "Введіть годину: ";
    std::cin >> t.hour;
    std::cout << "Введіть хвилину: ";
    std::cin >> t.minute;
    std::cout << "Введіть секунду: ";
    std::cin >> t.second;
}

void printTime(const Time& t) {
    std::cout << t.hour << ":" << t.minute << ":" << t.second << std::endl;
}

struct FullDate {
    int day;
    int month;
    int year;
    int hour;
    int minute;
};

void inputFullDate(FullDate& fd) {
    std::cout << "Введіть число (день): ";
    std::cin >> fd.day;
    std::cout << "Введіть місяць: ";
    std::cin >> fd.month;
    std::cout << "Введіть рік: ";
    std::cin >> fd.year;
    std::cout << "Введіть годину: ";
    std::cin >> fd.hour;
    std::cout << "Введіть хвилину: ";
    std::cin >> fd.minute;
}

void printFullDate(const FullDate& fd) {
    std::cout << fd.day << "." << fd.month << "." << fd.year << " " << fd.hour << ":" << fd.minute << std::endl;
}

struct Address {
    std::string city;
    std::string street;
    std::string house;
    int apartment;
};

void inputAddress(Address& addr) {
    std::cin.ignore();
    std::cout << "Введіть місто: ";
    std::getline(std::cin, addr.city);
    std::cout << "Введіть вулицю: ";
    std::getline(std::cin, addr.street);
    std::cout << "Введіть будинок: ";
    std::getline(std::cin, addr.house);
    std::cout << "Введіть квартиру: ";
    std::cin >> addr.apartment;
}

void printAddress(const Address& addr) {
    std::cout << "м. " << addr.city << ", вул. " << addr.street << ", буд. " << addr.house << ", кв. " << addr.apartment << std::endl;
}

struct Seminar {
    std::string subject;
    std::string teacher;
    std::string group_number;
    std::string day_of_week;
    int class_hours;
    std::string classroom;
};

void inputSeminar(Seminar& sem) {
    std::cin.ignore();
    std::cout << "Введіть предмет: ";
    std::getline(std::cin, sem.subject);
    std::cout << "Введіть викладача: ";
    std::getline(std::cin, sem.teacher);
    std::cout << "Введіть № групи: ";
    std::getline(std::cin, sem.group_number);
    std::cout << "Введіть день тижня: ";
    std::getline(std::cin, sem.day_of_week);
    std::cout << "Введіть години занять (кількість): ";
    std::cin >> sem.class_hours;
    std::cin.ignore();
    std::cout << "Введіть аудиторію: ";
    std::getline(std::cin, sem.classroom);
}

void printSeminar(const Seminar& sem) {
    std::cout << "Предмет: " << sem.subject << " | Викладач: " << sem.teacher
        << " | Група: " << sem.group_number << " | День: " << sem.day_of_week
        << " | Годин: " << sem.class_hours << " | Ауд: " << sem.classroom << std::endl;
}

int main() {
    setupLocale();

    std::cout << "=== Введення вартості ===" << std::endl;
    Cost myCost;
    inputCost(myCost);
    std::cout << "Вартість: ";
    printCost(myCost);

    std::cout << "\n=== Введення часу ===" << std::endl;
    Time myTime;
    inputTime(myTime);
    std::cout << "Час: ";
    printTime(myTime);

    std::cout << "\n=== Введення повної дати ===" << std::endl;
    FullDate myDate;
    inputFullDate(myDate);
    std::cout << "Повна дата: ";
    printFullDate(myDate);

    std::cout << "\n=== Введення адреси ===" << std::endl;
    Address myAddress;
    inputAddress(myAddress);
    std::cout << "Адреса: ";
    printAddress(myAddress);

    std::cout << "\n=== Введення семінару ===" << std::endl;
    Seminar mySeminar;
    inputSeminar(mySeminar);
    std::cout << "Семінар: ";
    printSeminar(mySeminar);

    return 0;
}