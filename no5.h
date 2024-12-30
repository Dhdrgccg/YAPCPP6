#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <sstream>
#include <numeric> // ��� std::accumulate


// ����� ��� ���������� ����������� �������
template <typename K, typename V>
class Dictionary {
private:
    std::map<K, V> data; // ��������� ��� ������ � ��������

public:
    // ����� ���������� ��������
    void add(const K& key, const V& value) {
        if (data.find(key) == data.end()) {
            data[key] = value;
        }
        else {
            std::cerr << "������: ���� \"" << key << "\" ��� ����������!" << std::endl;
        }
    }

    // ����� �������� ��������
    void remove(const K& key) {
        if (data.find(key) != data.end()) {
            data.erase(key);
        }
        else {
            std::cerr << "������: ���� \"" << key << "\" �� ������!" << std::endl;
        }
    }

    // ��������� �������� �� �����
    V get(const K& key) const {
        auto it = data.find(key);
        if (it != data.end()) {
            return it->second;
        }
        else {
            throw std::runtime_error("���� �� ������!");
        }
    }

    // ��������� ���� ������ � ��������
    const std::map<K, V>& getAll() const {
        return data;
    }
};

// ������� ��� ���������� ����� ������
int calculateTotalPoints(const std::vector<int>& scores) {
    return std::accumulate(scores.begin(), scores.end(), 0);
}

// ������� ��� ������ ������ �� �����
void readDataFromFile(const std::string& filename, Dictionary<std::string, std::vector<int>>& dict) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "������ �������� �����!" << std::endl;
        return;
    }

    int n; // ���������� ����������
    inFile >> n;
    inFile.ignore(); // ���������� ������ ����� ������ ����� �����

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

// ������� ��� ���������� ������ ����������
void findTopParticipants(const Dictionary<std::string, std::vector<int>>& dict, int topN) {
    const auto& data = dict.getAll();
    std::vector<std::pair<std::string, int>> results;

    // ��������� ����� ������ ��� ������� ���������
    for (const auto& entry : data) {
        int totalPoints = calculateTotalPoints(entry.second);
        results.emplace_back(entry.first, totalPoints);
    }

    // ��������� �� �������� ����� ������
    std::sort(results.begin(), results.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
        });

    // ���������� ����������� ����, ������� �������� � ���
    int threshold = results.size() > topN ? results[topN - 1].second : results.back().second;

    // ����� ����������, ������� ������� ����� ������ ��� ������ threshold
    std::cout << "��� ����������:" << std::endl;
    for (const auto& entry : results) {
        if (entry.second >= threshold) {
            std::cout << entry.first << " � ������ ������: " << entry.second << std::endl;
        }
    }
}

int no5() {
    std::setlocale(LC_ALL, ""); // ������������� ������ ��� ������ � ������� �������

    const std::string filename = "results.txt";

    // ������� ��������� �������
    Dictionary<std::string, std::vector<int>> participants;

    // ������ ������ �� �����
    readDataFromFile(filename, participants);

    // ���������� ������ ����������
    findTopParticipants(participants, 3);

    return 0;
}
