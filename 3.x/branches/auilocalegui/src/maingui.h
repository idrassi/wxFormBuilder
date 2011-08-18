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
// Written by
//   José Antonio Hurtado - joseantonio.hurtado@gmail.com
//   Juan Antonio Ortega  - jortegalalmolda@gmail.com
//
///////////////////////////////////////////////////////////////////////////////
#ifndef __MAINGUI__
#define __MAINGUI__

#include <wx/app.h>
#include <wx/intl.h>

class MainFrame;

class wxFormBuilderApp : public wxApp
{
private:
  void SelectLanguage( int lang );

  wxLog *       m_old_log;
  wxLogWindow * m_log;

  MainFrame *   m_frame;
  wxLocale      m_locale;

public:
  bool OnInit();
  #if wxUSE_ON_FATAL_EXCEPTION && wxUSE_STACKWALKER
  void OnFatalException();
  #endif
  int OnRun();
  int OnExit();
  ~wxFormBuilderApp();

  /** Add locale support from a component **/
  void AddPluginLocaleCatalog( const wxString& catalog ) { m_locale.AddCatalog( catalog ); }

  #ifdef __WXMAC__
  wxString m_mac_file_name;
  void MacOpenFile(const wxString &fileName);
  #endif
};

DECLARE_APP(wxFormBuilderApp)

#endif //__MAINGUI__
