#include "Shield.h"
#include "GameWindow.h"
#include "Bullet.h"
#include "CharOne.h"

void Shield::draw(wxAutoBufferedPaintDC & dc)
{
	if (window->isPlayerAlive()) {
		if (parent->getOwner() == 1) {
			int X = window->getMouseX() - parent->getX();
			int Y = window->getMouseY() - parent->getY();
			double a, b, c;
			a = X;
			b = Y;
			c = sqrt(a*a + b * b);
			double sin = b / c;
			double cos = a / c;
			x = cos * (parent->getR() - 15) + parent->getX();
			y = sin * (parent->getR() - 15) + parent->getY();
			dc.SetBrush(wxBrush(wxColour(0, 150, 255)));
			dc.DrawCircle(wxPoint(x, y), r);
		}
		else {
			int X = window->getPlayerX() - parent->getX();
			int Y = window->getPlayerY() - parent->getY();
			double a, b, c;
			a = X;
			b = Y;
			c = sqrt(a*a + b * b);
			double sin = b / c;
			double cos = a / c;
			x = cos * (parent->getR() - 15) + parent->getX();
			y = sin * (parent->getR() - 15) + parent->getY();
			dc.SetBrush(wxBrush(wxColour(0, 150, 255)));
			dc.DrawCircle(wxPoint(x, y), r);
		}
	}
}

bool Shield::isCollidingWith(GameObject * o)
{
	return false;
}

Shield::Shield(CharOne * parent, GameWindow * window)
{
	this->parent = parent;
	this->window = window;
	r = 25;
	type = 3;
}

void Shield::deflect(Bullet * bullet)
{
	if (bullet->getOwner() != 1) {
		bullet->shoot(window->getMouseX(), window->getMouseY());
		bullet->setOwner(1);
	}
	else if (window->isPlayerAlive()) {
		bullet->shoot(window->getPlayerX(), window->getPlayerY());
		bullet->setOwner(2);
	}
}

void Shield::pause()
{
}

Shield::Shield()
{
}


Shield::~Shield()
{
	parent->setShieldPtr(nullptr);
}
