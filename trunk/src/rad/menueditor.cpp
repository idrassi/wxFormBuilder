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
#include "menueditor.h"

#define ID_DEFAULT -1 // Default
#define ID_ADDMENUITEM 1000
#define ID_ADDSEPARATOR 1001
#define ID_MENUDOWN 1002
#define ID_MENULEFT 1003
#define ID_MENURIGHT 1004
#define ID_MENUUP 1005
#define ID_REMOVEMENUITEM 1006

#define IDENTATION 4

BEGIN_EVENT_TABLE(MenuEditor, wxDialog)
    EVT_BUTTON(ID_ADDMENUITEM, MenuEditor::OnAddMenuItem)
    EVT_BUTTON(ID_ADDSEPARATOR, MenuEditor::OnAddSeparator)
    EVT_BUTTON(ID_REMOVEMENUITEM, MenuEditor::OnRemoveMenuItem)
    EVT_BUTTON(ID_MENUDOWN, MenuEditor::OnMenuDown)
    EVT_BUTTON(ID_MENULEFT, MenuEditor::OnMenuLeft)
    EVT_BUTTON(ID_MENURIGHT, MenuEditor::OnMenuRight)
    EVT_BUTTON(ID_MENUUP, MenuEditor::OnMenuUp)
    EVT_UPDATE_UI_RANGE(ID_MENUDOWN, ID_MENUUP, MenuEditor::OnUpdateMovers)
END_EVENT_TABLE()

