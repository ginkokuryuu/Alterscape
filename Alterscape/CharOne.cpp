#include "CharOne.h"
#include "Weapon.h"
#include "Shield.h"
#include "GameWindow.h"
#include <cmath>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#define TIMER_ID 2100

BEGIN_EVENT_TABLE(CharOne, wxEvtHandler)
	EVT_TIMER(TIMER_ID, CharOne::botShoot)
	EVT_TIMER(TIMER_ID + 1, CharOne::botMove)
	EVT_TIMER(TIMER_ID + 2, CharOne::changeWeapon)
END_EVENT_TABLE()

CharOne::CharOne()
{
}

CharOne::CharOne(GameWindow* parent, int x, int y, int r)
{
	float scaleY = wxGetDisplaySize().GetHeight() / 1080.0;
	float scaleX = wxGetDisplaySize().GetWidth() / 1920.0;
	this->parent = parent;
	this->x = x;
	this->y = y;
	this->r = r * scaleY;
	type = 1;
	botshooter = new wxTimer(this, TIMER_ID);
	botshooter->Start(rand() % 1000 + 100);
	botmover = new wxTimer(this, TIMER_ID + 1);
	botmover->Start(100);
	weaponchanger = new wxTimer(this, TIMER_ID + 2);
	weapon = new Weapon(parent, this);
	nextweapon = rand() % 3 + 1;
	while (nextweapon == weapon->getType()) nextweapon = rand() % 3 + 1;
	wduration = rand() % 3000 + 7000;
	weaponchanger->Start(wduration);
	stopwatch.Start(0);
}

bool CharOne::isCollidingWith(GameObject * o)
{
	if (o->getObjType() == 4) {
		int dx = o->getX() - x;
		int dy = o->getY() - y;
		int or = o->getR();
		if ((dx*dx) + (dy*dy) <= (or +r) * (or +r)) {
			if (owner == o->getOwner()) return true;
			else return false;
		}
	}
	return false;
}

void CharOne::draw(wxAutoBufferedPaintDC & dc)
{
	wxGraphicsContext *gc = wxGraphicsContext::Create(dc);
	gc->SetPen(*wxBLACK_PEN);
	gc->Translate(x, y);
	float scaleY = wxGetDisplaySize().GetHeight() / 1080.0;
	float scaleX = wxGetDisplaySize().GetWidth() / 1920.0;
	if (shield != nullptr) shield->draw(dc);
	else {
	}
	if (owner == 1) {
		gc->SetBrush(wxBrush(wxColour(165, 149, 255)));
		wxGraphicsPath path = gc->CreatePath();
		path.AddCircle(0, 0, r*scaleY);
		gc->StrokePath(path);
		gc->FillPath(path);
		if (shield == nullptr) {
			int s = 10;
			int X = parent->getMouseX() - x;
			int Y = parent->getMouseY() - y;
			double a, b, c;
			a = X;
			b = Y;
			c = sqrt(a*a + b * b);
			double sin = b / c;
			double cos = a / c;
			wxGraphicsPath path2 = gc->CreatePath();
			path2.MoveToPoint(35 + s, 0);
			path2.AddLineToPoint(35, s);
			path2.AddLineToPoint(35, -s);
			path2.AddLineToPoint(35 + s, 0);
			gc->SetBrush(wxBrush(wxColour(165, 149, 255, 150)));
			gc->Rotate(atan2(sin, cos));
			gc->StrokePath(path2);
			gc->FillPath(path2);
		}
	}
	else {
		int X = parent->getPlayerX() - x;
		int Y = parent->getPlayerY() - y;
		double a, b, c;
		a = X;
		b = Y;
		c = sqrt(a*a + b * b);
		double sin = b / c;
		double cos = a / c;
		gc->SetBrush(*wxRED_BRUSH);
		wxGraphicsPath path = gc->CreatePath();
		path.MoveToPoint(r, 0);
		path.AddLineToPoint(-r, r);
		path.AddLineToPoint(-r, -r);
		path.AddLineToPoint(r, 0);
		gc->Rotate(atan2(sin, cos));
		gc->StrokePath(path);
		gc->FillPath(path);
	}
	delete gc;
}

