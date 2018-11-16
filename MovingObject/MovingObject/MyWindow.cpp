#include "MyWindow.h"
#include "Ball.h"
#include "Bullet.h"
#define TIMER_ID 2000

BEGIN_EVENT_TABLE(MyWindow, wxWindow)
	EVT_PAINT(MyWindow::onPaint)
	EVT_TIMER(TIMER_ID, MyWindow::onTimer)
	EVT_TIMER(TIMER_ID+1, MyWindow::delayShoot)
	EVT_KEY_DOWN(MyWindow::moveBall)
	EVT_KEY_UP(MyWindow::stopBall)
	EVT_LEFT_DOWN(MyWindow::shootBall)
END_EVENT_TABLE()

MyWindow::MyWindow(wxFrame * frame)
	: wxWindow(frame, wxID_ANY)
{
	SetInitialSize(wxSize(1024, 768));
	SetBackgroundStyle(wxBG_STYLE_PAINT);
	SetBackgroundColour(*wxBLACK);
	timer = new wxTimer(this, TIMER_ID);
	timer->Start(1); //1ms refresh delay
	ball = new Ball(500, 500, 25);
}

MyWindow::~MyWindow()
{
	timer->Stop();
	delete timer;
	delete ball;
	for (int i = 0; i < bullets.size(); i++) delete bullets[i];
}

void MyWindow::onPaint(wxPaintEvent & evt)
{
	wxAutoBufferedPaintDC pdc(this);
	
	pdc.SetBrush(wxBrush(wxColor(*wxBLACK)));
	pdc.DrawRectangle(wxPoint(0, 0), wxSize(1024, 768));
	if (!bullets.empty()) {
		for (int i = 0; i < bullets.size(); i++) {
			bullets[i]->draw(pdc);
		}
	}
	ball->draw(pdc);
	

}

void MyWindow::onTimer(wxTimerEvent & evt)
{
	//static int counter = 0;
	//wxMessageOutputDebug().Printf("wxTimer event %d.", counter++);
	ball->move();
	if (!bullets.empty()) {
		for (int i = 0; i < bullets.size(); i++) {
			bullets[i]->move();
		}
	}
	Refresh(0);
	//Update();
}

void MyWindow::moveBall(wxKeyEvent & evt)
{
	int keycode = evt.GetKeyCode();
	switch (keycode)
	{
	case 'W':
		ball->moveMY();
		break;
	case 'A':
		ball->moveMX();
		break;
	case 'S':
		ball->moveY();
		break;
	case 'D':
		ball->moveX();
		break;
	default:
		break;
	}
	//ball->move();
}

void MyWindow::stopBall(wxKeyEvent & evt)
{
	int keycode = evt.GetKeyCode();
	switch (keycode)
	{
	case 'W':
		ball->stopY();
		break;
	case 'A':
		ball->stopX();
		break;
	case 'S':
		ball->stopY();
		break;
	case 'D':
		ball->stopX();
		break;
	default:
		break;
	}
}

void MyWindow::shootBall(wxMouseEvent & evt)
{
	if (shooter == nullptr) {
		wxPoint mousePos = evt.GetPosition();

		bullets.push_back(new Bullet(ball->getX(), ball->getY()));
		bullets.back()->shoot(mousePos.x, mousePos.y);
		shooter = new wxTimer(this, TIMER_ID + 1);
		shooter->StartOnce(200); //shoot delay (ms)
	}
}

void MyWindow::delayShoot(wxTimerEvent & evt)
{
	delete shooter;
	shooter = nullptr;
}
