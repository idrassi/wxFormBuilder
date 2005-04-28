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


#include "menubar.h"
#include "wx/debug.h"

Menubar::Menubar() : wxPanel()
{
    m_sizer = NULL;
}

Menubar::Menubar(wxWindow *parent, int id, const wxPoint& pos, const wxSize &size,
            long style, const wxString &name) : wxPanel(parent, id, pos, size, style, name)
{
    m_sizer = new wxBoxSizer(wxHORIZONTAL);
    SetSizer(m_sizer);    
}

Menubar::~Menubar()
{
    while (!m_menus.empty())
    {
        wxMenu *menu = m_menus[0];
        delete menu;
        m_menus.erase(m_menus.begin());
    }
}

void Menubar::AppendMenu(const wxString& name, wxMenu *menu)
{
    wxStaticText *st = new wxStaticText(this, -1, name);
    st->PushEventHandler(new MenuEvtHandler(st, menu));
    m_sizer->Add(st, 0, wxRIGHT | wxLEFT, 5);
    Layout();
    m_menus.push_back(menu);    
}

wxMenu* Menubar::GetMenu(int i)
{
    wxASSERT(i < int(m_menus.size()));
    return m_menus[i];
}

int Menubar::GetMenuCount()
{
    return m_menus.size();
}

wxMenu* Menubar::Remove(int i)
{
    return NULL; //TODO: Implementar Menubar::Remove    
}

BEGIN_EVENT_TABLE(MenuEvtHandler, wxEvtHandler)
    EVT_LEFT_DOWN(MenuEvtHandler::OnMouseEvent) 
END_EVENT_TABLE()

MenuEvtHandler::MenuEvtHandler(wxStaticText *st, wxMenu *menu)
{
    wxASSERT(menu != NULL && st != NULL);

    m_label = st;
    m_menu = menu;
}

void MenuEvtHandler::OnMouseEvent(wxMouseEvent& event)
{ 
    m_label->PopupMenu(m_menu, 0, m_label->GetSize().y + 3);
}


