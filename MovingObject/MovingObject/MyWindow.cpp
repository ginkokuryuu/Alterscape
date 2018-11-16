#include "MyWindow.h"
#include <stdlib.h>
#include <time.h>
#define TIMER_ID 2000

BEGIN_EVENT_TABLE(MyWindow, wxWindow)
	EVT_PAINT(MyWindow::onPaint)
	EVT_TIMER(TIMER_ID, MyWindow::onTimer)
	EVT_TIMER(TIMER_ID + 1, MyWindow::delayShoot)
	EVT_TIMER(TIMER_ID + 2, MyWindow::enemySpawn)
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
	timer->Start(1); // 1ms refresh delay
	srand(time(NULL)); // generate random seed
	spawner = new wxTimer(this, TIMER_ID + 2);
	spawner->Start(rand() % 4000 + 1000); // generate random spawner delay (ms)
	ball = new Ball(500, 500, 25);
	ball->setOwner(1);
	obj.push_back(ball);
}

MyWindow::~MyWindow()
{
	timer->Stop();
	spawner->Stop();
	delete timer;
	delete spawner;
	//for (int i = 0; i < bullets.size(); i++) delete bullets[i];
	//for (int i = 0; i < enemy.size(); i++) delete enemy[i];
	for (int i = 0; i < obj.size(); i++) delete obj[i];
}

void MyWindow::onPaint(wxPaintEvent & evt)
{
	wxAutoBufferedPaintDC pdc(this);
	
	pdc.SetBrush(wxBrush(wxColor(*wxBLACK)));
	pdc.DrawRectangle(wxPoint(0, 0), wxSize(1024, 768));
	/*if (!bullets.empty()) {
		for (int i = 0; i < bullets.size(); i++) {
			bullets[i]->draw(pdc, 1);
		}
	}
	ball->draw(pdc,1);
	
	if (!enemy.empty()) {
		for (int i = 0; i < enemy.size(); i++) {
			enemy[i]->draw(pdc);
		}
	}*/
	for (int i = 0; i < obj.size(); i++) {
		obj[i]->draw(pdc);
	}
}

void MyWindow::onTimer(wxTimerEvent & evt)
{
	//static int counter = 0;
	//wxMessageOutputDebug().Printf("wxTimer event %d.", counter++);
	for (int i = 0; i < obj.size(); i++) obj[i]->move();
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
		Bullet* bull = new Bullet(ball->getX(), ball->getY());
		bull->setOwner(1);
		bull->shoot(mousePos.x, mousePos.y);
		//bullets.push_back(bull);
		
		obj.push_back(bull);
		shooter = new wxTimer(this, TIMER_ID + 1);
		shooter->StartOnce(200); // shoot delay (ms)
	}
}

void MyWindow::delayShoot(wxTimerEvent & evt)
{
	delete shooter;
	shooter = nullptr;
}

void MyWindow::enemySpawn(wxTimerEvent &evt)
{
	int randX = rand() % 950 + 50;
	int randY = rand() % 650 + 50;
	int randTime = rand() % 4000 + 1000;
	Ball* enem = new Ball(randX, randY, 25);
	//enemy.push_back(enem); // spawn enemy on random position
	obj.push_back(enem);
	spawner->Start(randTime); // re-generate random spawner delay(ms)
}
