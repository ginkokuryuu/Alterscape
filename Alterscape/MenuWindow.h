#pragma once
#include "wx/wx.h"
#include "wx/dcbuffer.h"
#include "wx/stdpaths.h"
#include "wx/filename.h"

class GameFrame;

class MenuWindow : public wxWindow
{
public:
	MenuWindow(wxFrame *frame);
	~MenuWindow();
	void RenderFrame(wxPaintEvent &event);
	void OnClick(wxMouseEvent &event);
	void LoadBackground();
	void LoadAbout();
private:
	bool aboutState = false;
	GameFrame *parentWindow;
	wxBitmap *backGround;
	wxBitmap *about;
	wxPNGHandler *pngHandler;
	DECLARE_EVENT_TABLE()
};

