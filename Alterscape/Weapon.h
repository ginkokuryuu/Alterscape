#pragma once
#include "Bullet.h"
class GameObject;
class GameWindow;
class Weapon
{
private:
	int type;
	GameObject* owner;
	GameWindow* parent;
public:
	void shoot(int x, int y);
	Weapon(GameWindow* parent, GameObject* owner);
	int getType();
	void setType(int type);
	Weapon();
	~Weapon();
};
