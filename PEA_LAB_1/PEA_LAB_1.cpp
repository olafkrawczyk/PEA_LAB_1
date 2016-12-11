// PEA_LAB_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "Knapsack.h"
#include "PEA_LAB_1.h"

using namespace std;

void header() {
	std::cout << "PEA LAB 1 - Knapsack B&B | Olaf Krawczyk 218126 | 10.12.2016 \n" <<
			     "----------------------------------------------------------------\n";
}
char menu_glowne() {
	system("cls");
	header();
	std::cout << "1. Wczytaj dane z pliku\n2. B&B\n3. Brute Force\n4. Wypisz przedmioty\n5. Zmien pojemnosc plecaka\n6. Koniec\n";
	std::cout << "Wybor: ";
	return 'z';
}
void wczytaj_dane(Knapsack * knap) {
	string filename = "";
	int capacity;
	cout << "Podaj nazwe pliku: ";
	std::cin >> filename;
	cout << "Podaj rozmiar plecaka: ";
	cin >> capacity;
	knap->setCapacity(capacity);

	if (knap->inputFromFile(filename)) {
		knap->sortItemsByRatio();
		std::cout << "Wczytane przedmioty: \n";
		knap->printItems();
	}
}

void run_bnb(Knapsack * plecak) {
	system("cls");
	header();
	std::cout << "Uruchomiono Branch and Bound \n";
	plecak->BNB();
}
void run_bruteforce(Knapsack * plecak) {
	system("cls");
	header();
	std::cout << "Uruchomiono Brute Force \n";
	plecak->bruteForce();
}
void wypisz_plecak(Knapsack * plecak) {
	system("cls");
	header();
	std::cout << "Dostepne przedmioty: \n";
	plecak->printItems();
}
void zmien_rozmiar(Knapsack * plecak) {
	int new_size;
	system("cls");
	header();
	std::cout << "Nowy rozmiar: \n";
	cin >> new_size;
	plecak->setCapacity(new_size);
}

int main()
{	
	Knapsack *plecak = new Knapsack(10);
	

	char k = 'z';

	while (k != '6')
	{
		switch (k)
		{
		case '1':
			wczytaj_dane(plecak);
			system("pause");
			k = 'z';
			break;
		case '2':
			run_bnb(plecak);
			system("pause");
			k = 'z';
			break;
		case '3':
			run_bruteforce(plecak);
			system("pause");
			k = 'z';
			break;
		case '4':
			wypisz_plecak(plecak);
			system("pause");
			k = 'z';
			break;
		case '5':
			zmien_rozmiar(plecak);
			system("pause");
			k = 'z';
			break;
		default:
			menu_glowne();
			k = getchar();
			break;
		}
	}
	system("pause");
    return 0;
}

