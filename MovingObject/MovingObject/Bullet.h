#pragma once
#include "wx\wx.h"
#include "wx\dcbuffer.h"
class Bullet
{
private:
	int x;
	int y;
	double vx = 0;
	double vy = 0;
	int v = 15;
public:
	void draw(wxAutoBufferedPaintDC &dc);
	void move();
	void shoot(int x, int y);
	Bullet(int x, int y);
	Bullet();
	~Bullet();
};

