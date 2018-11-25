#pragma once
#include "wx/wxprec.h"
#include "wx/wx.h"
#include "GameWindow.h"
#include "MenuWindow.h"
class GameFrame :
	public wxFrame
{
public:
	GameFrame(const wxString& title);
	void OnQuit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void LoadGame();
	void GameOver();
private:
	GameWindow *gamewindow;
	MenuWindow *menuwindow;
	wxDECLARE_EVENT_TABLE();
};
