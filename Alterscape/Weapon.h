#pragma once
#include "Bullet.h"
class CharOne;
class GameWindow;
class Weapon
{
private:
	int type;
	CharOne* owner;
	GameWindow* parent;
public:
	void shoot(int x, int y);
	Weapon(GameWindow* parent, CharOne* owner);
	int getType();
	void setType(int type);
	Weapon();
	~Weapon();
};
