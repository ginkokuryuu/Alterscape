#pragma once
#include "wx\wx.h"
#include "wx\dcbuffer.h"
#include <list>
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
	void onKeyDown(wxKeyEvent &evt);
	void onKeyUp(wxKeyEvent &evt);
	void onChar(wxKeyEvent &evt);
	void onClick(wxMouseEvent &evt);
	void delayShoot(wxTimerEvent &evt);
	void enemySpawn(wxTimerEvent &evt);
	void checkCollision();
	void updateGrid(GameObject* object);
	void addObject(GameObject* object);
	void deleteObject(GameObject* object);
	void timeScore(wxTimerEvent &evt);
	void drawUI(wxAutoBufferedPaintDC &dc);
	void imageLoad();
	void pauseGame();
	bool isPaused();
	int getPlayerX();
	int getPlayerY();
	int getGridSize();
	bool isPlayerAlive();
	int getMouseX();
	int getMouseY();
	void updateMouse(wxMouseEvent &evt);
private:
	bool paused = false;
	int hp = 5;
	int score = 0;
	int kill = 0;
	GameFrame *parentWindow;
	int mouseX;
	int mouseY;
	CharOne *player;
	std::list<GameObject*> obj;
	std::list<GameObject*> grid[18][31]; // 18 x 31 @64px gridtiles (1920x1080)
	int gridSize = 64;
	wxTimer *timer;
	wxTimer *shooter;
	wxTimer *spawner;
	wxTimer *timescore;
	wxBitmap *pausemenu;
	wxBitmap *killcount;
	wxBitmap* weapon[6];
	wxBitmap *background;
	DECLARE_EVENT_TABLE()
};

