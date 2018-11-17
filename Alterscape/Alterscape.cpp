#include "Alterscape.h"

bool Alterscape::OnInit()
{
	if (!wxApp::OnInit())
		return false;
	GameFrame *mainframe = new GameFrame("Alterscape");
	mainframe->SetClientSize(1024, 768);
	mainframe->Centre();
	mainframe->Show(true);

	return true;
}
