#include "app.h"
#include "mainframe.h"

IMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
	MainFrame* frame = new MainFrame(0L);
	frame->Show();
	return true;
}
