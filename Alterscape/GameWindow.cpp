#include "GameWindow.h"
#include "GameFrame.h"
#include "CharOne.h"
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
	EVT_MOTION(GameWindow::updateMouse)
END_EVENT_TABLE()

GameWindow::GameWindow(wxFrame * frame)
	: wxWindow(frame, wxID_ANY)
{
	parentWindow = (GameFrame*)frame;
	SetBackgroundStyle(wxBG_STYLE_PAINT);
	SetBackgroundColour(*wxBLACK);
	for (int i = 0; i < 18; i++) {
		for (int j = 0; j < 31; j++) grid[i][j].clear();
	}
	timer = new wxTimer(this, TIMER_ID);
	timer->Start(1); // 1ms refresh delay
	srand(time(NULL)); // generate random seed
	spawner = new wxTimer(this, TIMER_ID + 2);
	spawner->Start(rand() % 4000 + 1000); // generate random spawner delay (ms)
	player = new CharOne(this, wxGetDisplaySize().GetWidth()/2, wxGetDisplaySize().GetHeight()/2, 25);
	player->setOwner(1);
	updateGrid(player);
	addObject(player);
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
	pdc.DrawRectangle(wxPoint(0, 0), wxGetDisplaySize());
	for (auto it : obj) it->draw(pdc);
}

void GameWindow::onTimer(wxTimerEvent & evt)
{
	if (!isPlayerAlive()) {
		timer->Stop();
		parentWindow->GameOver();
		return;
	}
	for (auto it = obj.begin(); it != obj.end();) {
		(*it)->move();
		updateGrid(*it);
		if ((*it)->getObjType() == 2 && ((*it)->getX() > wxGetDisplaySize().GetWidth() || (*it)->getX() < 0 || (*it)->getY() > wxGetDisplaySize().GetHeight() || (*it)->getY() < 0)) {
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
	if (player != nullptr) {
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
}

void GameWindow::stopChar(wxKeyEvent & evt)
{
	if (player != nullptr) {
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
}

void GameWindow::shootChar(wxMouseEvent & evt)
{
	if (shooter == nullptr && player != nullptr) {
		wxPoint mousePos = evt.GetPosition();
		player->shoot(mousePos.x, mousePos.y);
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
	int randX = rand() % (wxGetDisplaySize().GetWidth()-50) + 25;
	int randY = rand() % (wxGetDisplaySize().GetHeight()-50) + 25;
	int randTime = rand() % 4000 + 1000;
	CharOne* enemy = new CharOne(this, randX, randY, 25);
	updateGrid(enemy);
	if (player != nullptr) {
		while ((enemy->getGridX() >= player->getGridX() - 3 && enemy->getGridX() <= player->getGridX() + 3) &&
			(enemy->getGridY() >= player->getGridY() - 3 && enemy->getGridY() <= player->getGridY() + 3)) {
			randX = rand() % 950 + 50;
			randY = rand() % 650 + 50;
			enemy->setX(randX);
			enemy->setY(randY);
			updateGrid(enemy);
		}
	}
	addObject(enemy); // spawn enemy on random position
	spawner->Start(randTime); // re-generate random spawner delay(ms)
}

void GameWindow::checkCollision() // all object collision (collision handler baru di bullet)
{
	for (auto it1 = obj.begin(); it1 != obj.end();) {
		int gx = (*it1)->getGridX();
		int gy = (*it1)->getGridY();
		for (int y = -1; y < 2; y++) {
			for (int x = -1; x < 2; x++) {
				if (gy + y >= 0 && gy + y < 18 && gx + x >= 0 && gx + x < 31) {
					for (auto it2 = grid[gy + y][gx + x].begin(); it2 != grid[gy + y][gx + x].end();) {
						if (*it1 != *it2 && (*it1)->isCollidingWith(*it2)) {
							if (*it2 == player) player = nullptr;
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

void GameWindow::addObject(GameObject * object)
{
	obj.insert(object);
}

void GameWindow::deleteObject(GameObject * object)
{
	grid[object->getGridY()][object->getGridX()].erase(object);
	delete object;
	obj.erase(object);
}

int GameWindow::getPlayerX()
{
	return player->getX();
}

int GameWindow::getPlayerY()
{
	return player->getY();
}

int GameWindow::getGridSize()
{
	return gridSize;
}

bool GameWindow::isPlayerAlive()
{

	if (player == nullptr) return false;
	else return true;
}

int GameWindow::getMouseX()
{
	return mouseX;
}

int GameWindow::getMouseY()
{
	return mouseY;
}

void GameWindow::updateMouse(wxMouseEvent & evt)
{
	mouseX = evt.GetPosition().x;
	mouseY = evt.GetPosition().y;
}
