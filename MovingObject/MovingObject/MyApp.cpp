#include "MyApp.h"

bool MyApp::OnInit()
{
	if (!wxApp::OnInit())
		return false;
	MyFrame *frame = new MyFrame("Ball Movement Handler");
	frame->SetClientSize(1024, 768);
	frame->Centre();
	frame->Show(true);

	return true;
}