void CharOne::botShoot(wxTimerEvent & evt)
{
	if (owner != 1) {
		if (parent->isPlayerAlive()) {
			shoot(parent->getPlayerX(), parent->getPlayerY());
			botshooter->Start(rand() % 1000 + 600);
		}
	}
	else botshooter->Stop();
}

void CharOne::botMove(wxTimerEvent & evt)
{
	if (owner != 1) {
		int axis = rand() % 4;
		switch (axis)
		{
		case 0:
			xDir = 0;
			moveX();
			break;
		case 1:
			yDir = 0;
			moveY();
			break;
		case 2:
			xDir = 0;
			moveMX();
			break;
		case 3:
			yDir = 0;
			moveMY();
			break;
		default:
			break;
		}
		botmover->Start(rand() % 500 + 250);
	}
	else botmover->Stop();
}

void CharOne::changeWeapon(wxTimerEvent & evt)
{
	deleteShield();
	int neww = nextweapon;
	if (neww == 3) setShield();
	weapon->setType(neww);
	nextweapon = rand() % 3 + 1;
	while (nextweapon == neww) nextweapon = rand() % 3 + 1;
	wduration = rand() % 3000 + 7000;
	weaponchanger->Start(wduration);
	stopwatch.Start(0);
}

void CharOne::shoot(int x, int y)
{
	weapon->shoot(x, y);
}

void CharOne::pause()
{
	if (!parent->isPaused()) {
		botshooter->Stop();
		botmover->Stop();
		weaponchanger->Stop();
	}
	else {
		botshooter->Start(rand() % 1000 + 500);
		botmover->Start(rand() % 1000);
		wduration = abs(wduration - stopwatch.Time());
		weaponchanger->Start(wduration);
		stopwatch.Start(0);
	}
}

void CharOne::move()
{
	int tx = x + a * xDir;
	int ty = y + a * yDir;
	if (tx > r && tx < wxGetDisplaySize().GetWidth() - r && ty > r && ty < wxGetDisplaySize().GetHeight() - r) {
		//wxMessageOutputDebug().Printf("%d %d", x, y);
		x += a * xDir;
		y += a * yDir;
	}
}

void CharOne::moveX()
{
	if (xDir < 1) ++xDir;
}

void CharOne::moveY()
{
	if (yDir < 1) ++yDir;
}

void CharOne::moveMX()
{
	if (xDir > -1) --xDir;
}

void CharOne::moveMY()
{
	if (yDir > -1) --yDir;
}

int CharOne::getWeaponType()
{
	return weapon->getType();
}

int CharOne::getNextWeapon()
{
	return nextweapon;
}

int CharOne::getWeaponDuration()
{
	return wduration;
}

int CharOne::getStopwatchTime()
{
	return stopwatch.Time();
}

Shield * CharOne::getShieldPtr()
{
	return shield;
}

void CharOne::setShieldPtr(Shield * shield)
{
	this->shield = shield;
}

void CharOne::setShield()
{
	shield = new Shield(this, parent);
	shield->setOwner(owner);
	parent->addObject(shield);
	parent->updateGrid(shield);
}

void CharOne::deleteShield()
{
	if (shield != nullptr) {
		parent->deleteObject(shield);
		shield = nullptr;
	}
}

CharOne::~CharOne()
{
	botshooter->Stop();
	botmover->Stop();
	weaponchanger->Stop();
	delete botshooter;
	delete botmover;
	delete weapon;
	delete weaponchanger;
	if (shield != nullptr) {
		parent->deleteObject(shield);
		shield = nullptr;
	}
}
