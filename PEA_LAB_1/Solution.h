#pragma once
#include "stdafx.h"
#include <vector>
#include "Item.h"
#include "Knapsack.h"


class Solution
{
	Knapsack* knap;
	std::vector<int> taken;
	int cur_item;
	float upper_bound;
	int total_weight;
	int value;

public:
	Solution();
	Solution(const Solution & sol);
	Solution(Knapsack &knap);
	Solution(Knapsack &knap, Solution &sol);
	void calculateUpperBound();
	int getWeight();
	int getCurr();
	int getValue();
	float getUpperBound();
	void addItem(int item);
	int takenSize();
	void print_solution();
	~Solution();
};

