#pragma once
#include "wx/wxprec.h"
#include "wx/wx.h"
class MyWindow;
class MyFrame :
	public wxFrame
{
public:
	MyFrame(const wxString& title);
	void OnQuit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
private:
	MyWindow *window;
	wxDECLARE_EVENT_TABLE();
};
