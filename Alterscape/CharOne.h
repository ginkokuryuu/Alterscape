#pragma once
#include "wx\wx.h"
#include "wx\dcbuffer.h"
#include "GameObject.h"
#include "Bullet.h"
class Weapon;
class GameWindow;
class CharOne
	: public GameObject
{
private:
	Weapon* weapon;
	int vx = 0;
	int vy = 0;
	int ax = 0;
	int ay = 0;
	int a = 5;
	int hp = 10;
	wxTimer *botshooter;
	wxTimer *botmover;
	wxTimer *weaponchanger;
	GameWindow* parent;
	DECLARE_EVENT_TABLE()
public:
	CharOne();
	CharOne(GameWindow* parent, int x, int y, int r);
	bool isCollidingWith(GameObject* o);
	void draw(wxAutoBufferedPaintDC &dc);
	void botShoot(wxTimerEvent &evt);
	void botMove(wxTimerEvent &evt);
	void changeWeapon(wxTimerEvent &evt);
	void shoot(int x, int y);
	int getHP();
	void move();
	void moveX();
	void moveY();
	void moveMX();
	void moveMY();
	void stopX();
	void stopY();
	~CharOne();
};

