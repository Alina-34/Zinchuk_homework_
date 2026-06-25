#define NOMINMAX
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
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
    double getPrice() const { return price; }
    void setPrice(double p) { price = p; }

    virtual int getDaysLeft() const { return 999; }

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

    virtual void print() const {
        std::cout << "Назва: " << name << " | Артикул: " << article
            << " | Ціна: " << price << " грн | Одиниця: " << unit;
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

    void serialize(std::ostream& os) const override {
        Product::serialize(os);
        os.write(reinterpret_cast<const char*>(&ageLimit), sizeof(ageLimit));
    }

    void deserialize(std::istream& is) override {
        Product::deserialize(is);
        is.read(reinterpret_cast<char*>(&ageLimit), sizeof(ageLimit));
    }

    void print() const override {
        Product::print();
        std::cout << " | [Іграшка] Вікове обмеження: " << ageLimit << "+" << std::endl;
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
    int getDaysLeft() const override { return expirationDays; }

    void serialize(std::ostream& os) const override {
        Product::serialize(os);
        os.write(reinterpret_cast<const char*>(&expirationDays), sizeof(expirationDays));
    }

    void deserialize(std::istream& is) override {
        Product::deserialize(is);
        is.read(reinterpret_cast<char*>(&expirationDays), sizeof(expirationDays));
    }

    void print() const override {
        Product::print();
        std::cout << " | [Їжа] Термін придатності: " << expirationDays << " днів" << std::endl;
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
    int getDaysLeft() const override { return hasWarranty ? warrantyDays : 999; }

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

    void print() const override {
        Product::print();
        std::cout << " | [Техніка] Гарантія: " << (hasWarranty ? std::to_string(warrantyDays) + " днів" : "немає") << std::endl;
    }
};

void saveToBinaryFile(const std::string& filename, const std::vector<std::unique_ptr<Product>>& products) {
    std::ofstream os(filename, std::ios::binary);
    if (!os) return;
    size_t size = products.size();
    os.write(reinterpret_cast<const char*>(&size), sizeof(size));
    for (const auto& prod : products) {
        ProductType type = prod->getType();
        os.write(reinterpret_cast<const char*>(&type), sizeof(type));
        prod->serialize(os);
    }
}

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

void searchProduct(const std::string& filename, const std::string& name, ProductType type) {
    auto products = loadFromBinaryFile(filename);
    bool found = false;
    for (const auto& prod : products) {
        if (prod->getName() == name && prod->getType() == type) {
            if (!found) {
                std::cout << "\nЗнайдено товар(и):" << std::endl;
                found = true;
            }
            prod->print();
        }
    }
    if (!found) std::cout << "\nТовар із такими параметрами не знайдено." << std::endl;
}

void processOrder(const std::string& filename, const std::vector<std::string>& orderNames) {
    auto products = loadFromBinaryFile(filename);
    double totalCost = 0.0;
    std::vector<std::unique_ptr<Product>> remainingProducts;

    for (auto& prod : products) {
        auto it = std::find(orderNames.begin(), orderNames.end(), prod->getName());
        if (it != orderNames.end()) {
            totalCost += prod->getPrice();
            std::cout << "Оформлено замовлення на: " << prod->getName() << " (" << prod->getPrice() << " грн)" << std::endl;
        }
        else {
            remainingProducts.push_back(std::move(prod));
        }
    }
    std::cout << "Загальна сума замовлення: " << totalCost << " грн" << std::endl;
    saveToBinaryFile(filename, remainingProducts);
}

void applyDiscount(const std::string& filename) {
    auto products = loadFromBinaryFile(filename);
    bool updated = false;
    for (auto& prod : products) {
        if (prod->getDaysLeft() < 5) {
            double oldPrice = prod->getPrice();
            prod->setPrice(oldPrice * 0.8);
            std::cout << "Знижено ціну на " << prod->getName() << ": " << oldPrice << " -> " << prod->getPrice() << " грн" << std::endl;
            updated = true;
        }
    }
    if (updated) {
        saveToBinaryFile(filename, products);
    }
    else {
        std::cout << "Товарів, що підпадають під знижку (< 5 днів дії), не знайдено." << std::endl;
    }
}

int main() {
    setupLocale();
    std::string dbFile = "products.dat";

    std::vector<std::unique_ptr<Product>> initialProducts;
    initialProducts.push_back(std::make_unique<Toy>("Ведмедик", "T01", "шт", 250.0, Date{ 10, 5, 2026 }, 3));
    initialProducts.push_back(std::make_unique<Food>("Молоко", "F02", "л", 45.0, Date{ 22, 6, 2026 }, 3));
    initialProducts.push_back(std::make_unique<Tech>("Ноутбук", "H03", "шт", 32000.0, Date{ 1, 1, 2026 }, true, 730));
    initialProducts.push_back(std::make_unique<Tech>("Мишка", "H04", "шт", 600.0, Date{ 12, 3, 2026 }, true, 4));

    saveToBinaryFile(dbFile, initialProducts);
    std::cout << "--- Початковий каталог створено та збережено в бінарний файл ---" << std::endl;

    std::cout << "\n=== ПУНКТ 1: ПОШУК ТОВАРУ ===" << std::endl;
    searchProduct(dbFile, "Молоко", ProductType::Food);

    std::cout << "\n=== ПУНКТ 3: ЗНИЖЕННЯ ВАРТОСТІ НА 20% (якщо залишилось < 5 днів) ===" << std::endl;
    applyDiscount(dbFile);

    std::cout << "\n=== ПУНКТ 2: ОФОРМЛЕННЯ ЗАМОВЛЕННЯ ТА ВИДАЛЕННЯ З ФАЙЛУ ===" << std::endl;
    std::vector<std::string> order = { "Ведмедик", "Мишка" };
    processOrder(dbFile, order);

    std::cout << "\n=== СТАН КАТАЛОГУ ПІСЛЯ ЗАМОВЛЕННЯ ===" << std::endl;
    auto finalProducts = loadFromBinaryFile(dbFile);
    for (const auto& prod : finalProducts) {
        prod->print();
    }

    return 0;
}