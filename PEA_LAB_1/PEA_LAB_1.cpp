// PEA_LAB_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "Knapsack.h"
#include "PEA_LAB_1.h"
#include <cstdlib>
#include <time.h>
#include <Windows.h>

using namespace std;

LARGE_INTEGER startTimer()											//funkcje mierzace czas
{
	LARGE_INTEGER start;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&start);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return start;
}

LARGE_INTEGER endTimer()
{
	LARGE_INTEGER stop;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&stop);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return stop;
}

void header() {
	std::cout << "PEA LAB 1 - Knapsack B&B | Olaf Krawczyk 218126 | 10.12.2016 \n" <<
		"----------------------------------------------------------------\n";
}
char menu_glowne() {
	system("cls");
	header();
	std::cout << "1. Wczytaj dane z pliku\n2. B&B\n3. Brute Force\n4. Dynamic Programming\n5. Wypisz przedmioty\n6. Zmien pojemnosc plecaka\n7. Koniec\n";
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
	plecak->BNB(true);
}
void run_bruteforce(Knapsack * plecak) {
	system("cls");
	header();
	std::cout << "Uruchomiono Brute Force \n";
	plecak->bruteForce(true);
}
void run_dp(Knapsack * plecak) {
	system("cls");
	header();
	std::cout << "Uruchomiono Programowanie dynamiczne \n";
	plecak->DP(true);
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

std::vector<Item> wygeneruj_problem(int n) {
	std::vector<Item> tmp = *new std::vector<Item>();
	for (int i = 0; i < n; i++)
	{
		tmp.push_back(*new Item(rand() % 900, rand() % 900));
	}
	return tmp;
}
void make_tests(Knapsack * plecak) {
	std::fstream plik;
	LARGE_INTEGER performanceCountStart, performanceCountEnd, freq;
	QueryPerformanceFrequency(&freq);
	double tm;
	int capacity = 900;
	int sizesCnt = 7;
	int sizes[] = {10, 50, 100, 200, 300, 400, 500};
	std::vector<Item> problem;
	double **wyniki = new double*[sizesCnt];
	for (int i = 0; i < sizesCnt; i++)
	{
		wyniki[i] = new double[2];
		wyniki[i][0] = 0;
		wyniki[i][1] = 0;
	}

	plecak->setCapacity(capacity);
	int tries = 100;
	for (int k = 0; k < sizesCnt; k++)
	{
		for (int j = 0; j < tries; j++)
		{
			problem = wygeneruj_problem(sizes[k]);
			plecak->setItems(problem);
			performanceCountStart = startTimer();
			plecak->DP(false);
			performanceCountEnd = endTimer();
			tm = (double)(performanceCountEnd.QuadPart - performanceCountStart.QuadPart);
			wyniki[k][1] += (tm / freq.QuadPart * 100) * 10;

			problem.clear();
			problem.shrink_to_fit();
		}
		wyniki[k][0] = sizes[k];
		wyniki[k][1] /= tries;
	}
	string nazwa_pliku = "results_dp";
	std::string out_name = nazwa_pliku + ".csv";
	plik.open(out_name, std::ios::out);

	
	plik << std::endl;


	for (int i = 0; i < sizesCnt; i++)
	{
		plik << sizes[i] << ";";
	}
	plik << "\n";
	for (int i = 0; i < sizesCnt; i++)
	{
		plik << wyniki[i][1] << ";";
	}
	plik.close();
}

int main()
{
	srand(time(NULL));
	Knapsack *plecak = new Knapsack(10);


	char k = 'z';
	while (k != '7')
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
			run_dp(plecak);
			system("pause");
			k = 'z';
			break;
		case '5':
			wypisz_plecak(plecak);
			system("pause");
			k = 'z';
			break;
		case '6':
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

	make_tests(plecak);
	system("pause");
	return 0;
}

