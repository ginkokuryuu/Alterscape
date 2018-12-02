#pragma once
#include "GameObject.h"
class GameWindow;
class Bullet;
class CharOne;
class Shield :
	public GameObject
{
private:
	CharOne* parent;
	GameWindow* window;
public:
	void draw(wxAutoBufferedPaintDC &dc);
	bool isCollidingWith(GameObject* o);
	Shield(CharOne* parent, GameWindow* window);
	void deflect(Bullet* bullet);
	void pause();
	Shield();
	~Shield();
};

