#include "GameWindow.h"
#include "GameFrame.h"
#include "CharOne.h"
#include <stdlib.h>
#include <time.h>
#include <sstream>
#define TIMER_ID 2000

BEGIN_EVENT_TABLE(GameWindow, wxWindow)
	EVT_PAINT(GameWindow::onPaint)
	EVT_TIMER(TIMER_ID, GameWindow::onTimer)
	EVT_TIMER(TIMER_ID + 1, GameWindow::delayShoot)
	EVT_TIMER(TIMER_ID + 2, GameWindow::enemySpawn)
	EVT_TIMER(TIMER_ID + 3, GameWindow::timeScore)
	EVT_KEY_DOWN(GameWindow::onKeyDown)
	EVT_KEY_UP(GameWindow::onKeyUp)
	EVT_CHAR(GameWindow::onChar)
	EVT_LEFT_DOWN(GameWindow::onClick)
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
	timescore = new wxTimer(this, TIMER_ID + 3);
	timescore->Start(100);
	player = new CharOne(this, wxGetDisplaySize().GetWidth()/2, wxGetDisplaySize().GetHeight()/2, 25);
	player->setOwner(1);
	if (player->getShieldPtr() != nullptr) (player->getShieldPtr())->setOwner(1);
	updateGrid(player);
	addObject(player);
	imageLoad();
}

GameWindow::~GameWindow()
{
	timer->Stop();
	spawner->Stop();
	timescore->Stop();
	delete timer;
	delete spawner;
	delete timescore;
	delete pausemenu;
	for (auto it : weapon) delete it;
	delete background;
	delete killcount;
	for (auto it : obj) if (it != nullptr) {
		delete it;
		it = nullptr;
	}
	wxMessageOutputDebug().Printf("over");
}

void GameWindow::onPaint(wxPaintEvent & evt)
{
	wxAutoBufferedPaintDC pdc(this);
	pdc.SetBrush(wxBrush(wxColour(0, 0, 0)));
	pdc.DrawBitmap(*background, wxPoint(0, 0));
	for (auto it : obj) if (it->getObjType() != 3) it->draw(pdc);
	drawUI(pdc);
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
			grid[(*it)->getGridY()][(*it)->getGridX()].remove(*it);
			delete *it;
			it = obj.erase(it);
		}
		else ++it;
	}
	checkCollision();
	Refresh(0);
}

void GameWindow::onKeyDown(wxKeyEvent & evt)
{
	if (player != nullptr) {
		int keycode = evt.GetKeyCode();
		//wxMessageOutputDebug().Printf("%d", keycode);
		if (!paused) {
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
			case 27:
				evt.Skip();
				break;
			default:
				break;
			}
		}
		else if (keycode == 27) evt.Skip();
	}
}

