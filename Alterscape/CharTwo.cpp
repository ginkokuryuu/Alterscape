#include "CharTwo.h"
#include "GameWindow.h"
#include "Weapon.h"
#include "MedKit.h"
#include "wx/graphics.h"
#include <cmath>
#define TIMER_ID 2200
BEGIN_EVENT_TABLE(CharTwo, wxEvtHandler)
	EVT_TIMER(TIMER_ID, CharTwo::botShooter)
	EVT_TIMER(TIMER_ID + 1, CharTwo::botMover)
END_EVENT_TABLE()

void CharTwo::draw(wxAutoBufferedPaintDC & dc)
{
	int s = 10;
	wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
	wxGraphicsPath path = gc->CreatePath();
	gc->Translate(x, y);
	gc->SetBrush(wxBrush(wxColour(255 * ((50 - hp) / 50.0), 255 * (hp / 50.0), 0)));
	gc->DrawRoundedRectangle(-r, -r - 20, 120 * hp / 50.0, 10, 5);
	path.MoveToPoint(r*cos(0), r*sin(0));
	path.AddLineToPoint(r*cos(72 * acos(-1) / 180.0), r*sin(72 * acos(-1) / 180.0));
	path.AddLineToPoint(r*cos(72*2 * acos(-1) / 180.0), r*sin(72*2 * acos(-1) / 180.0));
	path.AddLineToPoint(r*cos(72*3 * acos(-1) / 180.0), r*sin(72*3 * acos(-1) / 180.0));
	path.AddLineToPoint(r*cos(72*4 * acos(-1) / 180.0), r*sin(72*4 * acos(-1) / 180.0));
	path.AddLineToPoint(r*cos(0 * acos(-1) / 180.0), r*sin(0 * acos(-1) / 180.0));
	path.MoveToPoint(35 + s, 0);
	path.AddLineToPoint(35, s);
	path.AddLineToPoint(35, -s);
	path.AddLineToPoint(35 + s, 0);
	gc->SetBrush(wxBrush(wxColour(255, 0, 0)));
	gc->SetPen(*wxBLACK_PEN);
	int X = parent->getPlayerX() - x;
	int Y = parent->getPlayerY() - y;
	double a, b, c;
	a = X;
	b = Y;
	c = sqrt(a*a + b * b);
	double sin = b / c;
	double cos = a / c;
	gc->Rotate(atan2(sin, cos));
	gc->StrokePath(path);
	gc->FillPath(path);
	delete gc;
}

bool CharTwo::isCollidingWith(GameObject * o)
{
	return false;
}

void CharTwo::botMover(wxTimerEvent & evt)
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
		mover->Start(rand() % 500 + 1500);
	}
	else mover->Stop();
}

void CharTwo::botShooter(wxTimerEvent & evt)
{
	if (owner != 1) {
		if (parent->isPlayerAlive()) {
			shoot(parent->getPlayerX(), parent->getPlayerY());
			shooter->Start(rand() % 500 + 4500);
		}
	}
	else shooter->Stop();
}

void CharTwo::shoot(int x, int y)
{
	weapon->shoot(x, y);
}

void CharTwo::pause()
{
	if (!parent->isPaused()) {
		shooter->Stop();
		mover->Stop();
	}
	else {
		shooter->Start(rand() % 1000 + 4000);
		mover->Start(rand() % 1000);
	}
}

void CharTwo::move()
{
	int tx = x + a * xDir;
	int ty = y + a * yDir;
	if (tx > r && tx < wxGetDisplaySize().GetWidth() - r && ty > r && ty < wxGetDisplaySize().GetHeight() - r) {
		//wxMessageOutputDebug().Printf("%d %d", x, y);
		x += a * xDir;
		y += a * yDir;
	}
}

void CharTwo::moveX()
{
	if (xDir < 1) ++xDir;
}

void CharTwo::moveY()
{
	if (yDir < 1) ++yDir;
}

void CharTwo::moveMX()
{
	if (xDir > -1) --xDir;
}

void CharTwo::moveMY()
{
	if (yDir > -1) --yDir;
}

void CharTwo::decHP()
{
	--hp;
}

int CharTwo::getHP()
{
	return hp;
}

CharTwo::CharTwo(int x, int y, GameWindow * parent)
{
	this->x = x;
	this->y = y;
	this->r = 60;
	this->parent = parent;
	this->type = 5;
	weapon = new Weapon(parent, this);
	mover = new wxTimer(this, TIMER_ID + 1);
	shooter = new wxTimer(this, TIMER_ID);
	mover->Start(300);
	shooter->Start(500);
	parent->updateGrid(this);
	parent->addObject(this);
}

CharTwo::CharTwo()
{
}


CharTwo::~CharTwo()
{
	delete shooter;
	delete mover;
	delete weapon;
	for (int i = 0; i < 2; i++) {
		int randX = rand() % 2*r + x - r;
		int randY = rand() % 2*r + y - r;
		MedKit* med = new MedKit(randX, randY, parent);
	}
}
