#include "stdafx.h"
#include "Knapsack.h"

Knapsack::Knapsack()
{
}

Knapsack::Knapsack(int capacity)
{
	this->capacity = capacity;
}


Knapsack::~Knapsack()
{
	this->items.clear();
	this->items.shrink_to_fit();
}

bool Knapsack::inputFromFile(std::string filename)
{
	items.clear();
	int tempSize, tempWeight;
	std::ifstream plik(filename, std::ios::in);
	if (plik) {
		plik >> this->allItems;
		for (int i = 0; i < this->allItems; i++)
		{
			
			plik >> tempSize;
			plik >> tempWeight;
			items.push_back(*new Item(tempSize, tempWeight));
		}
		std::cout << "Wczytano dane z pliku..." << std::endl;
		return true;
	}
	else {
		std::cout << "Blad wczytywania danych z pliku..." << std::endl;
		return false;
	}
	
}

bool Knapsack::bruteForce(bool showResults) {
	/*
	Funkcja dokonuj¹ca przegl¹du zupe³nego dla rozwi¹zania problemu plecakowego
	*/

	int sumSize = 0;
	int sumVal = 0;
	int finSum = 0;
	int finVal = 0;
	std::vector<Item> tempSolution; //Wektor przechowuj¹cy badane rozwi¹zanie
	std::vector<Item> finSolution; //Wektor przechowuj¹cy gotowe rozwi¹zanie
	int setSize = items.size(); // iloœc przedmiotów, które mo¿emy w³o¿yæ do plecaka

	if (setSize > 64) {
		std::cout << "\nZbyt duza liczba elementow, ilosc elemetow musi byc mniejsza niz 65\n";
		return false;
	}
	int size = items.size();
	unsigned long long int setCntr = (1ULL << size); // Poniewa¿ dokonujemy przegl¹du zupe³nego, musimy zbadaæ wszystkie podzbiory na wejœcu
													 // Których jest 2^n, 
	for (unsigned long long int i = 0; i < setCntr; i++) {
		//G³ówna pêtla sprawdzaj¹ca wszystkie mo¿liwoœci
		unsigned long long int currSet = i;

		sumSize = 0;
		sumVal = 0;
		tempSolution.clear();
		bool nothintToPut = false;
		for (int k = 0; k < setSize; k++) {
			if (((currSet >> k) & 1) != 1) continue;

			sumSize += items[k].getWeight();
			sumVal += items[k].getValue();
			tempSolution.push_back(items[k]);

			if (sumSize > capacity) {
				nothintToPut = true;
				break;
			}

		}
		if (nothintToPut)
			continue;

		if (sumSize <= capacity && sumVal > finVal) {
			finVal = sumVal;
			finSum = sumSize;
			finSolution = tempSolution;
		}
	}

	if (showResults) {
		std::cout << "\nWYNIK:" << std::endl;
		for (int i = 0; i < finSolution.size(); i++) {
			std::cout << finSolution[i] << std::endl;
		}
		std::cout << "\nRozmiar: " << finSum;
		std::cout << "\nWartosc: " << finVal << "\n";
	}
	return true;
}

float Knapsack::bound(Node u, int n, int W)
{
	if (u.weight >= W)
		return 0;
	int profit_bound = u.profit;
	int j = u.level + 1;
	int totweight = u.weight;

	while ((j < n) && (totweight + items[j].getWeight()  <= W))
	{
		totweight += items[j].getWeight();
		profit_bound += items[j].getValue();
		j++;
	}
	if (j < n)
		profit_bound += (W - totweight) * items[j].getValue() / items[j].getWeight();

	return profit_bound;
}

