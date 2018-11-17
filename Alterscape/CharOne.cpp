#include "CharOne.h"
#include <cmath>
#include <algorithm>

CharOne::CharOne()
{
}


CharOne::CharOne(int x, int y, int r)
{
	this->x = x;
	this->y = y;
	this->r = r;
	type = 1;
}

bool CharOne::isCollidingWith(GameObject * o)
{
	return false;
}

void CharOne::draw(wxAutoBufferedPaintDC & dc)
{
	if (owner == 1) dc.SetBrush(wxBrush(wxColor(*wxWHITE)));
	else dc.SetBrush(wxBrush(wxColor(*wxRED)));
	//dc.SetPen(wxPen(wxColor(*wxRED), 1, wxPENSTYLE_SOLID)); //ball outline
	dc.DrawCircle(wxPoint(x, y), r);
}

void CharOne::move()
{
	int tx = x + vx;
	int ty = y + vy;
	if (tx > 0 && tx < 1024 && ty > 0 && ty < 768) {
		//wxMessageOutputDebug().Printf("%d %d", x, y);
		x += vx;
		y += vy;
		/*if (ax > 0) {
			if (vx <= 10) vx += ax;
		}
		else if (ax < 0) {
			if (vx >= -10) vx += ax;
		}
		else {
			if (vx > 0) vx -= a;
			else if (vx < 0) vx += a;
		}
		if (ay > 0) {
			if (vy <= 10) vy += ay;
		}
		else if (ay < 0) {
			if (vy >= -10) vy += ay;
		}
		else {
			if (vy > 0) vy -= a;
			else if (vy < 0) vy += a;
		}*/
	}
	else if (tx < 0 || tx > 1024) {
		vx = ax = 0;
	}
	else if (ty < 0 || ty > 768) {
		vy = ay = 0;
	}
}

void CharOne::moveX()
{
	vx = a;
}

void CharOne::moveY()
{
	vy = a;
}

void CharOne::moveMX()
{
	vx = -a;
}

void CharOne::moveMY()
{
	vy = -a;
}

void CharOne::stopX()
{
	vx = 0;
}

void CharOne::stopY()
{
	vy = 0;
}

CharOne::~CharOne()
{
}
