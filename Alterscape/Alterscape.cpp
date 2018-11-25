#include "Alterscape.h"

bool Alterscape::OnInit()
{
	if (!wxApp::OnInit())
		return false;
	wxImage::AddHandler(new wxPNGHandler);
	GameFrame *mainframe = new GameFrame("Alterscape");
	/*mainframe->SetClientSize(1024, 768);
	mainframe->Centre();
	mainframe->Show(true);*/
	mainframe->ShowFullScreen(true);
	return true;
}
