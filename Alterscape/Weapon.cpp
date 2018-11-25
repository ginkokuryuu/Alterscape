#include "Weapon.h"

void Weapon::shoot(int x, int y)
{
	Bullet* bullet = new Bullet(owner->getX(),owner->getY());
	bullet->setOwner(owner->getOwner());
	bullet->shoot(x, y);
	//parent->addObject(bullet);
}

Weapon::Weapon()
{
}


Weapon::~Weapon()
{
}
