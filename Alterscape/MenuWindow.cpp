#include "MenuWindow.h"
#include "GameFrame.h"

BEGIN_EVENT_TABLE(MenuWindow, wxWindow)
EVT_PAINT(MenuWindow::RenderFrame)
EVT_LEFT_DOWN(MenuWindow::OnClick)
END_EVENT_TABLE()

MenuWindow::MenuWindow(wxFrame * frame)
	: wxWindow(frame, wxID_ANY)
{
	wxMessageOutputDebug().Printf("DDD");
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
		wxMessageOutputDebug().Printf("TOOBBB");
		pdc.DrawBitmap(*backGround, wxPoint(0, 0));
	}
}

void MenuWindow::OnClick(wxMouseEvent & event)
{
	wxPoint mousePos = event.GetPosition();
	float scale = wxGetDisplaySize().GetHeight() / 1080.0;
	if (mousePos.x > 64 * scale && mousePos.x < 302 * scale) {
		if (mousePos.y > 537 * scale && mousePos.y < 618 * scale) {
			parentWindow->LoadGame();
			wxMessageOutputDebug().Printf("Play");
		}
		else if (mousePos.y > 647 * scale && mousePos.y < 728 * scale) {
			wxMessageOutputDebug().Printf("About");
		}
		else if (mousePos.y > 757 * scale && mousePos.y < 838 * scale) {
			this->GetParent()->Close(true);
			wxMessageOutputDebug().Printf("Exit");
		}
	}
}

void MenuWindow::LoadBackground()
{
	wxLogNull pls;
	wxStandardPaths &stdPaths = wxStandardPaths::Get();
	wxString path = stdPaths.GetExecutablePath();
	path = wxFileName(path).GetPath() + wxT("\\res\\Main_Menu.png");
	wxMessageOutputDebug().Printf("LOAD BACKGROUND");
	wxImage image(path);
	backGround = new wxBitmap(image.Scale(wxGetDisplaySize().GetWidth(), wxGetDisplaySize().GetHeight()));
}
