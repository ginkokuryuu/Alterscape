#pragma once
#include "wx/wxprec.h"
#include "wx/wx.h"
#include "GameWindow.h"
#include "MenuWindow.h"
#include "GameOverWindow.h"
class GameFrame :
	public wxFrame
{
public:
	GameFrame(const wxString& title);
	void OnQuit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void LoadGame();
	void GameOver(int, int, int, int);
	void LoadMenu();
private:
	GameWindow *gamewindow;
	MenuWindow *menuwindow;
	GameOverWindow *gameOverWindow;
	wxDECLARE_EVENT_TABLE();
};
