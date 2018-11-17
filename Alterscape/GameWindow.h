#pragma once
#include "wx\wx.h"
#include "CharOne.h"
#include "Bullet.h"
#include <unordered_set>
class GameWindow :
	public wxWindow
{
public:
	~GameWindow();
	GameWindow(wxFrame *frame);
	void onPaint(wxPaintEvent &evt);
	void onTimer(wxTimerEvent &evt);
	void moveChar(wxKeyEvent &evt);
	void stopChar(wxKeyEvent &evt);
	void shootChar(wxMouseEvent &evt);
	void delayShoot(wxTimerEvent &evt);
	void enemySpawn(wxTimerEvent &evt);
	void checkCollision();
	void updateGrid(GameObject* object);
private:
	CharOne *player;
	std::unordered_set<GameObject*> obj;
	std::unordered_set<GameObject*> grid[13][17]; // 12 x 16 @64px gridtiles
	int gridSize = 64;
	wxTimer *timer;
	wxTimer *shooter;
	wxTimer *spawner;
	DECLARE_EVENT_TABLE()
};

