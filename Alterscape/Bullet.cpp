#include "Bullet.h"
#include "Weapon.h"
#include "GameWindow.h"
#include <cmath>
#include <algorithm>

BEGIN_EVENT_TABLE(Bullet, wxEvtHandler)
	EVT_TIMER(-1, Bullet::outRange)
END_EVENT_TABLE()

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

void Bullet::pause()
{
	if (!window->isPaused()) {
		range->Stop();
		stopwatch.Pause();
	}
	else {
		duration = abs(duration - stopwatch.Time());
		range->Start(duration);
		stopwatch.Start(0);
	}
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

void Bullet::outRange(wxTimerEvent & evt)
{
	window->deleteObject(this);
}

double Bullet::getVx()
{
	return vx;
}

double Bullet::getVy()
{
	return vy;
}

void Bullet::setVx(double vx)
{
	this->vx = vx;
}

void Bullet::setVy(double vy)
{
	this->vy = vy;
}

Bullet::Bullet(Weapon* parent, int x, int y, GameWindow* window)
{
	this->parent = parent;
	this->x = x;
	this->y = y;
	this->window = window;
	type = 2;
	switch (parent->getType())
	{
	case 1:
		r = 10;
		range = new wxTimer(this, -1);
		range->StartOnce(1200);
		duration = 1200;
		break;
	case 2:
		r = 5;
		range = new wxTimer(this, -1);
		range->StartOnce(600);
		duration = 600;
		break;
	default:
		break;
	}
	stopwatch.Start(0);
}

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
	range->Stop();
	delete range;
}
