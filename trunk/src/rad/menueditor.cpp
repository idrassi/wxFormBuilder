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
END_EVENT_TABLE()

MenuEditor::MenuEditor(wxWindow *parent, int id) : wxDialog(parent,id,wxT(""),wxDefaultPosition,wxDefaultSize)
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
  m_bOk = new wxButton(this,ID_DEFAULT,wxT("OK"),wxDefaultPosition,wxDefaultSize,0);
  sizerOkCancel->Add(m_bOk, 0, wxALL, 5);
  wxButton *m_bCancel;
  m_bCancel = new wxButton(this,ID_DEFAULT,wxT("Cancel"),wxDefaultPosition,wxDefaultSize,0);
  sizerOkCancel->Add(m_bCancel, 0, wxALL, 5);
  mainSizer->Add(sizerOkCancel, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
  this->SetSizer(mainSizer);
  this->SetAutoLayout(true);
  this->Layout();
  SetClientSize(540, 293);
}

long MenuEditor::GetSelectedItem()
{
    return m_menuList->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
}

void MenuEditor::OnAddMenuItem(wxCommandEvent& e)
{
    int sel = GetSelectedItem();
    int identation = 0;
    if (sel >= 0) m_menuList->GetItemData(GetSelectedItem());
    wxString label = m_tcLabel->GetValue();
    label.Trim(true);
    label.Trim(false);
    m_menuList->InsertItem(sel >= 0 ? sel : 0, wxString(' ', identation) + label);
}

void MenuEditor::OnAddSeparator(wxCommandEvent& e)
{
}

void MenuEditor::OnRemoveMenuItem(wxCommandEvent& e)
{
}

void MenuEditor::OnMenuDown(wxCommandEvent& e)
{
}

void MenuEditor::OnMenuLeft(wxCommandEvent& e)
{
    int sel = GetSelectedItem();
    wxString label = m_menuList->GetItemText(sel);
    int curIdent = 0;
    while (curIdent < label.Len() && label[curIdent] == ' ') curIdent++;
    curIdent /= IDENTATION;
    
    if (curIdent == 0) return;
    
    label.Trim(true);
    label.Trim(false);
    label = wxString(' ', (curIdent - 1) * IDENTATION) + label;
    m_menuList->SetItemText(sel, label);
}

void MenuEditor::OnMenuRight(wxCommandEvent& e)
{
    int sel = GetSelectedItem();
    wxString label = m_menuList->GetItemText(sel);
    int curIdent = 0;
    while (curIdent < label.Len() && label[curIdent] == ' ') curIdent++;
    curIdent /= IDENTATION;
    label.Trim(true);
    label.Trim(false);
    label = wxString(' ', (curIdent + 1) * IDENTATION) + label;
    m_menuList->SetItemText(sel, label);
}

void MenuEditor::OnMenuUp(wxCommandEvent& e)
{
}


