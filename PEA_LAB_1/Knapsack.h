#pragma once
#include "stdafx.h"
#include "Item.h"
#include <vector>
#include <queue>

struct Node
{
	int level, profit, bound;
	float weight;
	std::vector<Item> items;
	Node() {

	}
	Node(int l, int p, float w) {
		level = l;
		profit = p;
		weight = w;
	}
	Node(const Node& n) {
		level = n.level;
		profit = n.profit;
		weight = n.weight;
		bound = n.bound;
		items = *new std::vector<Item>(n.items);
	}
	~Node() {
		items.clear();
		items.shrink_to_fit();
	}
};

class Knapsack
{
	
	int capacity;
	int allItems;
	int sumVal;
	int sumSize;
	std::vector<Item> items;

public:
	Knapsack();
	Knapsack(int capacity);
	~Knapsack();
	bool inputFromFile(std::string filename);
	bool bruteForce(bool);
	int BNB(bool);
	void sortItemsByRatio();
	void printItems();
	void setCapacity(int capacity);
	int getCapacity();
	int setItems(std::vector<Item> items);

	float bound(Node u, int n, int W);
};