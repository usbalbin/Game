#pragma once

#include "Box.hpp"

class Thing
{
public:
	Thing();
	~Thing();
	void remove() {}

	bool func(Box& box);

	Neighbors findNeighbors(Box box);
	void checkAndAddNeighbor(Box box, Box other);

	void attatch(Box b) {};

private:
	std::vector<Box*> members;
	Vector<float> position;
};

