#include "GameWindow.h"
#include <stdlib.h>
#include <time.h>
#define TIMER_ID 2000

BEGIN_EVENT_TABLE(GameWindow, wxWindow)
	EVT_PAINT(GameWindow::onPaint)
	EVT_TIMER(TIMER_ID, GameWindow::onTimer)
	EVT_TIMER(TIMER_ID + 1, GameWindow::delayShoot)
	EVT_TIMER(TIMER_ID + 2, GameWindow::enemySpawn)
	EVT_KEY_DOWN(GameWindow::moveChar)
	EVT_KEY_UP(GameWindow::stopChar)
	EVT_LEFT_DOWN(GameWindow::shootChar)
END_EVENT_TABLE()

GameWindow::GameWindow(wxFrame * frame)
	: wxWindow(frame, wxID_ANY)
{
	SetInitialSize(wxSize(1024, 768));
	SetBackgroundStyle(wxBG_STYLE_PAINT);
	SetBackgroundColour(*wxBLACK);
	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 17; j++) grid[i][j].clear();
	}
	timer = new wxTimer(this, TIMER_ID);
	timer->Start(1); // 1ms refresh delay
	srand(time(NULL)); // generate random seed
	spawner = new wxTimer(this, TIMER_ID + 2);
	spawner->Start(rand() % 4000 + 1000); // generate random spawner delay (ms)
	player = new CharOne(500, 500, 25);
	player->setOwner(1);
	obj.insert(player);
	updateGrid(player);
}

GameWindow::~GameWindow()
{
	timer->Stop();
	spawner->Stop();
	delete timer;
	delete spawner;
	for (auto it : obj) delete it;
}

void GameWindow::onPaint(wxPaintEvent & evt)
{
	wxAutoBufferedPaintDC pdc(this);

	pdc.SetBrush(wxBrush(wxColor(*wxBLACK)));
	pdc.DrawRectangle(wxPoint(0, 0), wxSize(1024, 768));
	for (auto it : obj) it->draw(pdc);
}

void GameWindow::onTimer(wxTimerEvent & evt)
{
	for (auto it = obj.begin(); it != obj.end();) {
		(*it)->move();
		updateGrid(*it);
		if ((*it)->getObjType() == 2 && ((*it)->getX() > 1024 || (*it)->getX() < 0 || (*it)->getY() > 768 || (*it)->getY() < 0)) {
			grid[(*it)->getGridY()][(*it)->getGridX()].erase(*it);
			delete *it;
			it = obj.erase(it);
		}
		else ++it;
	}
	checkCollision();
	Refresh(0);
	//Update();
}

void GameWindow::moveChar(wxKeyEvent & evt)
{
	int keycode = evt.GetKeyCode();
	switch (keycode)
	{
	case 'W':
		player->moveMY();
		break;
	case 'A':
		player->moveMX();
		break;
	case 'S':
		player->moveY();
		break;
	case 'D':
		player->moveX();
		break;
	default:
		break;
	}
}

void GameWindow::stopChar(wxKeyEvent & evt)
{
	int keycode = evt.GetKeyCode();
	switch (keycode)
	{
	case 'W':
		player->stopY();
		break;
	case 'A':
		player->stopX();
		break;
	case 'S':
		player->stopY();
		break;
	case 'D':
		player->stopX();
		break;
	default:
		break;
	}
}

void GameWindow::shootChar(wxMouseEvent & evt)
{
	if (shooter == nullptr) {
		wxPoint mousePos = evt.GetPosition();
		Bullet* bull = new Bullet(player->GameObject::getX(), player->GameObject::getY());
		bull->setOwner(1);
		bull->shoot(mousePos.x, mousePos.y);
		obj.insert(bull);
		updateGrid(bull);
		shooter = new wxTimer(this, TIMER_ID + 1);
		shooter->StartOnce(200); // shoot delay (ms)
	}
}

void GameWindow::delayShoot(wxTimerEvent & evt)
{
	delete shooter;
	shooter = nullptr;
}

void GameWindow::enemySpawn(wxTimerEvent &evt)
{
	int randX = rand() % 950 + 50;
	int randY = rand() % 650 + 50;
	int randTime = rand() % 4000 + 1000;
	CharOne* enemy = new CharOne(randX, randY, 25);
	obj.insert(enemy); // spawn enemy on random position
	updateGrid(enemy);
	spawner->Start(randTime); // re-generate random spawner delay(ms)
}

void GameWindow::checkCollision() // all object collision (collision handler baru di bullet)
{
	for (auto it1 = obj.begin(); it1 != obj.end();) {
		int gx = (*it1)->getGridX();
		int gy = (*it1)->getGridY();
		for (int y = -1; y < 2; y++) {
			for (int x = -1; x < 2; x++) {
				if (gy + y >= 0 && gy + y < 13 && gx + x >= 0 && gx + x < 17) {
					for (auto it2 = grid[gy + y][gx + x].begin(); it2 != grid[gy + y][gx + x].end();) {
						if (*it1 != *it2 && (*it1)->isCollidingWith(*it2)) {
							obj.erase(*it2);
							delete *it2;
							it2 = grid[gy + y][gx + x].erase(it2);
						}
						else ++it2;
					}
				}
			}
		}
		++it1;
	}
}

void GameWindow::updateGrid(GameObject * object)
{
	int gx = object->getX() / gridSize;
	int gy = object->getY() / gridSize;
	int tx = object->getGridX();
	int ty = object->getGridY();
	if (gx != tx || gy != ty) {
		if (grid[ty][tx].find(object) != grid[ty][tx].end()) grid[ty][tx].erase(object);
		object->setGridX(gridSize);
		object->setGridY(gridSize);
		grid[gy][gx].insert(object);
	}
}
