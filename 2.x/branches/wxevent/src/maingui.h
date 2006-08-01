#ifndef __MAINGUI__
#define __MAINGUI__

#include "wx/wxprec.h"



class MyApp : public wxApp
{
private:
  wxLog * m_old_log;
  wxLogWindow * m_log;
  std::vector< wxEvtHandler* > m_handlers;

public:

  virtual bool OnInit();
  void NotifyEvent( wxFBEvent& event );
  void AddHandler( wxEvtHandler* handler );
};

DECLARE_APP(MyApp)

#endif //__MAINGUI__
