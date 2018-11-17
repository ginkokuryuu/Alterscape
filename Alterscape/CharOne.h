#pragma once
#include "GameObject.h"
#include "wx\wx.h"
#include "wx\dcbuffer.h"
class CharOne
	: public GameObject
{
private:
	int vx = 0;
	int vy = 0;
	int ax = 0;
	int ay = 0;
	int a = 5;
public:
	CharOne();
	CharOne(int x, int y, int r);
	bool isCollidingWith(GameObject* o);
	void draw(wxAutoBufferedPaintDC &dc);
	void move();
	void moveX();
	void moveY();
	void moveMX();
	void moveMY();
	void stopX();
	void stopY();
	~CharOne();
};

