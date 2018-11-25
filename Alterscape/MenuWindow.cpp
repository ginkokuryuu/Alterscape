#include "MenuWindow.h"
#include "GameFrame.h"

BEGIN_EVENT_TABLE(MenuWindow, wxWindow)
EVT_PAINT(MenuWindow::RenderFrame)
EVT_LEFT_DOWN(MenuWindow::OnClick)
END_EVENT_TABLE()

MenuWindow::MenuWindow(wxFrame * frame)
	: wxWindow(frame, wxID_ANY)
{
	wxMessageOutputDebug().Printf("NGENTOODDD");
	parentWindow = (GameFrame*)frame;
	SetBackgroundStyle(wxBG_STYLE_PAINT);
	SetBackgroundColour(wxColor(*wxBLUE));
	pngHandler = new wxPNGHandler();
	wxImage::AddHandler(pngHandler);
	LoadBackground();

}

MenuWindow::~MenuWindow()
{
	delete backGround;
}

void MenuWindow::RenderFrame(wxPaintEvent & event)
{
	wxMessageOutputDebug().Printf("PAINT EVENT");
	wxAutoBufferedPaintDC pdc(this);
	if (backGround != nullptr) {
		wxMessageOutputDebug().Printf("NGENTOOBBB");
		pdc.DrawBitmap(*backGround, wxPoint(0, 0));
	}
}

void MenuWindow::OnClick(wxMouseEvent & event)
{

	wxPoint mousePos = event.GetPosition();
	if (mousePos.x > 64 && mousePos.x < 302) {
		if (mousePos.y > 537 && mousePos.y < 618) {
			parentWindow->LoadGame();
			wxMessageOutputDebug().Printf("Play");
		}
		else if (mousePos.y > 647 && mousePos.y < 728) {
			wxMessageOutputDebug().Printf("About");
		}
		else if (mousePos.y > 757 && mousePos.y < 838) {
			this->GetParent()->Close(true);
			wxMessageOutputDebug().Printf("Exit");
		}
	}
}

void MenuWindow::LoadBackground()
{
	wxStandardPaths &stdPaths = wxStandardPaths::Get();
	wxString path = stdPaths.GetExecutablePath();
	path = wxFileName(path).GetPath() + wxT("\\MainMenu.png");
	wxMessageOutputDebug().Printf("LOAD BACKGEOUND");
	wxImage image(path);
	backGround = new wxBitmap(image.Scale(wxGetDisplaySize().GetWidth(), wxGetDisplaySize().GetHeight()));
}
