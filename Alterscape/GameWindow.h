#pragma once
#include "wx\wx.h"
#include <unordered_set>
class CharOne;
class GameObject;
class GameFrame;
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
	void addObject(GameObject* object);
	void deleteObject(GameObject* object);
	int getPlayerX();
	int getPlayerY();
	int getGridSize();
	bool isPlayerAlive();
	int getMouseX();
	int getMouseY();
	void updateMouse(wxMouseEvent &evt);
private:
	GameFrame *parentWindow;
	int mouseX;
	int mouseY;
	CharOne *player;
	std::unordered_set<GameObject*> obj;
	std::unordered_set<GameObject*> grid[18][31]; // 18 x 31 @64px gridtiles (1920x1080)
	int gridSize = 64;
	wxTimer *timer;
	wxTimer *shooter;
	wxTimer *spawner;
	DECLARE_EVENT_TABLE()
};

