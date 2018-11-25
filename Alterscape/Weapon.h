#pragma once
#include "Bullet.h"
class Weapon
{
private:
	GameObject* owner;
	//GameWindow* parent;
public:
	void shoot(int x, int y);
	//Weapon(GameWindow* parent, GameObject* owner);
	Weapon();
	~Weapon();
};

