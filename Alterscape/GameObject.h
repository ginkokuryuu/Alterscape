#pragma once
#include "wx\wx.h"
#include "wx\dcbuffer.h"
class GameObject
	: public wxEvtHandler
{
protected:
	double x;
	double y;
	int gridX = 0;
	int gridY = 0;
	int r = 0;
	int type;
	int owner = 2;
public:
	virtual void draw(wxAutoBufferedPaintDC &dc) = 0;
	virtual void move();
	virtual bool isCollidingWith(GameObject* o) = 0;
	int getGridX();
	int getGridY();
	void setGridX(int gridSize);
	void setGridY(int gridSize);
	int getX();
	int getY();
	void setX(int x);
	void setY(int y);
	int getR();
	int getObjType();
	int getOwner();
	void setOwner(int owner);
	virtual void pause() = 0;
	GameObject();
	~GameObject();
};
