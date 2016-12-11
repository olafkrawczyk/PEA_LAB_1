#include "stdafx.h"
#include "Solution.h"


Solution::Solution()
{
}

Solution::Solution(const Solution & sol)
{
	knap = sol.knap;
	taken = sol.taken;
	cur_item = sol.cur_item;
	upper_bound = sol.upper_bound;
	total_weight = sol.total_weight;
	value = sol.value;
}

Solution::Solution(Knapsack & knap)
{
	cur_item = 0;
	taken = *new std::vector<int>();
	this->knap = &knap;
	upper_bound = 0;

}

Solution::Solution(Knapsack & knap, Solution & sol)
{
	cur_item = sol.cur_item + 1;
	this->knap = &knap;
	taken = *new std::vector<int>(sol.taken);
	upper_bound = sol.upper_bound;
}

float Solution::calculateUpperBound()
{

	upper_bound = 0;
	int weight = getWeight();
	int value = getValue();

	int i = cur_item;
	for (i; i < knap->items.size(); i++)
	{
		weight += knap->items[i]->getSize();
		if (weight <= knap->capacity) {
			value += knap->items[i]->getValue();
		}
		else
			break;
	}
	if (i >= knap->items.size())
		i--;
	upper_bound = value + (knap->capacity - weight) * knap->items[i]->getRatio();
	
	return upper_bound;
}

int Solution::getWeight()
{
	if (cur_item == -1)
		return 0;

	int temp_weight = 0;

	for (int i = 0; i < taken.size(); i++)
	{
		temp_weight += knap->items[i]->getSize()*taken[i];
	}

	return temp_weight;
}

int Solution::getCurr()
{
	return cur_item;
}

int Solution::getValue()
{
	if (cur_item == -1)
		return 0;

	int temp_val = 0;
	for (int i = 0; i < taken.size(); i++)
	{
		temp_val += knap->items[i]->getValue();
	}

	return temp_val;
}

float Solution::getUpperBound()
{
	return upper_bound;
}

void Solution::addItem(int item)
{
	taken.push_back(item);
}

int Solution::takenSize()
{
	return taken.size();
}

void Solution::print_solution()
{
	std::cout << "Solution: \n";
	for (int i = 0; i < taken.size(); i++)
	{	
		if (taken[i] != 0)
			std::cout << *knap->items[i] << std::endl;
	}
}

Solution::~Solution()
{
	taken.clear();
	taken.shrink_to_fit();
	cur_item = 0;
	upper_bound = 0;
	total_weight = 0;
	value = 0;
}


