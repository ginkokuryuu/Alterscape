#pragma once
#include "wx\wx.h"
#include "wx\dcbuffer.h"
class Ball
{
private:
	int x;
	int y;
	int r;
	int vx = 0;
	int vy = 0;
	int ax = 0;
	int ay = 0;
	int a = 5;
public:
	Ball();
	Ball(int x, int y, int r);
	void draw(wxAutoBufferedPaintDC &dc, bool isPlayer);
	void move();
	void moveX();
	void moveY();
	void moveMX();
	void moveMY();
	void stopX();
	void stopY();
	int getX();
	int getY();
	~Ball();
};