void GameWindow::onKeyUp(wxKeyEvent & evt)
{
	if (player != nullptr) {
		int keycode = evt.GetKeyCode();
		if (!paused) {
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
}

void GameWindow::onChar(wxKeyEvent & evt)
{
	int key = evt.GetKeyCode();
	if (key == 27) pauseGame();
}

void GameWindow::onClick(wxMouseEvent & evt)
{
	wxPoint mousePos = evt.GetPosition();
	wxMessageOutputDebug().Printf("%d %d", mousePos.x, mousePos.y);
	if (!paused) {
		if (shooter == nullptr && player != nullptr) {
			player->shoot(mousePos.x, mousePos.y);
			shooter = new wxTimer(this, TIMER_ID + 1);
			shooter->StartOnce(200 * player->getWeaponType()); // shoot delay (ms)
		}
	}
	else {
		float scale = wxGetDisplaySize().GetHeight() / 1080.0;
		if (mousePos.x >= 832*scale && mousePos.x <= 1090*scale) {
			if (mousePos.y >= 540*scale && mousePos.y <= 627*scale) pauseGame();
			else if (mousePos.y >= 674*scale && mousePos.y <= 755*scale) {
				deleteObject(player);
				player = nullptr;
				timer->Stop();
				parentWindow->GameOver();
			}
		}
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

void GameWindow::checkCollision() 
{
	for (auto it1 = obj.begin(); it1 != obj.end();) {
		bool hit = 0;
		if ((*it1)->getObjType() == 2) { // bullet collision
			int gx = (*it1)->getGridX();
			int gy = (*it1)->getGridY();
			for (int y = -1; y < 2; y++) {
				for (int x = -1; x < 2; x++) {
					if (gy + y >= 0 && gy + y < 18 && gx + x >= 0 && gx + x < 31) {
						for (auto it2 = grid[gy + y][gx + x].begin(); it2 != grid[gy + y][gx + x].end();) {
							if ((*it2)->getObjType() == 1) {
								if ((*it1)->isCollidingWith(*it2)) {
									if (((CharOne*)(*it2))->getShieldPtr() != nullptr) {
										if ((*it1)->isCollidingWith(((CharOne*)(*it2))->getShieldPtr())) {
											(((CharOne*)(*it2))->getShieldPtr())->deflect((Bullet*)(*it1));
											wxMessageOutputDebug().Printf("t1");
											++it2;
										}
										else {
											hit = 1;
											if (*it2 == player) {
												if (hp > 1) {
													--hp;
													++it2;
												}
												else {
													player = nullptr;
													obj.remove(*it2);
													delete *it2;
													*it2 = nullptr;
													it2 = grid[gy + y][gx + x].erase(it2);
												}
											}
											else {
												obj.remove(*it2);
												delete *it2;
												*it2 = nullptr;
												it2 = grid[gy + y][gx + x].erase(it2);
												score += 50;
												kill++;
												wxMessageOutputDebug().Printf("a1");
											}
											grid[gy + y][gx + x].remove(*it1);
											delete *it1;
											it1 = obj.erase(it1);
											break;
										}
									}
									else {
										hit = 1;
										if (*it2 == player) {
											if (hp > 1) {
												--hp;
												++it2;
											}
											else {
												player = nullptr;
												obj.remove(*it2);
												delete *it2;
												*it2 = nullptr;
												it2 = grid[gy + y][gx + x].erase(it2);
											}
										}
										else {
											obj.remove(*it2);
											delete *it2;
											*it2 = nullptr;
											it2 = grid[gy + y][gx + x].erase(it2);
											score += 50;
											kill++;
											wxMessageOutputDebug().Printf("a2");
										}
										grid[gy + y][gx + x].remove(*it1);
										delete *it1;
										it1 = obj.erase(it1);
										break;
									}
								}
								else ++it2;
							}
							else if ((*it2)->getObjType() == 3) {
								if ((*it1)->isCollidingWith(*it2)) {
									((Shield*)(*it2))->deflect((Bullet*)(*it1));
									wxMessageOutputDebug().Printf("t2");
								}
								++it2;
							}
							else ++it2;
						}
					}
					if (hit) x = 2;
				}
				if (hit) y = 2;
			}
		}
		if (!hit) ++it1;
	}
}

void GameWindow::updateGrid(GameObject * object)
{
	int gx = object->getX() / gridSize;
	int gy = object->getY() / gridSize;
	int tx = object->getGridX();
	int ty = object->getGridY();
	if (gx != tx || gy != ty) {
		grid[ty][tx].remove(object);
		object->setGridX(gridSize);
		object->setGridY(gridSize);
		grid[gy][gx].push_back(object);
	}
}

void GameWindow::addObject(GameObject * object)
{
	obj.push_back(object);
}

void GameWindow::deleteObject(GameObject * object)
{
	grid[object->getGridY()][object->getGridX()].remove(object);
	obj.remove(object);
	delete object;
}

void GameWindow::timeScore(wxTimerEvent & evt)
{
	score++;
}

void GameWindow::drawUI(wxAutoBufferedPaintDC &dc)
{
	if (isPlayerAlive()) {
		float scale = wxGetDisplaySize().GetHeight() / 1080.0;
		int curr = player->getWeaponType();
		int next = player->getNextWeapon();
		dc.DrawBitmap(wxBitmap(*weapon[curr - 1]), wxPoint(45 * scale, 27 * scale));
		dc.DrawBitmap(wxBitmap(*weapon[next + 2]), wxPoint(45 * scale, 220 * scale));
		dc.DrawBitmap(wxBitmap(*killcount), wxPoint(320 * scale, 118 * scale));

		dc.SetFont(wxFont(30 * scale, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
		dc.SetTextForeground(wxColour(255, 255, 255));
		std::wstringstream pts;
		pts << score << " pts" << std::ends;
		dc.DrawText(pts.str().c_str(), wxPoint(230 * scale, 20 * scale));
		std::wstringstream ko;
		ko << kill << std::ends;
		dc.DrawText(ko.str().c_str(), wxPoint(230 * scale, 130 * scale));

		wxPoint tri[3];
		int s = 20 * scale;
		int x = 160 * scale;
		int y = 220 * scale;
		int dist = 50 * scale;
		dc.SetBrush(wxBrush(wxColour(255, 0, 0)));
		for (int i = 0; i < hp; i++) {
			tri[0] = wxPoint(x + dist * i, y);
			tri[1] = wxPoint(x + dist * i + s, y);
			tri[2] = wxPoint(x + + dist * i + s / 2, y + s);
			dc.DrawPolygon(3, tri);
		}
	}
}

void GameWindow::imageLoad()
{
	float scale = wxGetDisplaySize().GetHeight() / 1080.0;
	wxMessageOutputDebug().Printf("x%f", scale);
	wxLogNull pls;
	wxStandardPaths &stdPaths = wxStandardPaths::Get();
	wxString execpath = stdPaths.GetExecutablePath();
	wxString filepath = wxFileName(execpath).GetPath() + wxT("\\res\\Pause_Menu.png");
	pausemenu = new wxBitmap(wxImage(filepath).Scale(461 * scale, 620 * scale));

	filepath = wxFileName(execpath).GetPath() + wxT("\\res\\Kill_Counter.png");
	killcount = new wxBitmap(wxImage(filepath).Scale(67 * scale, 53 * scale));

	filepath = wxFileName(execpath).GetPath() + wxT("\\res\\Now_Rifle.png");
	weapon[0] = new wxBitmap(wxImage(filepath).Scale(146 * scale, 146 * scale));

	filepath = wxFileName(execpath).GetPath() + wxT("\\res\\Now_Shotgun.png");
	weapon[1] = new wxBitmap(wxImage(filepath).Scale(146 * scale, 146 * scale));

	filepath = wxFileName(execpath).GetPath() + wxT("\\res\\Now_Shield.png");
	weapon[2] = new wxBitmap(wxImage(filepath).Scale(146 * scale, 146 * scale));

	filepath = wxFileName(execpath).GetPath() + wxT("\\res\\Next_Rifle.png");
	weapon[3] = new wxBitmap(wxImage(filepath).Scale(78 * scale, 78 * scale));

	filepath = wxFileName(execpath).GetPath() + wxT("\\res\\Next_Shotgun.png");
	weapon[4] = new wxBitmap(wxImage(filepath).Scale(78 * scale, 78 * scale));

	filepath = wxFileName(execpath).GetPath() + wxT("\\res\\Next_Shield.png");
	weapon[5] = new wxBitmap(wxImage(filepath).Scale(78 * scale, 78 * scale));

	filepath = wxFileName(execpath).GetPath() + wxT("\\res\\Background.png");
	background = new wxBitmap(wxImage(filepath).Scale(wxGetDisplaySize().GetWidth(), wxGetDisplaySize().GetHeight()));
}

void GameWindow::pauseGame()
{
	if (!paused) {
		timer->Stop();
		spawner->Stop();
		timescore->Stop();
		for (auto it : obj) {
			it->pause();
		}
		float scale = wxGetDisplaySize().GetHeight() / 1080.0;
		wxClientDC dc(this);
		dc.DrawBitmap(*pausemenu, wxPoint((wxGetDisplaySize().GetWidth() - 461)*scale / 2, (wxGetDisplaySize().GetHeight() - 620)* scale / 2));
		paused = true;
	}
	else {
		for (auto it : obj) {
			it->pause();
		}
		timer->Start(1);
		spawner->Start(2000);
		timescore->Start(100);
		paused = false;
	}
}

bool GameWindow::isPaused()
{
	return paused;
}

int GameWindow::getPlayerX()
{
	if (isPlayerAlive()) return player->getX();
	else return -1;
}

int GameWindow::getPlayerY()
{
	if (isPlayerAlive())  return player->getY();
	else return -1;
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
	mouseX = evt.GetX();
	mouseY = evt.GetY();
}
