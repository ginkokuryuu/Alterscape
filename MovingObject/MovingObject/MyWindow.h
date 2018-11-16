#pragma once
#include "wx\wx.h"
#include "Ball.h"
#include "Bullet.h"
#include <vector>
class MyWindow :
	public wxWindow
{
public:
	~MyWindow();
	MyWindow(wxFrame *frame);
	void onPaint(wxPaintEvent &evt);
	void onTimer(wxTimerEvent &evt);
	void moveBall(wxKeyEvent &evt);
	void stopBall(wxKeyEvent &evt);
	void shootBall(wxMouseEvent &evt);
	void delayShoot(wxTimerEvent &evt);
	void enemySpawn(wxTimerEvent &evt);
private:
	//std::vector<Bullet*> bullets;
	Ball *ball;
	//std::vector<Ball*> enemy;
	std::vector<GameObject*> obj;
	wxTimer *timer;
	wxTimer *shooter;
	wxTimer *spawner;
	DECLARE_EVENT_TABLE()
};

