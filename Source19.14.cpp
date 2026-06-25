#define NOMINMAX
#include <iostream>
#include <cmath>
#include <functional>
#include <string>
#include <iomanip>
#include <windows.h>

void setupLocale() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
}

class Function {
private:
    std::function<double(double)> fx;
    double a;
    double b;

public:
    Function(double left, double right, std::function<double(double)> func)
        : a(left), b(right), fx(func) {
    }

    double evaluate(double x) const {
        return fx(x);
    }

    double integrateLeftRectangles(int n) const {
        double h = (b - a) / n;
        double sum = 0.0;
        for (int i = 0; i < n; ++i) {
            sum += fx(a + i * h);
        }
        return sum * h;
    }

    double integrateRightRectangles(int n) const {
        double h = (b - a) / n;
        double sum = 0.0;
        for (int i = 1; i <= n; ++i) {
            sum += fx(a + i * h);
        }
        return sum * h;
    }

    double integrateMiddleRectangles(int n) const {
        double h = (b - a) / n;
        double sum = 0.0;
        for (int i = 0; i < n; ++i) {
            sum += fx(a + (i + 0.5) * h);
        }
        return sum * h;
    }

    double integrateTrapezoids(int n) const {
        double h = (b - a) / n;
        double sum = 0.5 * (fx(a) + fx(b));
        for (int i = 1; i < n; ++i) {
            sum += fx(a + i * h);
        }
        return sum * h;
    }

    double integrateSimpsons(int n) const {
        if (n % 2 != 0) n++;
        double h = (b - a) / n;
        double sum = fx(a) + fx(b);

        for (int i = 1; i < n; ++i) {
            double x = a + i * h;
            if (i % 2 == 0) {
                sum += 2.0 * fx(x);
            }
            else {
                sum += 4.0 * fx(x);
            }
        }
        return sum * h / 3.0;
    }

    void sample(double start, double end, int sampleCount) const {
        if (sampleCount <= 1) return;
        double step = (end - start) / (sampleCount - 1);

        std::cout << "\n-------------------------" << std::endl;
        std::cout << "| " << std::setw(10) << "Точка x" << " | " << std::setw(10) << "Значення f(x)" << " |" << std::endl;
        std::cout << "-------------------------" << std::endl;

        for (int i = 0; i < sampleCount; ++i) {
            double x = start + i * step;
            std::cout << "| " << std::setw(10) << std::fixed << std::setprecision(4) << x
                << " | " << std::setw(13) << fx(x) << " |" << std::endl;
        }
        std::cout << "-------------------------" << std::endl;
    }
};

int main() {
    setupLocale();

    double a = 1.0;
    double b = 3.0;
    int intervals = 1000;

    auto complexFunc = [](double x) {
        return std::pow(x, 2) + std::cos(x) + std::sqrt(x) + std::log(x);
        };

    Function myFunc(a, b, complexFunc);

    std::cout << "=== ОБЧИСЛЕННЯ ІНТЕГРАЛА НА ІНТЕРВАЛІ [" << a << ", " << b << "] ===" << std::endl;
    std::cout << "Формула лівих прямокутників:  " << myFunc.integrateLeftRectangles(intervals) << std::endl;
    std::cout << "Формула правих прямокутників: " << myFunc.integrateRightRectangles(intervals) << std::endl;
    std::cout << "Формула середніх прямокутників:" << myFunc.integrateMiddleRectangles(intervals) << std::endl;
    std::cout << "Формула трапецій:             " << myFunc.integrateTrapezoids(intervals) << std::endl;
    std::cout << "Формула Сімпсона:             " << myFunc.integrateSimpsons(intervals) << std::endl;

    std::cout << "\n=== СЕМПЛЮВАННЯ ФУНКЦІЇ ===" << std::endl;
    myFunc.sample(1.0, 2.0, 6);

    return 0;
}