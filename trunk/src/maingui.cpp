///////////////////////////////////////////////////////////////////////////////
//
// wxFormBuilder - A Visual Dialog Editor for wxWidgets.
// Copyright (C) 2005 José Antonio Hurtado
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//
// Written by José Antonio Hurtado - joseantonio.hurtado@hispalinux.es
//
///////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
  #include "wx/wx.h"
#endif

#include <wx/splash.h>
#include "rad/mainframe.h"
#include "rad/appdata.h"

#if defined(__WXGTK__) || defined(__WXMOTIF__) || defined(__WXMAC__) || defined(__WXMGL__) || defined(__WXX11__)
    #include "wxwin32x32.xpm"
#endif


class MyApp : public wxApp
{
private:
  wxLog * m_old_log;
  wxLogWindow * m_log;
  
public:

  virtual bool OnInit();
};


IMPLEMENT_APP(MyApp)


bool MyApp::OnInit()
{
  wxInitAllImageHandlers();

  wxBitmap bitmap;    
  if (bitmap.LoadFile(wxT("splash.png"), wxBITMAP_TYPE_PNG))
  {
      new wxSplashScreen(bitmap, wxSPLASH_CENTRE_ON_SCREEN|wxSPLASH_TIMEOUT,
          2000, NULL, -1, wxDefaultPosition, wxDefaultSize,
          wxSIMPLE_BORDER|wxSTAY_ON_TOP);
  }
  
  SetVendorName(_T("wxFormBuilder"));
  SetAppName(_T("wxFormBuilder"));

  #ifndef __WXMSW__
  wxSleep(2);
  #endif

  wxYield();

  #ifdef __WXFB_DEBUG__
  m_log = new wxLogWindow(NULL,wxT("Logging"));
  m_old_log = wxLog::SetActiveTarget(m_log);
  #endif //__WXFB_DEBUG__


  DataObservable *data = new ApplicationData();
  
  MainFrame *frame = new MainFrame(data, NULL);
  frame->Show(TRUE); 

  #ifdef __WXFB_DEBUG__    
  frame->AddChild(m_log->GetFrame());
  #endif //__WXFB_DEBUG__
  
  data->NewProject();
  //data->LoadProject(wxT("projects/example/example.xml"));
  
  return TRUE;
}

