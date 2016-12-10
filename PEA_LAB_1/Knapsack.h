#pragma once
#include "stdafx.h"
#include "Item.h"
#include <vector>
#

class Knapsack
{
	
	int capacity;
	int allItems;
	int sumVal;
	int sumSize;
	std::vector<Item*> items;

	friend class Solution;


public:
	Knapsack();
	Knapsack(int capacity);
	~Knapsack();
	bool inputFromFile(std::string filename);
	bool bruteForce();
	bool BNB();
	void sortItemsByRatio();
	void printItems();
	void setCapacity(int capacity);
	int getCapacity();
	
};