#pragma once
#include "GameObject.h"
class GameWindow;
class MedKit :
	public GameObject
{
private:
	GameWindow *window;
public:
	void draw(wxAutoBufferedPaintDC &dc);
	bool isCollidingWith(GameObject* o);
	void pause();
	MedKit(int x, int y, GameWindow* window);
	MedKit();
	~MedKit();
};

