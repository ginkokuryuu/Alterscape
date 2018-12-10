#pragma once
#include "GameObject.h"
#include "wx\wx.h"
#include "wx\dcbuffer.h"
#include "wx\graphics.h"
class Weapon;
class GameWindow;
class Bullet
	: public GameObject
{
private:
	Weapon *parent;
	GameWindow *window;
	double vx = 0;
	double vy = 0;
	int v = 15;
	int duration;
	wxTimer *range;
	wxStopWatch stopwatch;
	DECLARE_EVENT_TABLE()
public:
	void draw(wxAutoBufferedPaintDC &dc);
	void move();
	void shoot(int x, int y);
	void pause();
	bool isCollidingWith(GameObject* o);
	void outRange(wxTimerEvent &evt);
	double getVx();
	double getVy();
	void setVx(double vx);
	void setVy(double vy);
	Bullet(Weapon* parent, int x, int y, GameWindow* window);
	Bullet();
	~Bullet();
};

