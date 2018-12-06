#include "GameFrame.h"
wxBEGIN_EVENT_TABLE(GameFrame, wxFrame)
EVT_MENU(wxID_EXIT, GameFrame::OnQuit)
EVT_MENU(wxID_ABOUT, GameFrame::OnAbout)
wxEND_EVENT_TABLE()

GameFrame::GameFrame(const wxString & title)
	: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER & ~wxMAXIMIZE_BOX)
{
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
	
	menuwindow = new MenuWindow(this);
	menuwindow->SetInitialSize(wxGetDisplaySize());
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

void GameFrame::LoadGame()
{
	if(gameOverWindow != nullptr)
		gameOverWindow->Show(false);
	menuwindow->Show(false);
	if (gamewindow != nullptr) delete gamewindow;
	gamewindow = new GameWindow(this);
	gamewindow->Show(true);
	gamewindow->SetInitialSize(wxGetDisplaySize());
	gamewindow->SetFocus();
}

void GameFrame::GameOver(int score, int kill, int highScore, int highKill)
{
	wxMessageOutputDebug().Printf("%d %d %d %d", score, kill, highScore, highKill);
	menuwindow->Show(false);
	if (gamewindow != nullptr)
	gamewindow->Show(false);
	if (gameOverWindow != nullptr) delete gameOverWindow;
	gameOverWindow = new GameOverWindow(this, score, kill, highScore, highKill);
	gameOverWindow->Show(true);
	gameOverWindow->SetInitialSize(wxGetDisplaySize());
	gameOverWindow->SetFocus();
}

void GameFrame::LoadMenu()
{
	menuwindow->SetFocus();
	if (gameOverWindow != nullptr)
		gameOverWindow->Show(false);
	if (gamewindow != nullptr)
		gamewindow->Show(false);
	menuwindow->Show(true);
}
