#pragma once
#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
#include <cstdlib>

// Класс для неупорядоченного списка с уникальными элементами
class UniqueSet {
private:
    std::unordered_set<std::string> elements; // Хранилище уникальных элементов

public:
    // Метод для добавления элемента (повторяющийся не добавляется)
    void add(const std::string& value) {
        elements.insert(value);
    }

    // Метод для удаления элемента
    void remove(const std::string& value) {
        elements.erase(value);
    }

    // Метод для объединения двух коллекций
    UniqueSet Union(const UniqueSet& other) const {
        UniqueSet result = *this;
        for (const auto& elem : other.elements) {
            result.elements.insert(elem);
        }
        return result;
    }

    // Метод для исключения элементов другой коллекции
    UniqueSet Except(const UniqueSet& other) const {
        UniqueSet result = *this;
        for (const auto& elem : other.elements) {
            result.elements.erase(elem);
        }
        return result;
    }

    // Метод для получения пересечения двух коллекций
    UniqueSet Intersect(const UniqueSet& other) const {
        UniqueSet result;
        for (const auto& elem : elements) {
            if (other.elements.find(elem) != other.elements.end()) {
                result.elements.insert(elem);
            }
        }
        return result;
    }

    // Метод для проверки наличия элемента
    bool Contains(const std::string& value) const {
        return elements.find(value) != elements.end();
    }

    // Метод для получения всех элементов
    std::vector<std::string> getAllElements() const {
        return std::vector<std::string>(elements.begin(), elements.end());
    }

    // Вывод содержимого коллекции
    void print() const {
        for (const auto& elem : elements) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
};

// Решение задачи
int no3() {
    std::setlocale(LC_ALL, "Russian");
    std::wcout.imbue(std::locale("ru_RU.UTF-8"));

    int numDishes, numVisitors;

    // Ввод блюд в кафе
    std::cout << "Введите количество блюд в меню: ";
    std::cin >> numDishes;
    UniqueSet dishes;
    std::cout << "Введите названия блюд: ";
    for (int i = 0; i < numDishes; ++i) {
        std::string dish;
        std::cin >> dish;
        dishes.add(dish);
    }

    // Ввод заказов посетителей
    std::cout << "Введите количество посетителей: ";
    std::cin >> numVisitors;

    std::vector<UniqueSet> visitorsOrders(numVisitors);
    for (int i = 0; i < numVisitors; ++i) {
        int numOrders;
        std::cout << "Введите количество блюд, заказанных посетителем " << i + 1 << ": ";
        std::cin >> numOrders;
        std::cout << "Введите названия заказанных блюд: ";
        for (int j = 0; j < numOrders; ++j) {
            std::string dish;
            std::cin >> dish;
            visitorsOrders[i].add(dish);
        }
    }

    // Определяем блюда, которые заказывали все посетители
    UniqueSet allOrdered = visitorsOrders[0];
    for (int i = 1; i < numVisitors; ++i) {
        allOrdered = allOrdered.Intersect(visitorsOrders[i]);
    }

    // Определяем блюда, которые заказывали хотя бы некоторые посетители
    UniqueSet someOrdered = visitorsOrders[0];
    for (int i = 1; i < numVisitors; ++i) {
        someOrdered = someOrdered.Union(visitorsOrders[i]);
    }

    // Определяем блюда, которые не заказывал никто
    UniqueSet notOrdered = dishes.Except(someOrdered);

    // Вывод результатов
    std::cout << "Блюда, которые заказывали все посетители: ";
    allOrdered.print();

    std::cout << "Блюда, которые заказывали хотя бы некоторые посетители: ";
    someOrdered.print();

    std::cout << "Блюда, которые не заказывал никто: ";
    notOrdered.print();

    return 0;
}
