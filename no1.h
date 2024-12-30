#include <iostream>

// Класс узла списка
class Node {
public:
    int data;       // Данные узла
    Node* next;     // Указатель на следующий узел

    Node(int value) : data(value), next(nullptr) {}
};

// Класс однонаправленного списка
class SinglyLinkedList {
private:
    Node* head;  // Указатель на голову списка

public:
    // Конструктор
    SinglyLinkedList() : head(nullptr) {}

    // Метод для добавления элемента в список (в упорядоченном порядке)
    void add(int value) {
        Node* newNode = new Node(value);

        // Если список пуст или новый элемент меньше головы
        if (!head || value < head->data) {
            newNode->next = head;
            head = newNode;
            return;
        }

        // Ищем место для вставки
        Node* temp = head;
        while (temp->next && temp->next->data < value) {
            temp = temp->next;
        }

        // Вставляем новый узел
        newNode->next = temp->next;
        temp->next = newNode;
    }

    // Метод для удаления элемента по значению
    void remove(int value) {
        if (!head) return; // Список пуст

        // Удаление головы
        if (head->data == value) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        // Поиск узла, предшествующего удаляемому
        Node* temp = head;
        while (temp->next && temp->next->data != value) {
            temp = temp->next;
        }

        // Если элемент найден, удаляем его
        if (temp->next) {
            Node* nodeToDelete = temp->next;
            temp->next = temp->next->next;
            delete nodeToDelete;
        }
    }

    // Метод для слияния текущего списка с другим (не нарушая упорядоченности)
    void merge(SinglyLinkedList& other) {
        Node* l1 = this->head;
        Node* l2 = other.head;

        // Временный узел для построения нового списка
        Node dummy(0);
        Node* current = &dummy;

        // Слияние двух списков
        while (l1 && l2) {
            if (l1->data < l2->data) {
                current->next = l1;
                l1 = l1->next;
            }
            else {
                current->next = l2;
                l2 = l2->next;
            }
            current = current->next;
        }

        // Добавляем оставшиеся элементы
        current->next = l1 ? l1 : l2;

        // Обновляем голову текущего списка
        this->head = dummy.next;

        // Очищаем второй список (он уже включен в первый)
        other.head = nullptr;
    }

    // Метод для вывода списка
    void print() const {
        Node* temp = head;
        while (temp) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }

    // Деструктор для очистки памяти
    ~SinglyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int no1() {

    std::setlocale(LC_ALL, "Russian");
    std::wcout.imbue(std::locale("ru_RU.UTF-8"));
    // Создаем два списка
    SinglyLinkedList L1;
    SinglyLinkedList L2;

    int n1, n2, value;

    // Заполняем список L1 с клавиатуры
    std::cout << "Введите количество элементов для списка L1: ";
    std::cin >> n1;
    std::cout << "Введите элементы списка L1 (по возрастанию): ";
    for (int i = 0; i < n1; ++i) {
        std::cin >> value;
        L1.add(value);
    }

    // Заполняем список L2 с клавиатуры
    std::cout << "Введите количество элементов для списка L2: ";
    std::cin >> n2;
    std::cout << "Введите элементы списка L2 (по возрастанию): ";
    for (int i = 0; i < n2; ++i) {
        std::cin >> value;
        L2.add(value);
    }

    // Выводим исходные списки
    std::cout << "Список L1: ";
    L1.print();
    std::cout << "Список L2: ";
    L2.print();

    // Слияние списков
    L1.merge(L2);

    // Выводим результирующий список
    std::cout << "После слияния L2 в L1: ";
    L1.print();

    return 0;
}
