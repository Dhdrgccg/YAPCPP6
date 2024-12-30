#include <iostream>
#include <fstream>
#include <deque>
#include <iterator>
#include <string>
#include <locale>
#include <cstdlib>
#include <unordered_set>
#include <vector>
#include <cctype>
#include <algorithm>
#include "no1.h"
#include "no2.h"
#include "no3.h"
#include "no4.h"
#include "no5.h"
using namespace std;

int main()
{
	std::setlocale(LC_ALL, "Russian");
	std::wcout.imbue(std::locale("ru_RU.UTF-8"));

	int Choise;
	cout << "Введите номер задания:";
	while (!(std::cin >> Choise)) {
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		std::cout << "Ошибка. Повторите ввод: ";
	}
	if (Choise == 1) {
		no1();
	}
	else if (Choise == 2)
	{
		no2();
	}
	else if (Choise == 3)
	{
		no3();
	}
	else if (Choise == 4)
	{
		no4();
	}
	else if (Choise == 5)
	{
		no5();
	}
	else
	{
		std::cout << "Такого номера нет";
	}

	return 0;
}
