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

#ifndef __PALETTE__
#define __PALETTE__

#include <wx/wx.h>

#ifdef WXFB_USE_AUIBOOK
    #include <wx/aui/auibook.h>
#else
    #include <wx/wxFlatNotebook/wxFlatNotebook.h>
#endif

#ifdef WXFB_USE_AUITOOLBAR
    #include <wx/aui/auibar.h>
#else
    #include <wx/toolbar.h>
    #include <wx/spinbutt.h>
#endif

#include <vector>
#include <utils/wxfbdefs.h>
#include <model/database.h>

#ifdef WXFB_USE_AUITOOLBAR
typedef std::vector<wxAuiToolBar*> ToolbarVector;
#else
typedef std::vector<wxToolBar*> ToolbarVector;
#endif

class wxFbPalette : public wxPanel
{
private:

#ifdef WXFB_USE_AUIBOOK
  wxAuiNotebook *m_notebook;
#else
  wxFlatNotebook *m_notebook;
  wxFlatNotebookImageList m_icons;
#endif

  ToolbarVector m_tv;
  static wxWindowID nextId;

#ifdef WXFB_USE_AUITOOLBAR
  void PopulateToolbar( PObjectPackage pkg, wxAuiToolBar *toolbar );
#else
  std::vector<int> m_posVector; // Used by wxSpinCtrl, not needed in auibar
  void PopulateToolbar( PObjectPackage pkg, wxToolBar *toolbar );
#endif

#if 0
  void arrangeTabOrder( std::vector< wxWindow* > &pages ); // ifdef WXFB_USE_AUIBOOK TODO: set the wx version when it will be fixed
#endif

  DECLARE_EVENT_TABLE()

public:
  wxFbPalette(wxWindow *parent,int id);
  ~wxFbPalette();

  /**
   * Crea la paleta, previamente se ha debido configurar el objeto
   * DataObservable.
   */
  void Create();

#ifndef WXFB_USE_AUITOOLBAR
  void OnSpinUp(wxSpinEvent& e);
  void OnSpinDown(wxSpinEvent& e);
#endif

  void OnButtonClick(wxCommandEvent &event);
};
/*
class PaletteButton : public wxBitmapButton
{
 private:
  wxString m_name;
  DECLARE_EVENT_TABLE()

 public:
  PaletteButton(wxWindow *parent, const wxBitmap &bitmap, wxString &name);
  void OnButtonClick(wxCommandEvent &event);
};

*/
/*
class ToolPanel : public wxPanel, public DataObserver
{
 protected:
   DECLARE_EVENT_TABLE()

 public:
   ToolPanel(wxWindow *parent, int id);
   void OnSaveFile(wxCommandEvent &event);

};  */

/*
class PaletteButtonEventHandler : public wxEvtHandler
{
 private:
  wxString m_name;
  DECLARE_EVENT_TABLE()
  DataObservable *m_data;

 public:
  PaletteButtonEventHandler(wxString name, DataObservable *data);
  void OnButtonClick(wxCommandEvent &event);
};
*/
#endif //__PALETTE__
