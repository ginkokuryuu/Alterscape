#include "GameFrame.h"
#include "GameWindow.h"
wxBEGIN_EVENT_TABLE(GameFrame, wxFrame)
EVT_MENU(wxID_EXIT, GameFrame::OnQuit)
EVT_MENU(wxID_ABOUT, GameFrame::OnAbout)
wxEND_EVENT_TABLE()

GameFrame::GameFrame(const wxString & title)
	: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER & ~wxMAXIMIZE_BOX)
{
	SetInitialSize(wxDefaultSize);
#if wxUSE_MENUS
	wxMenu *fileMenu = new wxMenu;
	wxMenu *helpMenu = new wxMenu;
	helpMenu->Append(wxID_ABOUT, "&About\tF1", "Show about dialog");
	fileMenu->Append(wxID_EXIT, "E&xit\tAlt-X", "Quit this program");
	wxMenuBar *menuBar = new wxMenuBar();
	menuBar->Append(fileMenu, "&File");
	menuBar->Append(helpMenu, "&Help");
	SetMenuBar(menuBar);
#endif
	gamewindow = new GameWindow(this);
	gamewindow->SetInitialSize(wxDefaultSize);
}
void GameFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
	Close(true);
}
void GameFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
	wxMessageBox(wxString::Format
	(
		"Welcome to %s!\n"
		"\n"
		"This is the minimal wxWidgets sample\n"
		"running under %s.",
		wxVERSION_STRING,
		wxGetOsDescription()
	),
		"About wxWidgets minimal sample",
		wxOK | wxICON_INFORMATION,
		this);
}