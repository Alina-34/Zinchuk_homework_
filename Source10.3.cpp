#define NOMINMAX
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <windows.h>

const int CURRENT_YEAR = 2026;

void setupLocale() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
}

struct Date {
    int day;
    int month;
    int year;
};

struct Employee {
    std::string surname;
    std::string name;
    std::string gender; // "чоловіча" або "жіноча"
    Date birthDate;
    std::string position;
};

int calculateAge(const Employee& emp) {
    return CURRENT_YEAR - emp.birthDate.year;
}

void findMostPopularPosition(const std::vector<Employee>& p) {
    if (p.empty()) return;
    std::map<std::string, int> counts;
    for (const auto& emp : p) {
        counts[emp.position]++;
    }
    std::string max_pos = "";
    int max_count = 0;
    for (const auto& pair : counts) {
        if (pair.second > max_count) {
            max_count = pair.second;
            max_pos = pair.first;
        }
    }
    std::cout << "Посада, яку обіймає найбільша кількість співробітників: " << max_pos
        << " (" << max_count << " осіб)" << std::endl;
}

void findEmployeesWithSameNames(const std::vector<Employee>& p) {
    std::map<std::string, std::vector<size_t>> name_indices;
    for (size_t i = 0; i < p.size(); ++i) {
        name_indices[p[i].name].push_back(i);
    }
    bool found = false;
    std::cout << "Співробітники з однаковими іменами:" << std::endl;
    for (const auto& pair : name_indices) {
        if (pair.second.size() > 1) {
            found = true;
            std::cout << "Ім'я '" << pair.first << "': ";
            for (size_t idx : pair.second) {
                std::cout << p[idx].surname << " " << p[idx].name << "; ";
            }
            std::cout << std::endl;
        }
    }
    if (!found) std::cout << "Таких співробітників не знайдено." << std::endl;
}

void findEmployeesByLetter(const std::vector<Employee>& p, char letter) {
    bool found = false;
    std::cout << "Співробітники, прізвища яких починаються з літери '" << letter << "':" << std::endl;
    for (const auto& emp : p) {
        if (!emp.surname.empty() && (emp.surname[0] == letter || emp.surname[0] == std::toupper(letter))) {
            std::cout << emp.surname << " " << emp.name << " (" << emp.position << ")" << std::endl;
            found = true;
        }
    }
    if (!found) std::cout << "Таких співробітників не знайдено." << std::endl;
}

void findOldestMan(const std::vector<Employee>& p) {
    const Employee* oldest = nullptr;
    for (const auto& emp : p) {
        if (emp.gender == "чоловіча") {
            if (oldest == nullptr || emp.birthDate.year < oldest->birthDate.year) {
                oldest = &emp;
            }
        }
    }
    if (oldest != nullptr) {
        std::cout << "Найстарший з чоловіків: " << oldest->surname << " " << oldest->name
            << ", Рік народження: " << oldest->birthDate.year << std::endl;
    }
    else {
        std::cout << "У закладі немає чоловіків." << std::endl;
    }
}

void findEmployeesYoungerThanAverage(const std::vector<Employee>& p) {
    if (p.empty()) return;
    double total_age = 0;
    for (const auto& emp : p) {
        total_age += calculateAge(emp);
    }
    double avg_age = total_age / p.size();
    std::cout << "Середній вік по організації: " << avg_age << " років." << std::endl;
    std::cout << "Співробітники, вік яких менший за середній:" << std::endl;
    bool found = false;
    for (const auto& emp : p) {
        if (calculateAge(emp) < avg_age) {
            std::cout << emp.surname << " " << emp.name << " (" << calculateAge(emp) << " років)" << std::endl;
            found = true;
        }
    }
    if (!found) std::cout << "Таких співробітників не знайдено." << std::endl;
}

void findRetirementAgeEmployees(const std::vector<Employee>& p) {
    bool found = false;
    std::cout << "Співробітники пенсійного віку:" << std::endl;
    for (const auto& emp : p) {
        int age = calculateAge(emp);
        if ((emp.gender == "чоловіча" && age >= 65) || (emp.gender == "жіноча" && age >= 60)) {
            std::cout << emp.surname << " " << emp.name << " (" << emp.gender
                << ", " << age << " років, " << emp.position << ")" << std::endl;
            found = true;
        }
    }
    if (!found) std::cout << "Співробітників пенсійного віку не знайдено." << std::endl;
}

int main() {
    setupLocale();

    int n;
    std::cout << "Введіть кількість співробітників N: ";
    std::cin >> n;

    if (n <= 0) {
        std::cout << "Помилка: кількість має бути більшою за 0!" << std::endl;
        return 0;
    }

    std::vector<Employee> P(n);
    for (int i = 0; i < n; ++i) {
        std::cout << "\n--- Введення анкети " << i + 1 << " ---" << std::endl;
        std::cout << "Прізвище: ";
        std::cin >> P[i].surname;
        std::cout << "Ім'я: ";
        std::cin >> P[i].name;
        std::cout << "Стать (чоловіча/жіноча): ";
        std::cin >> P[i].gender;
        std::cout << "День народження: ";
        std::cin >> P[i].birthDate.day;
        std::cout << "Місяць народження: ";
        std::cin >> P[i].birthDate.month;
        std::cout << "Рік народження: ";
        std::cin >> P[i].birthDate.year;
        std::cout << "Посада: ";
        std::cin.ignore();
        std::getline(std::cin, P[i].position);
    }

    std::cout << "\n================ РЕЗУЛЬТАТИ ПОШУКУ ================" << std::endl;

    std::cout << "\n[а] ";
    findMostPopularPosition(P);

    std::cout << "\n[б] ";
    findEmployeesWithSameNames(P);

    std::cout << "\n[в] ";
    char searchLetter;
    std::cout << "Введіть літеру для пошуку прізвищ: ";
    std::cin >> searchLetter;
    findEmployeesByLetter(P, searchLetter);

    std::cout << "\n[г] ";
    findOldestMan(P);

    std::cout << "\n[д] ";
    findEmployeesYoungerThanAverage(P);

    std::cout << "\n[е] ";
    findRetirementAgeEmployees(P);

    return 0;
}