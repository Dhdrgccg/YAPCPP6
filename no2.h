#pragma once
#include <iostream>
#include <cstdlib>

// Класс узла двунаправленного списка
class DoublyNode {
public:
    int data;             // Данные узла
    DoublyNode* prev;      // Указатель на предыдущий узел
    DoublyNode* next;      // Указатель на следующий узел

    DoublyNode(int value) : data(value), prev(nullptr), next(nullptr) {}
};

// Класс двунаправленного списка
class DoublyLinkedList {
private:
    DoublyNode* head;      // Указатель на голову списка
    DoublyNode* tail;      // Указатель на хвост списка

public:
    // Конструктор
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // Метод для добавления элемента в конец списка
    void append(int value) {
        DoublyNode* newNode = new DoublyNode(value);
        if (!head) { // Если список пуст
            head = tail = newNode;
            head->next = head->prev = head; // Список замыкается сам на себя
        }
        else {
            newNode->prev = tail;
            newNode->next = head; // Новый узел указывает на голову
            tail->next = newNode;
            head->prev = newNode;
            tail = newNode; // Новый узел становится хвостом
        }
    }

    // Метод для удаления элемента по значению
    void remove(int value) {
        if (!head) return; // Если список пуст

        DoublyNode* current = head;

        // Обход списка
        do {
            if (current->data == value) { // Если нашли элемент
                if (current == head && current == tail) {
                    // Список содержит только один элемент
                    delete current;
                    head = tail = nullptr;
                    return;
                }

                // Удаляем голову
                if (current == head) {
                    head = head->next;
                    head->prev = tail;
                    tail->next = head;
                }
                // Удаляем хвост
                else if (current == tail) {
                    tail = tail->prev;
                    tail->next = head;
                    head->prev = tail;
                }
                // Удаляем элемент из середины
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

    // Метод для проверки наличия элемента, равного следующему за ним (по кругу)
    int countEqualNeighbors() {
        if (!head) return 0; // Если список пуст

        int count = 0;
        DoublyNode* current = head;

        do {
            if (current->data == current->next->data) {
                ++count; // Увеличиваем счетчик, если элемент равен следующему
            }
            current = current->next;
        } while (current != head);

        return count;
    }

    // Метод для вывода списка
    void print() const {
        if (!head) {
            std::cout << "Список пуст." << std::endl;
            return;
        }

        DoublyNode* current = head;
        do {
            std::cout << current->data << " ";
            current = current->next;
        } while (current != head);
        std::cout << std::endl;
    }

    // Деструктор для очистки памяти
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

    // Ввод элементов списка с клавиатуры
    std::cout << "Введите количество элементов списка L: ";
    std::cin >> n;
    std::cout << "Введите элементы списка L: ";
    for (int i = 0; i < n; ++i) {
        std::cin >> value;
        L.append(value);
    }

    // Вывод исходного списка
    std::cout << "Список L: ";
    L.print();

    // Подсчет равных соседних элементов
    int equalCount = L.countEqualNeighbors();
    std::cout << "Количество элементов, равных следующим за ними (по кругу): " << equalCount << std::endl;

    return 0;
}
