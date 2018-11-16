#pragma once
#include "wx\wx.h"
#include <vector>
class Ball;
class Bullet;
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
	std::vector<Bullet*> bullets;
	Ball *ball;
	std::vector<Ball*> enemy;
	wxTimer *timer;
	wxTimer *shooter;
	wxTimer *spawner;
	DECLARE_EVENT_TABLE()
};

