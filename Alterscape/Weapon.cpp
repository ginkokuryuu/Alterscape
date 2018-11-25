#include "Weapon.h"
#include "GameWindow.h"
#include <math.h>
#define PI 3.14159265
void Weapon::shoot(int x, int y)
{
	if (type == 1) {
		Bullet* bullet = new Bullet(this, owner->getX(), owner->getY(), parent);
		bullet->setOwner(owner->getOwner());
		bullet->shoot(x, y);
		parent->addObject(bullet);
		parent->updateGrid(bullet);
	}
	else if (type == 2) {
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
}

Weapon::Weapon(GameWindow * parent, GameObject * owner)
{
	this->parent = parent;
	this->owner = owner;
	type = rand() % 2 + 1;
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
