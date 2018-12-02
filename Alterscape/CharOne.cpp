#include "CharOne.h"
#include "Weapon.h"
#include "Shield.h"
#include "GameWindow.h"
#include <cmath>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
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
	this->parent = parent;
	this->x = x;
	this->y = y;
	this->r = r;
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
	return false;
}

void CharOne::draw(wxAutoBufferedPaintDC & dc)
{
	if (shield != nullptr) shield->draw(dc);
	if (owner == 1) dc.SetBrush(wxBrush(wxColour(255, 255, 255)));
	else dc.SetBrush(wxBrush(wxColor(*wxRED)));
	//dc.SetPen(wxPen(wxColor(*wxRED), 1, wxPENSTYLE_SOLID)); //ball outline
	dc.DrawCircle(wxPoint(x, y), r);
}

void CharOne::botShoot(wxTimerEvent & evt)
{
	if (owner != 1) {
		if (parent->isPlayerAlive()) {
			shoot(parent->getPlayerX(), parent->getPlayerY());
			botshooter->Start(rand() % 1000 + 500);
		}
	}
	else botshooter->Stop();
}

void CharOne::botMove(wxTimerEvent & evt)
{
	if (owner != 1) {
		stopX();
		stopY();
		int axis = rand() % 8;
		switch (axis)
		{
		case 0:
			moveX();
			break;
		case 1:
			moveY();
			break;
		case 2:
			moveMX();
			break;
		case 3:
			moveMY();
			break;
		case 4:
			moveX();
			moveY();
			break;
		case 5:
			moveY();
			moveMX();
			break;
		case 6:
			moveMX();
			moveMY();
			break;
		case 7:
			moveMY();
			moveX();
			break;
		default:
			break;
		}
		botmover->Start(rand() % 1000);
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
	int tx = x + vx;
	int ty = y + vy;
	if (tx > r && tx < wxGetDisplaySize().GetWidth() - r && ty > r && ty < wxGetDisplaySize().GetHeight() - r) {
		//wxMessageOutputDebug().Printf("%d %d", x, y);
		x += vx;
		y += vy;
	}
	else if (tx < r || tx > wxGetDisplaySize().GetWidth() - r) {
		vx = ax = 0;
	}
	else if (ty < r || ty > wxGetDisplaySize().GetHeight() - r) {
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

int CharOne::getWeaponType()
{
	return weapon->getType();
}

int CharOne::getNextWeapon()
{
	return nextweapon;
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
