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
	LoadAbout();
}

MenuWindow::~MenuWindow()
{
	delete backGround;
	delete about;
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
	wxMessageOutputDebug().Printf("%d %d", mousePos.x, mousePos.y);
	float scaleY = wxGetDisplaySize().GetHeight() / 1080.0;
	float scaleX = wxGetDisplaySize().GetWidth() / 1920.0;
	if (!aboutState) {
		if (mousePos.x > 64 * scaleX && mousePos.x < 302 * scaleX) {
			if (mousePos.y > 537 * scaleY && mousePos.y < 618 * scaleY) {
				parentWindow->LoadGame();
				wxMessageOutputDebug().Printf("Play");
			}
			else if (mousePos.y > 647 * scaleY && mousePos.y < 728 * scaleY) {
				wxClientDC dc(this);
				dc.DrawBitmap(*about, wxPoint((wxGetDisplaySize().GetWidth() - 1569) / 2 * scaleX, (wxGetDisplaySize().GetHeight() - 883) / 2 * scaleY));
				aboutState = true;
				wxMessageOutputDebug().Printf("About");
			}
			else if (mousePos.y > 757 * scaleY && mousePos.y < 838 * scaleY) {
				this->GetParent()->Close(true);
				wxMessageOutputDebug().Printf("Exit");
			}
		}
	}
	else if (mousePos.x < 173 * scaleX || mousePos.x > 1743 * scaleX || mousePos.y<98*scaleY || mousePos.y>982*scaleY || (mousePos.x >= 1600 * scaleX && mousePos.x <= 1661 * scaleX && mousePos.y >= 113 * scaleY && mousePos.y <= 171 * scaleY)) {
		Refresh();
		aboutState = false;
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

void MenuWindow::LoadAbout()
{
	float scaleY = wxGetDisplaySize().GetHeight() / 1080.0;
	float scaleX = wxGetDisplaySize().GetWidth() / 1920.0;
	wxLogNull pls;
	wxStandardPaths &stdPaths = wxStandardPaths::Get();
	wxString path = stdPaths.GetExecutablePath();
	path = wxFileName(path).GetPath() + wxT("\\res\\About.png");
	wxMessageOutputDebug().Printf("LOAD ABOUT");
	wxImage image(path);
	about = new wxBitmap(image.Scale(1569*scaleX, 883*scaleY));
}
