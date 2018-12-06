#pragma once
#include "wx/wx.h"
#include "wx/dcbuffer.h"
#include "wx/stdpaths.h"
#include "wx/filename.h"

class GameFrame;

class GameOverWindow : public wxWindow
{
public:
	GameOverWindow(wxFrame *frame, int , int, int, int);
	~GameOverWindow();
	void RenderFrame(wxPaintEvent &event);
	void DrawUI(wxAutoBufferedPaintDC &dc);
	void OnTimer(wxTimerEvent &event);
	void LoadBackground();
private:
	GameFrame *parentWindow;
	wxTimer *timer;
	wxBitmap *backGround;
	int score, highScore, kill, highKill;
	DECLARE_EVENT_TABLE()
};

