#include "Ball.h"
#include <cmath>
#include <algorithm>

Ball::Ball()
{
}


Ball::Ball(int x, int y, int r)
{
	this->x = x;
	this->y = y;
	this->r = r;
	type = 1;
}

void Ball::draw(wxAutoBufferedPaintDC & dc)
{
	if (owner == 1) dc.SetBrush(wxBrush(wxColor(*wxWHITE)));
	else dc.SetBrush(wxBrush(wxColor(*wxRED)));
	//dc.SetPen(wxPen(wxColor(*wxRED), 1, wxPENSTYLE_SOLID)); //ball outline
	dc.DrawCircle(wxPoint(x, y), r);
}

void Ball::move()
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

void Ball::moveX()
{
	vx = a;
}

void Ball::moveY()
{
	vy = a;
}

void Ball::moveMX()
{
	vx = -a;
}

void Ball::moveMY()
{
	vy = -a;
}

void Ball::stopX()
{
	vx = 0;
}

void Ball::stopY()
{
	vy = 0;
}

int Ball::getX()
{
	return x;
}

int Ball::getY()
{
	return y;
}

Ball::~Ball()
{
}
