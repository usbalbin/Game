#include "stdafx.h"
#include "Thing.hpp"

#include <algorithm>


Thing::~Thing()
{
}

bool Thing::func(Box & box)
{
	//if (this->intersects(box))//Does not fit!
	//	return false;

	Neighbors neighbors = findNeighbors(box);
	for (auto& side : neighbors)
		for (auto neighbor : side)
			if(neighbor)
				neighbor->add(box);



	return true;
}

Neighbors Thing::findNeighbors(Box box)
{
	Neighbors result;
	for (auto& member : members) {
		Side side;
		checkAndAddNeighbor(box);
	}
	return Neighbors({1, 1});
}

void Thing::checkAndAddNeighbor(Box box, Box other)
{
	Side side = box.isAtSide(other);
	if (side == NONE)
		return;

	int afirst, alast;
	int bfirst, blast;

	switch (side)
	{
	case LEFT:
	case RIGHT:
		afirst = box.getEdgeDown() - std::max(box.getEdgeDown(), other.getEdgeDown());//TODO: check those, div by 2???
		alast = box.getEdgeDown() - std::min(box.getEdgeUp(), other.getEdgeUp());

		bfirst = box.getEdgeDown() - std::max(box.getEdgeDown(), other.getEdgeDown());//TODO: check those
		blast = box.getEdgeDown() - std::min(box.getEdgeUp(), other.getEdgeUp());
		break;
	case UP:
	case DOWN:
		afirst = box.getEdgeLeft() - std::max(box.getEdgeLeft(), other.getEdgeLeft());//TODO: check those
		alast = box.getEdgeLeft() - std::min(box.getEdgeRight(), other.getEdgeRight());

		bfirst = other.getEdgeLeft() - std::max(box.getEdgeLeft(), other.getEdgeLeft());//TODO: check those
		blast = other.getEdgeLeft() - std::min(box.getEdgeRight(), other.getEdgeRight());
		break;
	default:
		return;
	}

	if(afirst > alast || afirst < )
		result[side][index] = member;


}


