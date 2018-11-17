#pragma once
#include "GameObject.h"
#include "wx\wx.h"
#include "wx\dcbuffer.h"
class Bullet
	: public GameObject
{
private:
	double vx = 0;
	double vy = 0;
	int v = 15;
public:
	void draw(wxAutoBufferedPaintDC &dc);
	void move();
	void shoot(int x, int y);
	bool isCollidingWith(GameObject* o);
	Bullet(int x, int y);
	Bullet();
	~Bullet();
};

