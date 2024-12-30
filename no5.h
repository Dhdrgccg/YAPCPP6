#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <sstream>
#include <numeric> // Для std::accumulate


// Класс для реализации функционала словаря
template <typename K, typename V>
class Dictionary {
private:
    std::map<K, V> data; // Хранилище для ключей и значений

public:
    // Метод добавления элемента
    void add(const K& key, const V& value) {
        if (data.find(key) == data.end()) {
            data[key] = value;
        }
        else {
            std::cerr << "Ошибка: ключ \"" << key << "\" уже существует!" << std::endl;
        }
    }

    // Метод удаления элемента
    void remove(const K& key) {
        if (data.find(key) != data.end()) {
            data.erase(key);
        }
        else {
            std::cerr << "Ошибка: ключ \"" << key << "\" не найден!" << std::endl;
        }
    }

    // Получение значения по ключу
    V get(const K& key) const {
        auto it = data.find(key);
        if (it != data.end()) {
            return it->second;
        }
        else {
            throw std::runtime_error("Ключ не найден!");
        }
    }

    // Получение всех ключей и значений
    const std::map<K, V>& getAll() const {
        return data;
    }
};

// Функция для вычисления суммы баллов
int calculateTotalPoints(const std::vector<int>& scores) {
    return std::accumulate(scores.begin(), scores.end(), 0);
}

// Функция для чтения данных из файла
void readDataFromFile(const std::string& filename, Dictionary<std::string, std::vector<int>>& dict) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        return;
    }

    int n; // Количество участников
    inFile >> n;
    inFile.ignore(); // Пропускаем символ новой строки после числа

    std::string line;
    while (std::getline(inFile, line)) {
        std::istringstream iss(line);
        std::string surname, name;
        int score1, score2, score3, score4;

        iss >> surname >> name >> score1 >> score2 >> score3 >> score4;

        std::string fullName = surname + " " + name;
        std::vector<int> scores = { score1, score2, score3, score4 };

        dict.add(fullName, scores);
    }

    inFile.close();
}

// Функция для нахождения лучших участников
void findTopParticipants(const Dictionary<std::string, std::vector<int>>& dict, int topN) {
    const auto& data = dict.getAll();
    std::vector<std::pair<std::string, int>> results;

    // Вычисляем суммы баллов для каждого участника
    for (const auto& entry : data) {
        int totalPoints = calculateTotalPoints(entry.second);
        results.emplace_back(entry.first, totalPoints);
    }

    // Сортируем по убыванию суммы баллов
    std::sort(results.begin(), results.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
        });

    // Определяем минимальный балл, который попадает в топ
    int threshold = results.size() > topN ? results[topN - 1].second : results.back().second;

    // Вывод участников, которые набрали баллы больше или равные threshold
    std::cout << "Топ участников:" << std::endl;
    for (const auto& entry : results) {
        if (entry.second >= threshold) {
            std::cout << entry.first << " с суммой баллов: " << entry.second << std::endl;
        }
    }
}

int no5() {
    std::setlocale(LC_ALL, ""); // Устанавливаем локаль для работы с русским текстом

    const std::string filename = "results.txt";

    // Создаем экземпляр словаря
    Dictionary<std::string, std::vector<int>> participants;

    // Чтение данных из файла
    readDataFromFile(filename, participants);

    // Нахождение лучших участников
    findTopParticipants(participants, 3);

    return 0;
}
