#include "Bullet.h"
#include <cmath>
#include <algorithm>

void Bullet::draw(wxAutoBufferedPaintDC &dc)
{
	if (owner == 1) dc.SetBrush(wxBrush(wxColor(*wxWHITE)));
	else dc.SetBrush(wxBrush(wxColor(*wxRED)));
	//dc.SetPen(wxPen(wxColor(*wxRED), 1, wxPENSTYLE_SOLID)); //ball outline
	dc.DrawCircle(wxPoint(x, y), r);
}

void Bullet::move()
{
	x += vx;
	y += vy;
}


void Bullet::shoot(int x, int y)
{
	int X = x - this->x;
	int Y = y - this->y;
	double a, b, c;
	a = X;
	b = Y;
	c = sqrt(a*a + b * b);
	double sin = b / c;
	double cos = a / c;
	vx = cos * v;
	vy = sin * v;
}

bool Bullet::isCollidingWith(GameObject * o)
{
	int dx = o->getX() - x;
	int dy = o->getY() - y;
	int or = o->getR();
	if ((dx*dx) + (dy*dy) <= (or +r) * (or +r)) {
		if (owner != o->getOwner()) return true;
		else return false;
	}
	else return false;
}

Bullet::Bullet(int x, int y)
{
	this->x = x;
	this->y = y;
	r = 10;
	type = 2;
}

Bullet::Bullet()
{
}


Bullet::~Bullet()
{
}
