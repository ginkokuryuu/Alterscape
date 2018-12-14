#include "MedKit.h"
#include "GameWindow.h"
#include "wx\graphics.h"


void MedKit::draw(wxAutoBufferedPaintDC & dc)
{
	wxGraphicsContext *gc = wxGraphicsContext::Create(dc);
	gc->Translate(x, y);
	wxGraphicsPath path = gc->CreatePath();
	path.MoveToPoint(0, 0);
	path.AddLineToPoint(0, -r);
	path.AddLineToPoint(-r, r);
	path.AddLineToPoint(r, r);
	path.AddLineToPoint(0, -r);
	gc->SetBrush(wxBrush(wxColour(0, 255, 0)));
	gc->SetPen(*wxBLACK_PEN);
	gc->StrokePath(path);
	gc->FillPath(path);
	delete gc;
}

bool MedKit::isCollidingWith(GameObject * o)
{
	return false;
}

void MedKit::pause()
{
}

MedKit::MedKit(int x, int y, GameWindow * window)
{
	this->x = x;
	this->y = y;
	this->r = 10;
	this->window = window;
	this->type = 4;
	this->owner = 1;
	window->updateGrid(this);
	window->addObject(this);
}

MedKit::MedKit()
{
}


MedKit::~MedKit()
{
}
