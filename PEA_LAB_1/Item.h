#pragma once
class Item
{
	int size;
	int value;
public:
	Item();
	Item(int size, int value);
	void setSize(int size);
	void setValue(int value);
	int getSize();
	int getValue();
	float getRatio();
	friend std::ostream& operator<<(std::ostream&, Item& iItem);
	~Item();
};

