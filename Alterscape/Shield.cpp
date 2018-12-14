#include "Shield.h"
#include "GameWindow.h"
#include "Bullet.h"
#include "CharOne.h"

#define PI 3.14159265

void Shield::draw(wxAutoBufferedPaintDC & dc)
{
	wxGraphicsContext *gc = wxGraphicsContext::Create(dc);
	gc->SetPen(*wxBLACK_PEN);
	gc->SetBrush(wxBrush(wxColour(0, 150, 255)));
	gc->Translate(parent->getX(), parent->getY());
	float scaleY = wxGetDisplaySize().GetHeight() / 1080.0;
	float scaleX = wxGetDisplaySize().GetWidth() / 1920.0;
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
			x = cos * (parent->getR() - 15);
			y = sin * (parent->getR() - 15);
			wxGraphicsPath path = gc->CreatePath();
			//path.AddCircle(x, y, r*scaleY);
			path.MoveToPoint(0, 0);
			path.AddArc(0, 0, 35, -PI/4.0, PI/4.0, 1);
			gc->Rotate(atan2(sin, cos));
			x += parent->getX();
			y += parent->getY();
			gc->StrokePath(path);
			gc->FillPath(path);
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
			x = cos * (parent->getR() - 15);
			y = sin * (parent->getR() - 15);
			wxGraphicsPath path = gc->CreatePath();
			//path.AddCircle(x, y, r*scaleY);
			path.MoveToPoint(0, 0);
			path.AddArc(0, 0, 35, -PI / 4.0, PI / 4.0, 1);
			gc->Rotate(atan2(sin, cos));
			x += parent->getX();
			y += parent->getY();
			gc->StrokePath(path);
			gc->FillPath(path);
		}
	}
	delete gc;
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
