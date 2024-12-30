#pragma once
#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
#include <cstdlib>

// ����� ��� ���������������� ������ � ����������� ����������
class UniqueSet {
private:
    std::unordered_set<std::string> elements; // ��������� ���������� ���������

public:
    // ����� ��� ���������� �������� (������������� �� �����������)
    void add(const std::string& value) {
        elements.insert(value);
    }

    // ����� ��� �������� ��������
    void remove(const std::string& value) {
        elements.erase(value);
    }

    // ����� ��� ����������� ���� ���������
    UniqueSet Union(const UniqueSet& other) const {
        UniqueSet result = *this;
        for (const auto& elem : other.elements) {
            result.elements.insert(elem);
        }
        return result;
    }

    // ����� ��� ���������� ��������� ������ ���������
    UniqueSet Except(const UniqueSet& other) const {
        UniqueSet result = *this;
        for (const auto& elem : other.elements) {
            result.elements.erase(elem);
        }
        return result;
    }

    // ����� ��� ��������� ����������� ���� ���������
    UniqueSet Intersect(const UniqueSet& other) const {
        UniqueSet result;
        for (const auto& elem : elements) {
            if (other.elements.find(elem) != other.elements.end()) {
                result.elements.insert(elem);
            }
        }
        return result;
    }

    // ����� ��� �������� ������� ��������
    bool Contains(const std::string& value) const {
        return elements.find(value) != elements.end();
    }

    // ����� ��� ��������� ���� ���������
    std::vector<std::string> getAllElements() const {
        return std::vector<std::string>(elements.begin(), elements.end());
    }

    // ����� ����������� ���������
    void print() const {
        for (const auto& elem : elements) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
};

// ������� ������
int no3() {
    std::setlocale(LC_ALL, "Russian");
    std::wcout.imbue(std::locale("ru_RU.UTF-8"));

    int numDishes, numVisitors;

    // ���� ���� � ����
    std::cout << "������� ���������� ���� � ����: ";
    std::cin >> numDishes;
    UniqueSet dishes;
    std::cout << "������� �������� ����: ";
    for (int i = 0; i < numDishes; ++i) {
        std::string dish;
        std::cin >> dish;
        dishes.add(dish);
    }

    // ���� ������� �����������
    std::cout << "������� ���������� �����������: ";
    std::cin >> numVisitors;

    std::vector<UniqueSet> visitorsOrders(numVisitors);
    for (int i = 0; i < numVisitors; ++i) {
        int numOrders;
        std::cout << "������� ���������� ����, ���������� ����������� " << i + 1 << ": ";
        std::cin >> numOrders;
        std::cout << "������� �������� ���������� ����: ";
        for (int j = 0; j < numOrders; ++j) {
            std::string dish;
            std::cin >> dish;
            visitorsOrders[i].add(dish);
        }
    }

    // ���������� �����, ������� ���������� ��� ����������
    UniqueSet allOrdered = visitorsOrders[0];
    for (int i = 1; i < numVisitors; ++i) {
        allOrdered = allOrdered.Intersect(visitorsOrders[i]);
    }

    // ���������� �����, ������� ���������� ���� �� ��������� ����������
    UniqueSet someOrdered = visitorsOrders[0];
    for (int i = 1; i < numVisitors; ++i) {
        someOrdered = someOrdered.Union(visitorsOrders[i]);
    }

    // ���������� �����, ������� �� ��������� �����
    UniqueSet notOrdered = dishes.Except(someOrdered);

    // ����� �����������
    std::cout << "�����, ������� ���������� ��� ����������: ";
    allOrdered.print();

    std::cout << "�����, ������� ���������� ���� �� ��������� ����������: ";
    someOrdered.print();

    std::cout << "�����, ������� �� ��������� �����: ";
    notOrdered.print();

    return 0;
}
