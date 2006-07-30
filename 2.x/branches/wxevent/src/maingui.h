#ifndef __MAINGUI__
#define __MAINGUI__

#include "wx/wxprec.h"



class MyApp : public wxApp
{
private:
  wxLog * m_old_log;
  wxLogWindow * m_log;
  std::vector< wxEvtHandler* > m_handlers;
  DECLARE_EVENT_TABLE()

public:

  virtual bool OnInit();
  void NotifyEvent( wxfbEvent& event );
  void AddHandler( wxEvtHandler* handler );
};

DECLARE_APP(MyApp)

#endif //__MAINGUI__
