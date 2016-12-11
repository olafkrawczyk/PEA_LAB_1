// PEA_LAB_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "Knapsack.h"
#include "PEA_LAB_1.h"

using namespace std;
int main()
{	
	Knapsack *plecak = new Knapsack(10);
	string filename = "";
	int capacity;
	cout << "Podaj nazwe pliku: ";
	std::cin >> filename;
	cout << "Podaj rozmiar plecaka: ";
	cin >> capacity;
	plecak->setCapacity(capacity);
	if(plecak->inputFromFile(filename))
		plecak->sortItemsByRatio();
		plecak->printItems();
		std::cout << "Profit: " << plecak->BNB() << std::endl;
	system("pause");
    return 0;
}

