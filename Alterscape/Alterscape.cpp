#include "Alterscape.h"

bool Alterscape::OnInit()
{
	if (!wxApp::OnInit())
		return false;
	wxImage::AddHandler(new wxPNGHandler);
	GameFrame *mainframe = new GameFrame("Alterscape");
	mainframe->ShowFullScreen(true);
	return true;
}
