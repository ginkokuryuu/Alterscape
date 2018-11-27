#pragma once
#include "GameObject.h"
class GameWindow;
class Bullet;
class Shield :
	public GameObject
{
private:
	GameObject* parent;
	GameWindow* window;
	int r = 25;
public:
	void draw(wxAutoBufferedPaintDC &dc);
	bool isCollidingWith(GameObject* o);
	Shield(GameObject* parent, GameWindow* window);
	void deflect(Bullet* bullet);
	Shield();
	~Shield();
};