int Knapsack::BNB(bool showResults)
{
	sortItemsByRatio();
	std::queue<Node> Q;
	Node v;

	Node u = Node(-1, 0, 0);

	Q.push(u);
	std::vector<Item> taken = std::vector<Item>();
	int maxProfit = 0;
	while (!Q.empty())
	{
		u = Q.front();
		Q.pop();

		if (u.level == -1)
			v.level = 0;

		if (u.level == items.size() - 1)
			continue;
		Node with = Node(u.level + 1, u.profit + items[u.level + 1].getValue(), u.weight + items[u.level + 1].getWeight());
		with.items = u.items;
		with.items.push_back(items[with.level]);
		
		if (with.weight <= capacity && with.profit > maxProfit) {
			taken = with.items;
			maxProfit = with.profit;
		}

		with.bound = bound(with, items.size(), capacity);

		if (with.bound > maxProfit) {
			Q.push(with);
		}

		Node without = Node(u.level + 1, u.profit, u.weight);
		without.items = u.items;

		without.bound = bound(without, items.size(), capacity);
		if (without.bound > maxProfit) {
			Q.push(without);
		}

		u.items.clear();
		u.items.shrink_to_fit();
		without.items.clear();
		with.items.clear();
		without.items.shrink_to_fit();
		with.items.shrink_to_fit();
	}
	
	if (showResults) {
		std::cout << "Wybrane przedmioty: \n";
		int totalWeight = 0;
		int totalValue = 0;
		for (int i = 0; i < taken.size(); i++)
		{
			std::cout << taken[i] << std::endl;
			totalWeight += taken[i].getWeight();
			totalValue += taken[i].getValue();
		}
		std::cout << "Wartosc: " << totalValue << std::endl;
		std::cout << "Rozmiar: " << totalWeight << std::endl;
	}
	taken.clear();
	taken.shrink_to_fit();
	return maxProfit;
}

int max(int a, int b) { return (a > b) ? a : b; }

bool Knapsack::DP(bool showResults)
{
	int itemsCnt = items.size();
	sortItemsByWeight();

	int **dp = new int*[itemsCnt + 1];
	for (int i = 0; i < itemsCnt + 1; i++)
	{
		dp[i] = new int[capacity + 1];
	}

	for (int i = 0; i <= itemsCnt; i++)
	{
		for (int k = 0; k <= capacity; k++)
		{
			if (i == 0 || k == 0)
				dp[i][k] = 0;
			else if (items[i - 1].getWeight() <= k)
				dp[i][k] = max(items[i - 1].getValue() + dp[i - 1][k - items[i - 1].getWeight()], dp[i - 1][k]);
			else
				dp[i][k] = dp[i - 1][k];
		}
	}

	if (showResults) {
		std::vector<Item> solution;
		int cntr = capacity;
		for (int i = itemsCnt; i > 0; i--)
		{
			if (dp[i][cntr] == 0)
				break;
			if (dp[i][cntr] == dp[i - 1][cntr])
				continue;
			solution.push_back(items[i - 1]);
			cntr -= items[i - 1].getWeight();
		}

		std::cout << "Wybrane przedmioty: " << std::endl;
		for (int i = 0; i < solution.size(); i++)
		{
			std::cout << solution[i] << std::endl;
		}

		std::cout << "Wartosc plecaka: " << dp[itemsCnt][capacity] << std::endl;

		solution.clear();
		solution.shrink_to_fit();
	}

	for (int i = 0; i < itemsCnt; i++)
	{
		delete dp[i];
	}
	delete dp;
	return false;
}

bool compRatio(Item a, Item b)
{
	return a.getRatio() > b.getRatio();
}

bool compWeight(Item a, Item b) {
	return a.getWeight() < b.getWeight();
}


void Knapsack::sortItemsByRatio()
{
	std::sort(this->items.begin(), this->items.end(), compRatio);
}

void Knapsack::sortItemsByWeight()
{
	std::sort(this->items.begin(), this->items.end(), compWeight);
}



void Knapsack::printItems()
{
	Item* temp;
	std::cout << "Ilosc przedmiotow: " << this->items.size() << std::endl;
	for (int i = 0; i < this->items.size(); i++)
	{
		std::cout << items[i] << std::endl;
	}
}

void Knapsack::setCapacity(int capacity)
{
	this->capacity = capacity;
}

int Knapsack::getCapacity()
{
	return this->capacity;
}

int Knapsack::setItems(std::vector<Item> items)
{
	/*
	if (this->items.size() != 0) {
		items.clear();
		items.shrink_to_fit();
	}*/
	this->items = std::vector<Item>(items);
	return 0;
}
