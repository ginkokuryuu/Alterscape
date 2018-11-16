#include "Bullet.h"
#include <cmath>
#include <algorithm>

void Bullet::draw(wxAutoBufferedPaintDC &dc)
{
	dc.SetBrush(wxBrush(wxColor(*wxRED)));
	//dc.SetPen(wxPen(wxColor(*wxRED), 1, wxPENSTYLE_SOLID)); //ball outline
	dc.DrawCircle(wxPoint(x, y), 10);
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

Bullet::Bullet(int x, int y)
{
	this->x = x;
	this->y = y;
}

Bullet::Bullet()
{
}


Bullet::~Bullet()
{
}
