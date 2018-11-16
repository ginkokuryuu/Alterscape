#include "GameObject.h"


int GameObject::getObjType()
{
	return type;
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
