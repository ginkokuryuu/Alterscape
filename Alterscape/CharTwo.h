#pragma once
#include "GameObject.h"
class Weapon;
class GameWindow;
class CharTwo :
	public GameObject
{
private:
	int hp = 40;
	int a = 2;
	int xDir = 0;
	int yDir = 0;
	Weapon* weapon;
	GameWindow* parent;
	wxTimer *shooter;
	wxTimer *mover;
	DECLARE_EVENT_TABLE()
public:
	void draw(wxAutoBufferedPaintDC &dc);
	bool isCollidingWith(GameObject* o);
	void botMover(wxTimerEvent &evt);
	void botShooter(wxTimerEvent &evt);
	void shoot(int x, int y);
	void pause();
	void move();
	void moveX();
	void moveY();
	void moveMX();
	void moveMY();
	void decHP();
	int getHP();
	CharTwo(int x, int y, GameWindow* parent);
	CharTwo();
	~CharTwo();
};
