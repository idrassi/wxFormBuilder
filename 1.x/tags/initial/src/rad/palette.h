///////////////////////////////////////////////////////////////////////////////
//
// wxFormBuilder - A Visual Dialog Editor for wxWidgets.
// Copyright (C) 2005 Jos� Antonio Hurtado
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
// Written by Jos� Antonio Hurtado - joseantonio.hurtado@hispalinux.es
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __PALETTE__
#define __PALETTE__

#include <wx/wx.h>
#include <wx/notebook.h>
#include "rad/appobserver.h"

class Palette : public DataObserver, public wxPanel
{
 private:
  wxNotebook *m_notebook;
   
 public:
  Palette(wxWindow *parent,int id);

  /**
   * Crea la paleta, previamente se ha debido configurar el objeto
   * DataObservable.
   */
  void Create();
  

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

class ToolPanel : public DataObserver, public wxPanel
{
 protected:
   DECLARE_EVENT_TABLE()
   
 public:
   ToolPanel(wxWindow *parent, int id);
   void OnSaveFile(wxCommandEvent &event);

};  


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

#endif //__PALETTE__
