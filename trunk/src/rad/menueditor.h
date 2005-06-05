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
#ifndef __MENUEDITOR__
#define __MENUEDITOR__
#include <wx/wx.h>
#include <wx/button.h>
#include <wx/listctrl.h>

/**
 * Class MenuEditor
 */
class MenuEditor : public wxDialog
{
  private:
    long GetSelectedItem();
  
  protected:
    wxListCtrl *m_menuList;
    wxTextCtrl *m_tcId;
    wxTextCtrl *m_tcLabel;
    wxTextCtrl *m_tcName;
    wxTextCtrl *m_tcHelpString;
    
    DECLARE_EVENT_TABLE()
  
  public:
    
    MenuEditor(wxWindow *parent, int id = -1);
    void OnAddMenuItem(wxCommandEvent& e);
    void OnAddSeparator(wxCommandEvent& e);
    void OnRemoveMenuItem(wxCommandEvent& e);
    void OnMenuDown(wxCommandEvent& e);
    void OnMenuLeft(wxCommandEvent& e);
    void OnMenuRight(wxCommandEvent& e);
    void OnMenuUp(wxCommandEvent& e);
};

#endif //__menueditor__

