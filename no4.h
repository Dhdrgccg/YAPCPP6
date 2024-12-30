#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <algorithm>
#include <cctype>
#include <locale>
#include <vector>

class UnorderedList {
private:
    std::set<int> items;

public:
    void add(int item) {
        // Добавляет элемент в коллекцию, если его там нет
        items.insert(item);
    }

    void remove(int item) {
        // Удаляет элемент из коллекции, если он существует
        items.erase(item);
    }

    UnorderedList unionWith(const UnorderedList& other) const {
        // Объединяет текущую коллекцию с другой коллекцией
        UnorderedList result;
        result.items = items;
        result.items.insert(other.items.begin(), other.items.end());
        return result;
    }

    UnorderedList exceptWith(const UnorderedList& other) const {
        // Удаляет из текущей коллекции элементы другой коллекции
        UnorderedList result;
        result.items = items;
        for (const int& item : other.items) {
            result.items.erase(item);
        }
        return result;
    }

    UnorderedList intersectWith(const UnorderedList& other) const {
        // Возвращает коллекцию, содержащую общие элементы двух коллекций
        UnorderedList result;
        for (const int& item : items) {
            if (other.items.find(item) != other.items.end()) {
                result.items.insert(item);
            }
        }
        return result;
    }

    bool contains(int item) const {
        // Проверяет, содержится ли элемент в коллекции
        return items.find(item) != items.end();
    }

    void print() const {
        for (const int& item : items) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
};

void printUniqueConsonants(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл: " << filename << std::endl;
        return;
    }

    std::set<char> uniqueConsonants;
    std::set<char> multipleOccurrences;
    std::vector<std::string> words;

    std::string word;
    while (file >> word) {
        words.push_back(word);
    }
    file.close();

    std::set<char> consonants;
    char consonantArray[] = { 'б', 'в', 'г', 'д', 'ж', 'з', 'й', 'к', 'л', 'м', 'н', 'п', 'р', 'с', 'т', 'ф', 'х', 'ц', 'ч', 'ш', 'щ' };
    consonants.insert(std::begin(consonantArray), std::end(consonantArray));

    for (const auto& w : words) {
        std::set<char> wordConsonants;
        for (char ch : w) {
            ch = std::tolower(ch, std::locale());
            if (consonants.find(ch) != consonants.end()) {
                if (wordConsonants.find(ch) == wordConsonants.end()) {
                    if (uniqueConsonants.find(ch) != uniqueConsonants.end()) {
                        multipleOccurrences.insert(ch);
                    }
                    else {
                        uniqueConsonants.insert(ch);
                    }
                }
                wordConsonants.insert(ch);
            }
        }
    }

    for (const char& ch : multipleOccurrences) {
        uniqueConsonants.erase(ch);
    }

    std::vector<char> result(uniqueConsonants.begin(), uniqueConsonants.end());
    std::sort(result.begin(), result.end());

    std::cout << "Согласные, которые входят ровно в одно слово: ";
    for (const char& ch : result) {
        std::cout << ch << " ";
    }
    std::cout << std::endl;
}

int no4() {
    std::setlocale(LC_ALL, "Russian");
    std::wcout.imbue(std::locale("ru_RU.UTF-8"));
    // Пример использования класса
    UnorderedList collection1;
    UnorderedList collection2;

    collection1.add(1);
    collection1.add(2);
    collection1.add(3);

    collection2.add(3);
    collection2.add(4);
    collection2.add(5);

    // Пример анализа текста из файла
    std::string filename = "text.txt";
    printUniqueConsonants(filename);

    return 0;
}
