#include "GameOverWindow.h"
#include "GameFrame.h"
#include <stdlib.h>
#include <sstream>

BEGIN_EVENT_TABLE(GameOverWindow, wxWindow)
	EVT_PAINT(GameOverWindow::RenderFrame)
	EVT_TIMER(2018, GameOverWindow::OnTimer)
END_EVENT_TABLE()

GameOverWindow::GameOverWindow(wxFrame *frame, int score, int kill, int highScore, int highKill) 
	: wxWindow(frame, wxID_ANY)
{
	parentWindow = (GameFrame*)frame;
	SetBackgroundStyle(wxBG_STYLE_PAINT);
	SetBackgroundColour(wxColor(*wxBLUE));
	LoadBackground();
	this->score = score;
	this->kill = kill;
	this->highKill = highKill;
	this->highScore = highScore;
	timer = new wxTimer(this, 2018);
	timer->Start(5000);
}


GameOverWindow::~GameOverWindow()
{
	delete backGround;
	delete timer;
}

void GameOverWindow::RenderFrame(wxPaintEvent & event)
{
	wxMessageOutputDebug().Printf("PAINT EVENT");
	wxAutoBufferedPaintDC pdc(this);
	if (backGround != nullptr) {
		wxMessageOutputDebug().Printf("TOOBBB");
		pdc.DrawBitmap(*backGround, wxPoint(0, 0));
	}
	DrawUI(pdc);
}

void GameOverWindow::DrawUI(wxAutoBufferedPaintDC & dc)
{
	float scaleY = wxGetDisplaySize().GetHeight() / 1080.0;
	float scaleX = wxGetDisplaySize().GetWidth() / 1920.0;
	dc.SetTextForeground(wxColour(255, 255, 255));
	dc.SetFont(wxFont(90 * scaleY, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
	std::wstringstream gameOver;
	gameOver << "Game over..." << std::ends;
	dc.DrawText(gameOver.str().c_str(), wxPoint(602 * scaleX, 433 * scaleY));
	dc.SetFont(wxFont(30 * scaleY, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
	std::wstringstream pts;
	pts << "You survived " << score << "pts" << std::ends;
	dc.DrawText(pts.str().c_str(), wxPoint(770 * scaleY, 569 * scaleY));
	dc.SetFont(wxFont(20 * scaleY, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
	std::wstringstream ko;
	ko << "and killed " << kill << " enemy(s)" << std::ends;
	dc.DrawText(ko.str().c_str(), wxPoint(818 * scaleY, 630 * scaleY));
	std::wstringstream hsc;
	hsc << "while the highscore is " << highScore << " pts" << std::ends;
	dc.DrawText(hsc.str().c_str(), wxPoint(1488 * scaleY, 970 * scaleY));
	std::wstringstream hko;
	hko << "and killed " << highKill << " enemy(s)" << std::ends;
	dc.DrawText(hko.str().c_str(), wxPoint(1569 * scaleY, 1020 * scaleY));
}

void GameOverWindow::OnTimer(wxTimerEvent & event)
{
	timer->Stop();
	parentWindow->LoadMenu();
}

void GameOverWindow::LoadBackground()
{
	wxLogNull pls;
	wxStandardPaths &stdPaths = wxStandardPaths::Get();
	wxString path = stdPaths.GetExecutablePath();
	path = wxFileName(path).GetPath() + wxT("\\res\\Background.png");
	wxMessageOutputDebug().Printf("LOAD BACKGROUNDs");
	wxImage image(path);
	backGround = new wxBitmap(image.Scale(wxGetDisplaySize().GetWidth(), wxGetDisplaySize().GetHeight()));
}