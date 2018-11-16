#pragma once
#include "wx\wx.h"
#include "wx\dcbuffer.h"
class GameObject
{
protected:
	int type;
	int owner = 2;
public:
	virtual void draw(wxAutoBufferedPaintDC &dc) = 0;
	virtual void move() = 0;
	int getObjType();
	void setOwner(int owner);
	GameObject();
	~GameObject();
};
