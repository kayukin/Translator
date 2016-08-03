#include "RuEngDictionary.h"
#include <iostream>
#include <string>
#include <Windows.h>

int main()
{
	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	RuEngDictionary dict("dict.dat");
	while (true)
	{
		std::string str;
		std::getline(std::cin, str);
		std::string match = dict.find_rus(str);
		std::cout << match << std::endl;
		std::string translation = dict.translate_to_eng(match);
		std::cout << translation << std::endl;
	}
	return 0;
}