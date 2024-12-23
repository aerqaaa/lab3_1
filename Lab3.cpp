#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <unordered_map>
#include <locale>

using namespace std;

const int SIZE = 15;

double F(double x, double a, double b, double c) {
    if (x < 0 && b != 0) {
        return a * x * x + b;
    }
    else if (x > 0 && b == 0) {
        return (x - a) / (x - c);
    }
    else {
        return x / c;
    }
}

// Функция для вывода числа с удалением лишних нулей
void printNumber(double num) {
    cout << fixed << setprecision(10) << num; // Устанавливаем высокую точность для округления
    cout << std::showpoint; // Показываем десятичную точку
    cout << std::defaultfloat; // Возвращаем к стандартному формату
}

int main() {
    // Установка setlocale для поддержки русского языка
    setlocale(LC_ALL, "ru_RU.UTF-8");

    double x1, x2, a, b, c;
    cin >> x1 >> x2 >> a >> b >> c;

    double arr1[SIZE], arr2[SIZE];

    // Заполнение массивов
    for (int i = 0; i < SIZE; ++i) {
        double step1 = (x2 - x1) / (SIZE - 1);
        double step2 = (x1 + x2) / (SIZE - 1);
        arr1[i] = F(x1 + i * step1, a, b, c);
        arr2[i] = F(-x2 + i * step2, a, b, c);
    }

    // Вывод заполненных массивов
    for (int i = 0; i < SIZE; ++i) {
        printNumber(arr1[i]);
        if (i < SIZE - 1) cout << " ";
    }
    cout << endl;

    for (int i = 0; i < SIZE; ++i) {
        printNumber(arr2[i]);
        if (i < SIZE - 1) cout << " ";
    }
    cout << endl;

    // Вычисление минимумов каждой группы из пяти элементов в arr1
    for (int i = 0; i < SIZE; i += 5) {
        double minVal = arr1[i];
        for (int j = 1; j < 5 && i + j < SIZE; ++j) {
            minVal = min(minVal, arr1[i + j]);
        }
        printNumber(minVal);
        cout << endl;
    }

    // Сортировка первого массива и вывод его
    sort(arr1, arr1 + SIZE);
    for (int i = 0; i < SIZE; ++i) {
        printNumber(arr1[i]);
        if (i < SIZE - 1) cout << " ";
    }
    cout << endl;

    // Подсчет дубликатов в arr1
    unordered_map<double, int> countMap;
    for (int i = 0; i < SIZE; ++i) {
        countMap[arr1[i]]++;
    }

    int duplicatesCount = 0;
    for (const auto& pair : countMap) {
        if (pair.second > 1) {
            duplicatesCount++;
        }
    }

    cout << duplicatesCount << endl;

    // Поиск первого индекса неотрицательных степеней двойки
    int powerOfTwoIndex = -1;

    for (int i = 0; i < SIZE; ++i) {
        if ((arr1[i] >= 0) && ((arr1[i] && (arr1[i] - 1)) == 0)) { // Проверка на степень двойки
            powerOfTwoIndex = i;
            break;
        }
    }

    cout << powerOfTwoIndex << endl;

    // Перераспределение массивов
    double newArr1[SIZE] = { 0 }, newArr2[SIZE] = { 0 };

    int index1 = 0, index2 = 0;

    for (int i = 0; i < SIZE; ++i) {
        if (arr1[i] < 0 && index1 < SIZE) {
            newArr1[index1++] = arr1[i];
        }

        if (arr2[i] > 0 && index2 < SIZE) {
            newArr2[index2++] = arr2[i];
        }
    }

    // Вывод перераспределенных массивов
    for (int i = 0; i < index1; ++i) {
        printNumber(newArr1[i]);
        if (i < index1 - 1) cout << " ";
    }

    cout << endl;

    for (int i = 0; i < index2; ++i) {
        printNumber(newArr2[i]);
        if (i < index2 - 1) cout << " ";
    }

    cout << endl;

    return 0;
}