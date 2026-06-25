#define NOMINMAX
#include <iostream>
#include <vector>
#include <algorithm>
#include <windows.h>

void setupLocale() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
}

template <typename T>
class Array {
private:
    std::vector<T> data;

public:
    Array() = default;
    Array(const std::vector<T>& initData) : data(initData) {}

    size_t getSize() const { return data.size(); }
    void print() const {
        for (const auto& val : data) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    void bubbleSort() {
        bubbleSortStatic(data);
    }

    void shakerSort() {
        shakerSortStatic(data);
    }

    void selectionSort() {
        selectionSortStatic(data);
    }

    void insertionSort() {
        insertionSortStatic(data);
    }

    void hashSort() {
        hashSortStatic(data);
    }

    static void bubbleSortStatic(std::vector<T>& arr) {
        if (arr.empty()) return;
        size_t n = arr.size();
        for (size_t i = 0; i < n - 1; ++i) {
            for (size_t j = 0; j < n - i - 1; ++j) {
                if (arr[j] > arr[j + 1]) {
                    std::swap(arr[j], arr[j + 1]);
                }
            }
        }
    }

    static void shakerSortStatic(std::vector<T>& arr) {
        if (arr.empty()) return;
        size_t left = 0;
        size_t right = arr.size() - 1;
        bool swapped = true;

        while (left < right&& swapped) {
            swapped = false;
            for (size_t i = left; i < right; ++i) {
                if (arr[i] > arr[i + 1]) {
                    std::swap(arr[i], arr[i + 1]);
                    swapped = true;
                }
            }
            right--;

            for (size_t i = right; i > left; --i) {
                if (arr[i - 1] > arr[i]) {
                    std::swap(arr[i - 1], arr[i]);
                    swapped = true;
                }
            }
            left++;
        }
    }

    static void selectionSortStatic(std::vector<T>& arr) {
        if (arr.empty()) return;
        size_t n = arr.size();
        for (size_t i = 0; i < n - 1; ++i) {
            size_t minIdx = i;
            for (size_t j = i + 1; j < n; ++j) {
                if (arr[j] < arr[minIdx]) {
                    minIdx = j;
                }
            }
            if (minIdx != i) {
                std::swap(arr[i], arr[minIdx]);
            }
        }
    }

    static void insertionSortStatic(std::vector<T>& arr) {
        if (arr.empty()) return;
        size_t n = arr.size();
        for (size_t i = 1; i < n; ++i) {
            T key = arr[i];
            int j = static_cast<int>(i) - 1;
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }

    static void hashSortStatic(std::vector<T>& arr) {
        if (arr.empty()) return;

        T minVal = arr[0];
        T maxVal = arr[0];
        for (const auto& val : arr) {
            if (val < minVal) minVal = val;
            if (val > maxVal) maxVal = val;
        }

        if (minVal == maxVal) return;

        size_t bucketCount = arr.size();
        std::vector<std::vector<T>> buckets(bucketCount);

        double range = static_cast<double>(maxVal - minVal);

        for (const auto& val : arr) {
            double normalized = static_cast<double>(val - minVal) / range;
            size_t bucketIdx = static_cast<size_t>(normalized * (bucketCount - 1));
            buckets[bucketIdx].push_back(val);
        }

        size_t idx = 0;
        for (size_t i = 0; i < bucketCount; ++i) {
            insertionSortStatic(buckets[i]);
            for (const auto& val : buckets[i]) {
                arr[idx++] = val;
            }
        }
    }
};

int main() {
    setupLocale();

    std::vector<int> rawData = { 64, -34, 25, 12, 22, 11, 90, 0, -5 };

    std::cout << "=== ТЕСТУВАННЯ МЕТОДІВ ОБ'ЄКТА (INPLACE) ===" << std::endl;

    Array<int> arr1(rawData);
    std::cout << "Початковий масив 1: "; arr1.print();
    arr1.bubbleSort();
    std::cout << "а) Сортування бульбашкою: "; arr1.print();

    Array<int> arr2(rawData);
    arr2.shakerSort();
    std::cout << "б) Шейкер-сорування:      "; arr2.print();

    Array<int> arr3(rawData);
    arr3.selectionSort();
    std::cout << "в) Сортування вибором:    "; arr3.print();

    std::cout << "\n=== ТЕСТУВАННЯ СТАТИЧНИХ ШАБЛОННИХ МЕТОДІВ ===" << std::endl;

    std::vector<double> doubleData = { 4.4, -1.2, 0.15, 10.8, 3.14, -5.5 };
    std::cout << "Початковий масив дійсних чисел: ";
    for (double d : doubleData) std::cout << d << " ";
    std::cout << std::endl;

    Array<double>::insertionSortStatic(doubleData);
    std::cout << "г) Статична вставка (double):   ";
    for (double d : doubleData) std::cout << d << " ";
    std::cout << std::endl;

    std::vector<int> hashTestData = { 99, 15, 82, 44, 3, 61, 27 };
    Array<int>::hashSortStatic(hashTestData);
    std::cout << "д) Статичне хеш-сортування (int): ";
    for (int i : hashTestData) std::cout << i << " ";
    std::cout << std::endl;

    return 0;
}