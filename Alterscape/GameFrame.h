#pragma once
#include "wx/wxprec.h"
#include "wx/wx.h"
#include "GameWindow.h"
class GameFrame :
	public wxFrame
{
public:
	GameFrame(const wxString& title);
	void OnQuit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
private:
	GameWindow *gamewindow;
	wxDECLARE_EVENT_TABLE();
};
