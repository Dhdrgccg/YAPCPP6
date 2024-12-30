#include <iostream>

// ����� ���� ������
class Node {
public:
    int data;       // ������ ����
    Node* next;     // ��������� �� ��������� ����

    Node(int value) : data(value), next(nullptr) {}
};

// ����� ����������������� ������
class SinglyLinkedList {
private:
    Node* head;  // ��������� �� ������ ������

public:
    // �����������
    SinglyLinkedList() : head(nullptr) {}

    // ����� ��� ���������� �������� � ������ (� ������������� �������)
    void add(int value) {
        Node* newNode = new Node(value);

        // ���� ������ ���� ��� ����� ������� ������ ������
        if (!head || value < head->data) {
            newNode->next = head;
            head = newNode;
            return;
        }

        // ���� ����� ��� �������
        Node* temp = head;
        while (temp->next && temp->next->data < value) {
            temp = temp->next;
        }

        // ��������� ����� ����
        newNode->next = temp->next;
        temp->next = newNode;
    }

    // ����� ��� �������� �������� �� ��������
    void remove(int value) {
        if (!head) return; // ������ ����

        // �������� ������
        if (head->data == value) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        // ����� ����, ��������������� ����������
        Node* temp = head;
        while (temp->next && temp->next->data != value) {
            temp = temp->next;
        }

        // ���� ������� ������, ������� ���
        if (temp->next) {
            Node* nodeToDelete = temp->next;
            temp->next = temp->next->next;
            delete nodeToDelete;
        }
    }

    // ����� ��� ������� �������� ������ � ������ (�� ������� ���������������)
    void merge(SinglyLinkedList& other) {
        Node* l1 = this->head;
        Node* l2 = other.head;

        // ��������� ���� ��� ���������� ������ ������
        Node dummy(0);
        Node* current = &dummy;

        // ������� ���� �������
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

        // ��������� ���������� ��������
        current->next = l1 ? l1 : l2;

        // ��������� ������ �������� ������
        this->head = dummy.next;

        // ������� ������ ������ (�� ��� ������� � ������)
        other.head = nullptr;
    }

    // ����� ��� ������ ������
    void print() const {
        Node* temp = head;
        while (temp) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }

    // ���������� ��� ������� ������
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
    // ������� ��� ������
    SinglyLinkedList L1;
    SinglyLinkedList L2;

    int n1, n2, value;

    // ��������� ������ L1 � ����������
    std::cout << "������� ���������� ��������� ��� ������ L1: ";
    std::cin >> n1;
    std::cout << "������� �������� ������ L1 (�� �����������): ";
    for (int i = 0; i < n1; ++i) {
        std::cin >> value;
        L1.add(value);
    }

    // ��������� ������ L2 � ����������
    std::cout << "������� ���������� ��������� ��� ������ L2: ";
    std::cin >> n2;
    std::cout << "������� �������� ������ L2 (�� �����������): ";
    for (int i = 0; i < n2; ++i) {
        std::cin >> value;
        L2.add(value);
    }

    // ������� �������� ������
    std::cout << "������ L1: ";
    L1.print();
    std::cout << "������ L2: ";
    L2.print();

    // ������� �������
    L1.merge(L2);

    // ������� �������������� ������
    std::cout << "����� ������� L2 � L1: ";
    L1.print();

    return 0;
}
