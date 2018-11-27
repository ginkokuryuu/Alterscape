#include "Weapon.h"
#include "GameWindow.h"
#include "CharOne.h"
#include <math.h>
#define PI 3.14159265
void Weapon::shoot(int x, int y)
{
	if (type == 1) {
		if (owner->getShieldPtr() != nullptr) owner->deleteShield();
		Bullet* bullet = new Bullet(this, owner->getX(), owner->getY(), parent);
		bullet->setOwner(owner->getOwner());
		bullet->shoot(x, y);
		parent->addObject(bullet);
		parent->updateGrid(bullet);
	}
	else if (type == 2) {
		if (owner->getShieldPtr() != nullptr) owner->deleteShield();
		for (int i = -2; i < 3; i++) {
			Bullet* bullet = new Bullet(this, owner->getX(), owner->getY(), parent);
			bullet->setOwner(owner->getOwner());
			bullet->shoot(x, y);
			double vx = std::cos(i * 5 * PI / 180.0)*bullet->getVx() - std::sin(i * 5 * PI / 180.0)*bullet->getVy();
			double vy = std::sin(i * 5 * PI / 180.0)*bullet->getVx() + std::cos(i * 5 * PI / 180.0)*bullet->getVy();
			bullet->setVx(vx);
			bullet->setVy(vy);
			parent->addObject(bullet);
			parent->updateGrid(bullet);
		}
	}
	else if (type == 3) {
		if (owner->getShieldPtr() == nullptr) {
			owner->setShield();
			parent->addObject(owner->getShieldPtr());
			parent->updateGrid(owner->getShieldPtr());
		}
	}
}

Weapon::Weapon(GameWindow * parent, CharOne * owner)
{
	this->parent = parent;
	this->owner = owner;
	type = rand() % 3 + 1;
}

int Weapon::getType()
{
	return type;
}

void Weapon::setType(int type)
{
	this->type = type;
}

Weapon::Weapon()
{
}


Weapon::~Weapon()
{
}
