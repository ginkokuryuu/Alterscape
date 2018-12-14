#include "Bullet.h"
#include "Weapon.h"
#include "GameWindow.h"
#include <cmath>
#include <algorithm>
#define PI 3.14159265

BEGIN_EVENT_TABLE(Bullet, wxEvtHandler)
	EVT_TIMER(-1, Bullet::outRange)
END_EVENT_TABLE()

void Bullet::draw(wxAutoBufferedPaintDC &dc)
{
	wxGraphicsContext *gc = wxGraphicsContext::Create(dc);
	gc->SetPen(*wxBLACK_PEN);
	gc->Translate(x, y);
	if (owner == 1) gc->SetBrush(wxBrush(wxColour(165, 149, 255)));
	else gc->SetBrush(wxBrush(wxColor(*wxRED)));
	wxGraphicsPath path = gc->CreatePath();
	path.AddCircle(0, 0, r);
	gc->StrokePath(path);
	gc->FillPath(path);
	delete gc;
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

void Bullet::setBullet(int bulletType)
{
	if (bulletType == 1) {
		this->bulletType = 1;
		r = 10;
		duration = 1200;
	}
	else if (bulletType == 2) {
		this->bulletType = 2;
		r = 5;
		duration = 600;
	}
	else if (bulletType == 4) {
		this->bulletType = 4;
		r = 35;
		v = 10;
		duration = 1500;
	}
	range->StartOnce(duration);
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
	range = new wxTimer(this, -1);
	switch (parent->getType())
	{
	case 1:
		bulletType = 1;
		r = 10;
		duration = 1200;
		break;
	case 2:
		bulletType = 2;
		r = 5;
		duration = 600;
		break;
	case 4:
		bulletType = 4;
		r = 35;
		v = 10;
		duration = 1500;
		break;
	default:
		break;
	}
	range->StartOnce(duration);
	stopwatch.Start(0);
}

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
	range->Stop();
	delete range;
	if (bulletType == 4) {
		for (int i = 0; i < 36; i++) {
			Bullet* bullet = new Bullet(parent, x, y, window);
			bullet->setOwner(owner);
			bullet->shoot(760, 540);
			double vx = std::cos(i * 10 * PI / 180.0)*bullet->getVx() - std::sin(i * 10 * PI / 180.0)*bullet->getVy();
			double vy = std::sin(i * 10 * PI / 180.0)*bullet->getVx() + std::cos(i * 10 * PI / 180.0)*bullet->getVy();
			bullet->setVx(vx);
			bullet->setVy(vy);
			bullet->setBullet(1);
			window->addObject(bullet);
			window->updateGrid(bullet);
		}
	}
}
