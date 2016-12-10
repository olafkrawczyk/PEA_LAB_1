#include "stdafx.h"
#include "Knapsack.h"
#include "Solution.h"

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
}

bool Knapsack::inputFromFile(std::string filename)
{
	int tempSize, tempWeight;
	std::ifstream plik(filename, std::ios::in);
	if (plik) {
		plik >> this->allItems;
		for (int i = 0; i < this->allItems; i++)
		{
			plik >> tempSize;
			plik >> tempWeight;
			items.push_back(new Item(tempSize, tempWeight));
		}
		std::cout << "Wczytano dane z pliku..." << std::endl;
		return true;
	}
	else {
		std::cout << "Blad wczytywania danych z pliku..." << std::endl;
		return false;
	}
	
}

bool Knapsack::bruteForce() {
	/*
	Funkcja dokonuj¹ca przegl¹du zupe³nego dla rozwi¹zania problemu plecakowego
	*/

	int sumSize = 0;
	int sumVal = 0;
	int finSum = 0;
	int finVal = 0;
	std::vector<Item*> tempSolution; //Wektor przechowuj¹cy badane rozwi¹zanie
	std::vector<Item*> finSolution; //Wektor przechowuj¹cy gotowe rozwi¹zanie
	int setSize = items.size(); // iloœc przedmiotów, które mo¿emy w³o¿yæ do plecaka

	if (setSize > 64) {
		std::cout << "\nZbyt du¿a liczba elementów, iloœc elemetów musi byæ mniejsza ni¿ 65\n";
		return false;
	}
	int size = items.size();
	unsigned long long int setCntr = (1ULL << size); // Poniewa¿ dokonujemy przegl¹du zupe³nego, musimy zbadaæ wszystkie podzbiory na wejœcu
													 // Których jest 2^n, 
	std::cout << "Rozmiar itemkow: " << size << std::endl;
	std::cout << "Ilosc iteracji: " << setCntr << std::endl;

	for (unsigned long long int i = 0; i < setCntr; i++) {
		//G³ówna pêtla sprawdzaj¹ca wszystkie mo¿liwoœci
		unsigned long long int currSet = i;

		sumSize = 0;
		sumVal = 0;
		tempSolution.clear();
		bool nothintToPut = false;
		for (int k = 0; k < setSize; k++) {
			if (((currSet >> k) & 1) != 1) continue;

			sumSize += items[k]->getSize();
			sumVal += items[k]->getValue();
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

	std::cout << "\nWYNIK:" << std::endl;
	for (int i = 0; i < finSolution.size(); i++) {
		std::cout << *finSolution[i] << std::endl;
	}
	std::cout << "\nRozmiar: " << finSum;
	std::cout << "\nWartosc: " << finVal << "\n";

	return true;
}


struct SolCompare
{
	bool operator()( Solution *t1, Solution *t2) const
	{
		return t1->getValue() > t2->getValue();
	}
};

bool Knapsack::BNB()
{
	Solution *best = new Solution(*this);
	Solution *root = new Solution(*this);

	Solution *tmp;
	Solution *tmp2;

	root->calculateUpperBound();

	std::priority_queue<Solution, std::vector<Solution*>, SolCompare> *queue = new std::priority_queue<Solution, std::vector<Solution*>, SolCompare>();
	queue->push(root);
	
	while (!queue->empty()) {
		
		root = queue->top();
		queue->pop();
		tmp = new Solution(*this, *root);

		tmp->addItem(1);
		
		if (tmp->getWeight() <= capacity && tmp->takenSize() < items.size() - 1) {
			
			tmp->calculateUpperBound();
			if (tmp->getUpperBound() > best->getValue()) {
				queue->push(tmp);
			}
			else
				delete tmp;
			if (tmp->getValue() > best->getValue()) {
				delete best;
				best = new Solution(*tmp);
			}
			
		}
		else {
			delete tmp;
		}

		tmp2 = new Solution(*this, *root);
		tmp2->addItem(0);

		if (tmp2->takenSize() < items.size() - 1)
		{
			tmp2->calculateUpperBound();
			if (tmp2->getUpperBound() > best->getValue())
				queue->push(tmp2);
			else
				delete tmp2;
		}
		else
			delete tmp2;

		delete root;

	}

	best->print_solution();

	return false;
}

bool compRatio(Item* a, Item* b)
{
	return a->getRatio() > b->getRatio();
}


void Knapsack::sortItemsByRatio()
{
	std::sort(this->items.begin(), this->items.end(), compRatio);
}



void Knapsack::printItems()
{
	Item* temp;
	std::cout << "Ilosc przedmiotow: " << this->items.size() << std::endl;
	for (int i = 0; i < this->items.size(); i++)
	{
		std::cout << *items[i] << std::endl;
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
