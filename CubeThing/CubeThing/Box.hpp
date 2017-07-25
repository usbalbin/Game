#pragma once

#include "Utils.hpp"
#include <vector>
#include <assert.h>

#define DIMENSION_COUNT 2
#define SIDE_COUNT (DIMENSION_COUNT * 2)

enum Side : int{
	LEFT = 0, RIGHT = 3,
	UP = 1, DOWN = 2,
	NONE = 255
};

//Returns inverse side eg. ~LEFT is RIGHT etc.
inline Side operator~(Side s) {
	return Side(DIMENSION_COUNT * 2 - 1 - int(s));
}

class Box;

class Neighbors {
public:
	Neighbors(Vector<int> extents) {
		auto& self = *this;
		self[LEFT] = self[RIGHT] = std::vector<Box*>(extents.y, nullptr);
		self[UP] = self[DOWN] = std::vector<Box*>(extents.x, nullptr);
	}
	std::vector<Box*> operator[](Side side) { assert(side != NONE); return sides[(int)side]; }

	std::vector<Box*>* begin() { return &sides[0]; }
	std::vector<Box*>* end() { return &sides[SIDE_COUNT]; }
private:
	std::vector<Box*> sides[SIDE_COUNT];	//Sides contains neighbors
};

class Thing;

class Box
{
public:
	Box(Vector<int> position, Vector<int> extents = { 1, 1 });
	~Box();

	void add(Box& box);

	void registerNeighbors(Box& box);

	Side isAtSide(Box box);

	bool isToLeft(Box box);
	bool isToRight(Box box);

	bool isOver(Box box);
	bool isUnder(Box box);

	int getEdgeLeft();
	int getEdgeRight();

	int getEdgeUp();
	int getEdgeDown();

private:
	Vector<int> position;		//Position relative to parents origin
	Vector<int> size;

	Thing* parent;
	
	Neighbors neighbors;
};