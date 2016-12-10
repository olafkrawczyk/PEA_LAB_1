#include "stdafx.h"
#include "Item.h"


Item::Item()
{
}

Item::Item(int aSize, int aWeight)
{
	this->size = aSize;
	this->value = aWeight;
}

void Item::setSize(int size)
{
	this->size = size;
}

void Item::setValue(int weight)
{
	this->value = weight;
}

int Item::getSize()
{
	return this->size;
}

int Item::getValue()
{
	return this->value;
}

float Item::getRatio()
{
	return (float)this->value/this->size;
}


Item::~Item()
{
}

std::ostream & operator<<(std::ostream & os, Item & iItem)
{
	return  os << "<Item s: " << iItem.getSize() << " v: " << iItem.getValue() << ">";
}
