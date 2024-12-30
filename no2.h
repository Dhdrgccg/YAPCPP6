#pragma once
#include <iostream>
#include <cstdlib>

// ����� ���� ���������������� ������
class DoublyNode {
public:
    int data;             // ������ ����
    DoublyNode* prev;      // ��������� �� ���������� ����
    DoublyNode* next;      // ��������� �� ��������� ����

    DoublyNode(int value) : data(value), prev(nullptr), next(nullptr) {}
};

// ����� ���������������� ������
class DoublyLinkedList {
private:
    DoublyNode* head;      // ��������� �� ������ ������
    DoublyNode* tail;      // ��������� �� ����� ������

public:
    // �����������
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // ����� ��� ���������� �������� � ����� ������
    void append(int value) {
        DoublyNode* newNode = new DoublyNode(value);
        if (!head) { // ���� ������ ����
            head = tail = newNode;
            head->next = head->prev = head; // ������ ���������� ��� �� ����
        }
        else {
            newNode->prev = tail;
            newNode->next = head; // ����� ���� ��������� �� ������
            tail->next = newNode;
            head->prev = newNode;
            tail = newNode; // ����� ���� ���������� �������
        }
    }

    // ����� ��� �������� �������� �� ��������
    void remove(int value) {
        if (!head) return; // ���� ������ ����

        DoublyNode* current = head;

        // ����� ������
        do {
            if (current->data == value) { // ���� ����� �������
                if (current == head && current == tail) {
                    // ������ �������� ������ ���� �������
                    delete current;
                    head = tail = nullptr;
                    return;
                }

                // ������� ������
                if (current == head) {
                    head = head->next;
                    head->prev = tail;
                    tail->next = head;
                }
                // ������� �����
                else if (current == tail) {
                    tail = tail->prev;
                    tail->next = head;
                    head->prev = tail;
                }
                // ������� ������� �� ��������
                else {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                }

                delete current;
                return;
            }
            current = current->next;
        } while (current != head);
    }

    // ����� ��� �������� ������� ��������, ������� ���������� �� ��� (�� �����)
    int countEqualNeighbors() {
        if (!head) return 0; // ���� ������ ����

        int count = 0;
        DoublyNode* current = head;

        do {
            if (current->data == current->next->data) {
                ++count; // ����������� �������, ���� ������� ����� ����������
            }
            current = current->next;
        } while (current != head);

        return count;
    }

    // ����� ��� ������ ������
    void print() const {
        if (!head) {
            std::cout << "������ ����." << std::endl;
            return;
        }

        DoublyNode* current = head;
        do {
            std::cout << current->data << " ";
            current = current->next;
        } while (current != head);
        std::cout << std::endl;
    }

    // ���������� ��� ������� ������
    ~DoublyLinkedList() {
        if (!head) return;

        DoublyNode* current = head;
        do {
            DoublyNode* temp = current;
            current = current->next;
            delete temp;
        } while (current != head);

        head = tail = nullptr;
    }
};

int no2() {
    std::setlocale(LC_ALL, "Russian");
    std::wcout.imbue(std::locale("ru_RU.UTF-8"));

    DoublyLinkedList L;
    int n, value;

    // ���� ��������� ������ � ����������
    std::cout << "������� ���������� ��������� ������ L: ";
    std::cin >> n;
    std::cout << "������� �������� ������ L: ";
    for (int i = 0; i < n; ++i) {
        std::cin >> value;
        L.append(value);
    }

    // ����� ��������� ������
    std::cout << "������ L: ";
    L.print();

    // ������� ������ �������� ���������
    int equalCount = L.countEqualNeighbors();
    std::cout << "���������� ���������, ������ ��������� �� ���� (�� �����): " << equalCount << std::endl;

    return 0;
}