MenuEditor::MenuEditor(wxWindow *parent, int id) : wxDialog(parent,id,_T("Menu Editor"),wxDefaultPosition,wxDefaultSize)
{
  wxBoxSizer *mainSizer;
  mainSizer = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *sizerTop;
  sizerTop = new wxBoxSizer(wxHORIZONTAL);
  m_menuList = new wxListCtrl(this,ID_DEFAULT,wxDefaultPosition,wxDefaultSize,wxLC_REPORT | wxLC_SINGLE_SEL);
  m_menuList->InsertColumn(0, _T("Label"), wxLIST_FORMAT_LEFT, 200);
  sizerTop->Add(m_menuList, 1, wxALL|wxEXPAND, 5);
  wxStaticBoxSizer *sizer1;
  sizer1 = new wxStaticBoxSizer(new wxStaticBox(this, -1, wxT("Menu item")), wxVERTICAL);
  wxFlexGridSizer *sizer11;
  sizer11 = new wxFlexGridSizer(4,2,0,0);
  wxStaticText *m_stId;
  m_stId = new wxStaticText(this,ID_DEFAULT,wxT("Id"),wxDefaultPosition,wxDefaultSize,0);
  sizer11->Add(m_stId, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5);
  m_tcId = new wxTextCtrl(this,ID_DEFAULT,wxT(""),wxDefaultPosition,wxDefaultSize,0);
  sizer11->Add(m_tcId, 0, wxALL, 5);
  wxStaticText *m_stLabel;
  m_stLabel = new wxStaticText(this,ID_DEFAULT,wxT("Label"),wxDefaultPosition,wxDefaultSize,0);
  sizer11->Add(m_stLabel, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5);
  m_tcLabel = new wxTextCtrl(this,ID_DEFAULT,wxT(""),wxDefaultPosition,wxDefaultSize,0);
  sizer11->Add(m_tcLabel, 0, wxALL, 5);
  wxStaticText *m_stName;
  m_stName = new wxStaticText(this,ID_DEFAULT,wxT("Name"),wxDefaultPosition,wxDefaultSize,0);
  sizer11->Add(m_stName, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5);
  m_tcName = new wxTextCtrl(this,ID_DEFAULT,wxT(""),wxDefaultPosition,wxDefaultSize,0);
  sizer11->Add(m_tcName, 0, wxALL, 5);
  wxStaticText *m_stHelpString;
  m_stHelpString = new wxStaticText(this,ID_DEFAULT,wxT("Help String"),wxDefaultPosition,wxDefaultSize,0);
  sizer11->Add(m_stHelpString, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5);
  m_tcHelpString = new wxTextCtrl(this,ID_DEFAULT,wxT(""),wxDefaultPosition,wxDefaultSize,0);
  sizer11->Add(m_tcHelpString, 0, wxALL, 5);
  sizer1->Add(sizer11, 0, wxEXPAND, 5);
  wxBoxSizer *sizer4;
  sizer4 = new wxBoxSizer(wxHORIZONTAL);
  wxButton *m_bAdd;
  m_bAdd = new wxButton(this,ID_ADDMENUITEM,wxT("&Add"),wxDefaultPosition,wxDefaultSize,0);
  sizer4->Add(m_bAdd, 0, wxALL, 5);
  wxButton *m_bRemove;
  m_bRemove = new wxButton(this,ID_REMOVEMENUITEM,wxT("&Remove"),wxDefaultPosition,wxDefaultSize,0);
  sizer4->Add(m_bRemove, 0, wxALL, 5);
  sizer1->Add(sizer4, 0, wxEXPAND, 5);
  wxButton *m_bAddSep;
  m_bAddSep = new wxButton(this,ID_ADDSEPARATOR,wxT("Add &Separator"),wxDefaultPosition,wxDefaultSize,0);
  sizer1->Add(m_bAddSep, 0, wxALL|wxEXPAND, 5);
  sizerTop->Add(sizer1, 0, wxALL | wxEXPAND, 5);
  mainSizer->Add(sizerTop, 1, wxEXPAND, 5);
  wxBoxSizer *sizerMoveButtons;
  sizerMoveButtons = new wxBoxSizer(wxHORIZONTAL);
  wxButton *m_bUp;
  m_bUp = new wxButton(this,ID_MENUUP,wxT("&Up"),wxDefaultPosition,wxDefaultSize,0);
  sizerMoveButtons->Add(m_bUp, 0, wxALL, 5);
  wxButton *m_bDown;
  m_bDown = new wxButton(this,ID_MENUDOWN,wxT("&Down"),wxDefaultPosition,wxDefaultSize,0);
  sizerMoveButtons->Add(m_bDown, 0, wxALL, 5);
  wxButton *m_bLeft;
  m_bLeft = new wxButton(this,ID_MENULEFT,wxT("<"),wxDefaultPosition,wxDefaultSize,0);
  sizerMoveButtons->Add(m_bLeft, 0, wxALL, 5);
  wxButton *m_bRight;
  m_bRight = new wxButton(this,ID_MENURIGHT,wxT(">"),wxDefaultPosition,wxDefaultSize,0);
  sizerMoveButtons->Add(m_bRight, 0, wxALL, 5);
  mainSizer->Add(sizerMoveButtons, 0, wxEXPAND, 5);
  wxBoxSizer *sizerOkCancel;
  sizerOkCancel = new wxBoxSizer(wxHORIZONTAL);
  wxButton *m_bOk;
  m_bOk = new wxButton(this,wxID_OK,wxT("OK"),wxDefaultPosition,wxDefaultSize,0);
  sizerOkCancel->Add(m_bOk, 0, wxALL, 5);
  wxButton *m_bCancel;
  m_bCancel = new wxButton(this,wxID_CANCEL,wxT("Cancel"),wxDefaultPosition,wxDefaultSize,0);
  sizerOkCancel->Add(m_bCancel, 0, wxALL, 5);
  mainSizer->Add(sizerOkCancel, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
  this->SetSizer(mainSizer);
  this->SetAutoLayout(true);
  this->Layout();
  SetClientSize(540, 293);
  CenterOnScreen();
}

long MenuEditor::GetSelectedItem()
{
    return m_menuList->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
}

int MenuEditor::GetItemIdentation(long n)
{
    wxString label = m_menuList->GetItemText(n);
    size_t curIdent = 0;
    while (curIdent < label.Len() && label[curIdent] == ' ') curIdent++;
    curIdent /= IDENTATION;
    
    return (int)curIdent;
}

void MenuEditor::AddItem(const wxString& label)
{
    int sel = GetSelectedItem();
    int identation = 0;
    if (sel >= 0) identation = GetItemIdentation(sel);
    wxString labelAux =label;
    labelAux.Trim(true);
    labelAux.Trim(false);
    if (sel < 0) sel = m_menuList->GetItemCount() - 1;
    long index = m_menuList->InsertItem(sel + 1, wxString(' ', identation * IDENTATION) + labelAux);
    m_menuList->SetItemState(index, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
}

void MenuEditor::OnAddMenuItem(wxCommandEvent& e)
{
    AddItem(m_tcLabel->GetValue());
}

void MenuEditor::OnAddSeparator(wxCommandEvent& e)
{
    AddItem(_T("---"));
}

void MenuEditor::OnRemoveMenuItem(wxCommandEvent& e)
{
    long sel = GetSelectedItem();
    if (sel < m_menuList->GetItemCount() - 1)
    {
        int curIdent = GetItemIdentation(sel);
        int nextIdent = GetItemIdentation(sel + 1);
        if (nextIdent > curIdent)
        {
            int res = wxMessageBox(
                _T("The children of the selected item will be eliminated too. Are you sure you want to continue?"), 
                _T("wxFormBuilder"), wxYES_NO);
            if (res == wxYES)
            {
                long item = sel + 1;
                while (item < m_menuList->GetItemCount() && GetItemIdentation(item) > curIdent)
                    m_menuList->DeleteItem(item);
                m_menuList->DeleteItem(sel);                    
            }
        }else
            m_menuList->DeleteItem(sel);
    }else
        m_menuList->DeleteItem(sel);  
}

void MenuEditor::OnMenuLeft(wxCommandEvent& e)
{
    int sel = GetSelectedItem();
    int curIdent = GetItemIdentation(sel) - 1;
    
    if (curIdent < 0)
        return;
    
    wxString label = m_menuList->GetItemText(sel);
    label.Trim(true);
    label.Trim(false);
    label = wxString(' ', curIdent * IDENTATION) + label;
    m_menuList->SetItemText(sel, label);
}

void MenuEditor::OnMenuRight(wxCommandEvent& e)
{
    int sel = GetSelectedItem();
    int curIdent = GetItemIdentation(sel) + 1;
    int parentIdent = sel > 0 ? GetItemIdentation(sel - 1) : -1;
    
    if (parentIdent == -1 || abs(curIdent - parentIdent) > 1)
        return;
    
    wxString label = m_menuList->GetItemText(sel);
    label.Trim(true);
    label.Trim(false);
    label = wxString(' ', curIdent * IDENTATION) + label;
    m_menuList->SetItemText(sel, label);
}

void MenuEditor::OnMenuUp(wxCommandEvent& e)
{
    long sel = GetSelectedItem();
    long prev = sel - 1;
    int prevIdent = GetItemIdentation(prev);
    int curIdent = GetItemIdentation(sel);
    if (prevIdent < curIdent) return;
    while (prevIdent > curIdent)
        prevIdent = GetItemIdentation(--prev);
        
    wxString label = m_menuList->GetItemText(sel);
    m_menuList->DeleteItem(sel);
    long newSel = m_menuList->InsertItem(prev, label);
    sel++; prev++;
    if (sel < m_menuList->GetItemCount())
    {
        long childIdent = GetItemIdentation(sel);
        while (sel < m_menuList->GetItemCount() && childIdent > curIdent)
        {
            label = m_menuList->GetItemText(sel);
            m_menuList->DeleteItem(sel);
            m_menuList->InsertItem(prev, label);
            sel++; prev++;
            if (sel < m_menuList->GetItemCount()) childIdent = GetItemIdentation(sel);
        }
    }
    m_menuList->SetItemState(newSel, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
}

long MenuEditor::GetEndIndex(long n)
{
    long res = n;
    int ident = GetItemIdentation(n);
    res++;
    if (res >= m_menuList->GetItemCount()) return n;
    while (GetItemIdentation(res) > ident) res++;
    return res - 1;
}

void MenuEditor::OnMenuDown(wxCommandEvent& e)
{
    long sel = GetSelectedItem();
    int selIdent = GetItemIdentation(sel);
    long selAux = sel + 1;
    while (GetItemIdentation(selAux) > selIdent) selAux++;
    if (GetItemIdentation(selAux) < selIdent) return;
    long endIndex = GetEndIndex(selAux) + 1;
    wxString label = m_menuList->GetItemText(sel);
    
    m_menuList->DeleteItem(sel);
    endIndex--;
    long first = m_menuList->InsertItem(endIndex, label);
    while (GetItemIdentation(sel) > selIdent)
    {
        label = m_menuList->GetItemText(sel);
        m_menuList->DeleteItem(sel);
        m_menuList->InsertItem(endIndex, label);
        first--;
    }
    m_menuList->SetItemState(first, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
}

void MenuEditor::OnUpdateMovers(wxUpdateUIEvent& e)
{
    switch (e.GetId())
    {
        case ID_MENUUP:
            e.Enable(GetSelectedItem() > 0);
            break;
        case ID_MENUDOWN:
            e.Enable(GetSelectedItem() < m_menuList->GetItemCount() - 1);
        default:
            break;
    }
}

