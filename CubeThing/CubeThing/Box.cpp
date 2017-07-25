#include "stdafx.h"
#include "Box.hpp"

#include <assert.h>
#include <algorithm>

#include "Thing.hpp"

Box::Box(Vector<int> position, Vector<int> extents) :
	position(position),
	size(extents),

	neighbors(extents),
	parent(nullptr)
{}

Box::~Box()
{
}

void Box::add(Box & box)
{
	this->registerNeighbors(box);
	
	if (box.parent)
		box.parent->remove();
	box.parent = this->parent;
}

void Box::registerNeighbors(Box& box){
	Side side = isAtSide(box);
	int afirst, alast;
	int bfirst, blast;
	

	if (side == LEFT || side == RIGHT) {
		afirst = this->getEdgeDown() - std::max(this->getEdgeDown(), box.getEdgeDown());//TODO: check those, div by 2???
		alast = this->getEdgeDown() - std::min(this->getEdgeUp(), box.getEdgeUp());

		bfirst = this->getEdgeDown() - std::max(this->getEdgeDown(), box.getEdgeDown());//TODO: check those
		blast = this->getEdgeDown() - std::min(this->getEdgeUp(), box.getEdgeUp());
	}
	else {
		afirst = this->getEdgeLeft() - std::max(this->getEdgeLeft(), box.getEdgeLeft());//TODO: check those
		alast = this->getEdgeLeft() - std::min(this->getEdgeRight(), box.getEdgeRight());

		bfirst = box.getEdgeLeft() - std::max(this->getEdgeLeft(), box.getEdgeLeft());//TODO: check those
		blast = box.getEdgeLeft() - std::min(this->getEdgeRight(), box.getEdgeRight());
	}

	for (int i = afirst; i <= alast; ++i) {
		assert(neighbors[side][i] == nullptr || neighbors[side][i] == &box, "Already a cube here");
		this->neighbors[side][i] = &box;
	}

	for (int i = bfirst; i <= blast; ++i) {
		assert(neighbors[side][i] == nullptr || neighbors[side][i] == &box, "Already a cube here");
		box.neighbors[~side][i] = this;
	}
}

Side Box::isAtSide(Box box) {
	if (isToLeft(box))
		return Side::LEFT;
	if (isToRight(box))
		return Side::RIGHT;
	if (isOver(box))
		return Side::UP;
	if (isUnder(box))
		return Side::DOWN;
	return Side::NONE;
}

bool Box::isToLeft(Box box) {
	return this->getEdgeLeft() == box.getEdgeRight();
}

bool Box::isToRight(Box box) {
	return this->getEdgeRight() == box.getEdgeLeft();
}

bool Box::isOver(Box box) {
	return this->getEdgeUp() == box.getEdgeDown();
}

bool Box::isUnder(Box box) {
	return this->getEdgeDown() == box.getEdgeUp();
}

//Returns 2 times the x coordinate of the left edge
int Box::getEdgeLeft()
{
	return 2 * position.x - size.x;
}

//Returns 2 times the x coordinate of the right edge
int Box::getEdgeRight()
{
	return 2 * position.x + size.x;
}

//Returns 2 times the y coordinate of the top edge
int Box::getEdgeUp()
{
	return 2 * position.y + size.y;
}

//Returns 2 times the y coordinate of the bottom edge
int Box::getEdgeDown()
{
	return 2 * position.y - size.y;
}