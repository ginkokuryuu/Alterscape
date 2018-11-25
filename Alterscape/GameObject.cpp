#include "GameObject.h"


int GameObject::getX()
{
	return x;
}

int GameObject::getY()
{
	return y;
}

void GameObject::setX(int x)
{
	this->x = x;
}

void GameObject::setY(int y)
{
	this->y = y;
}

int GameObject::getR()
{
	return r;
}

int GameObject::getObjType()
{
	return type;
}

int GameObject::getOwner()
{
	return owner;
}

void GameObject::setOwner(int owner)
{
	this->owner = owner;
}

GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

int GameObject::getGridX()
{
	return gridX;
}

int GameObject::getGridY()
{
	return gridY;
}

void GameObject::setGridX(int gridSize)
{
	gridX = x / gridSize;
}

void GameObject::setGridY(int gridSize)
{
	gridY = y / gridSize;
}
