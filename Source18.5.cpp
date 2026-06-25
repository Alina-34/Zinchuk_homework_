#define NOMINMAX
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include <iomanip>
#include <windows.h>

void setupLocale() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
}

enum class ProductType { Toy, Food, Tech };

struct Date {
    int day, month, year;
};

class Product {
protected:
    std::string name;
    std::string article;
    std::string unit;
    double price;
    Date deliveryDate;

public:
    Product() : price(0.0), deliveryDate{ 1, 1, 2026 } {}
    Product(std::string n, std::string art, std::string u, double p, Date d)
        : name(n), article(art), unit(u), price(p), deliveryDate(d) {
    }
    virtual ~Product() = default;

    virtual ProductType getType() const = 0;
    std::string getName() const { return name; }
    std::string getArticle() const { return article; }
    std::string getUnit() const { return unit; }
    double getPrice() const { return price; }

    virtual std::string getSpecificInfo() const = 0;

    virtual void serialize(std::ostream& os) const {
        size_t len = name.size();
        os.write(reinterpret_cast<const char*>(&len), sizeof(len));
        os.write(name.data(), len);

        len = article.size();
        os.write(reinterpret_cast<const char*>(&len), sizeof(len));
        os.write(article.data(), len);

        len = unit.size();
        os.write(reinterpret_cast<const char*>(&len), sizeof(len));
        os.write(unit.data(), len);

        os.write(reinterpret_cast<const char*>(&price), sizeof(price));
        os.write(reinterpret_cast<const char*>(&deliveryDate), sizeof(deliveryDate));
    }

    virtual void deserialize(std::istream& is) {
        size_t len;
        is.read(reinterpret_cast<char*>(&len), sizeof(len));
        name.resize(len);
        is.read(&name[0], len);

        is.read(reinterpret_cast<char*>(&len), sizeof(len));
        article.resize(len);
        is.read(&article[0], len);

        is.read(reinterpret_cast<char*>(&len), sizeof(len));
        unit.resize(len);
        is.read(&unit[0], len);

        is.read(reinterpret_cast<char*>(&price), sizeof(price));
        is.read(reinterpret_cast<char*>(&deliveryDate), sizeof(deliveryDate));
    }
};

class Toy : public Product {
private:
    int ageLimit;

public:
    Toy() : Product(), ageLimit(0) {}
    Toy(std::string n, std::string art, std::string u, double p, Date d, int age)
        : Product(n, art, u, p, d), ageLimit(age) {
    }

    ProductType getType() const override { return ProductType::Toy; }
    std::string getSpecificInfo() const override { return "Вік: " + std::to_string(ageLimit) + "+"; }

    void serialize(std::ostream& os) const override {
        Product::serialize(os);
        os.write(reinterpret_cast<const char*>(&ageLimit), sizeof(ageLimit));
    }

    void deserialize(std::istream& is) override {
        Product::deserialize(is);
        is.read(reinterpret_cast<char*>(&ageLimit), sizeof(ageLimit));
    }
};

class Food : public Product {
private:
    int expirationDays;

public:
    Food() : Product(), expirationDays(0) {}
    Food(std::string n, std::string art, std::string u, double p, Date d, int exp)
        : Product(n, art, u, p, d), expirationDays(exp) {
    }

    ProductType getType() const override { return ProductType::Food; }
    std::string getSpecificInfo() const override { return "Термін: " + std::to_string(expirationDays) + " днів"; }

    void serialize(std::ostream& os) const override {
        Product::serialize(os);
        os.write(reinterpret_cast<const char*>(&expirationDays), sizeof(expirationDays));
    }

    void deserialize(std::istream& is) override {
        Product::deserialize(is);
        is.read(reinterpret_cast<char*>(&expirationDays), sizeof(expirationDays));
    }
};

class Tech : public Product {
private:
    bool hasWarranty;
    int warrantyDays;

public:
    Tech() : Product(), hasWarranty(false), warrantyDays(0) {}
    Tech(std::string n, std::string art, std::string u, double p, Date d, bool hw, int wd)
        : Product(n, art, u, p, d), hasWarranty(hw), warrantyDays(wd) {
    }

    ProductType getType() const override { return ProductType::Tech; }
    std::string getSpecificInfo() const override { return hasWarranty ? "Гарантія: " + std::to_string(warrantyDays) + " дн." : "Без гарантії"; }

    void serialize(std::ostream& os) const override {
        Product::serialize(os);
        os.write(reinterpret_cast<const char*>(&hasWarranty), sizeof(hasWarranty));
        os.write(reinterpret_cast<const char*>(&warrantyDays), sizeof(warrantyDays));
    }

    void deserialize(std::istream& is) override {
        Product::deserialize(is);
        is.read(reinterpret_cast<char*>(&hasWarranty), sizeof(hasWarranty));
        is.read(reinterpret_cast<char*>(&warrantyDays), sizeof(warrantyDays));
    }
};

std::vector<std::unique_ptr<Product>> loadFromBinaryFile(const std::string& filename) {
    std::vector<std::unique_ptr<Product>> products;
    std::ifstream is(filename, std::ios::binary);
    if (!is) return products;
    size_t size;
    if (!is.read(reinterpret_cast<char*>(&size), sizeof(size))) return products;
    for (size_t i = 0; i < size; ++i) {
        ProductType type;
        is.read(reinterpret_cast<char*>(&type), sizeof(type));
        std::unique_ptr<Product> prod;
        if (type == ProductType::Toy) prod = std::make_unique<Toy>();
        else if (type == ProductType::Food) prod = std::make_unique<Food>();
        else if (type == ProductType::Tech) prod = std::make_unique<Tech>();
        prod->deserialize(is);
        products.push_back(std::move(prod));
    }
    return products;
}

void generateTextReport(const std::string& binFilename, const std::string& reportFilename) {
    auto products = loadFromBinaryFile(binFilename);
    std::ofstream report(reportFilename);

    if (!report.is_open()) {
        std::cout << "Помилка: не вдалося створити файл звіту!" << std::endl;
        return;
    }

    report << "=========================================================================================\n";
    report << "|                               ЗВІТ ПРО НАЯВНІ ТОВАРИ                                  |\n";
    report << "=========================================================================================\n";
    report << "| " << std::left << std::setw(15) << "Артикул"
        << "| " << std::setw(20) << "Назва товару"
        << "| " << std::setw(10) << "Ціна (грн)"
        << "| " << std::setw(8) << "Одиниця"
        << "| " << std::setw(22) << "Специфічна інформація" << "|\n";
    report << "-----------------------------------------------------------------------------------------\n";

    report << std::fixed << std::setprecision(2);
    for (const auto& prod : products) {
        report << "| " << std::left << std::setw(15) << prod->getArticle()
            << "| " << std::setw(20) << prod->getName()
            << "| " << std::setw(10) << prod->getPrice()
            << "| " << std::setw(8) << prod->getUnit()
            << "| " << std::setw(22) << prod->getSpecificInfo() << "|\n";
    }
    report << "=========================================================================================\n";

    report.close();
    std::cout << "Текстовий звіт успішно збережено у файл: " << reportFilename << std::endl;
}

int main() {
    setupLocale();
    std::string dbFile = "products.dat";
    std::string reportFile = "report.txt";

    std::cout << "=== ПУНКТ Д: ГЕНЕРАЦІЯ ТЕКСТОВОГО ЗВІТУ З БІНАРНОГО ФАЙЛУ ===" << std::endl;
    generateTextReport(dbFile, reportFile);

    return 0;
}