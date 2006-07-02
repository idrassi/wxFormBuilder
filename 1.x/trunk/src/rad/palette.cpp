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

#include "palette.h"
#include "model/objectbase.h"
#include "bitmaps.h"
#include "utils/debug.h"
#include "rad/title.h"

#define ID_PALETTE_BUTTON 999
#define ID_ABOUT 100
#define ID_QUIT  101

wxWindowID wxFbPalette::nextId = wxID_HIGHEST + 1000;

BEGIN_EVENT_TABLE(wxFbPalette, wxPanel)
    EVT_TOOL(-1, wxFbPalette::OnButtonClick)
    EVT_SPIN_UP(-1, wxFbPalette::OnSpinUp)
    EVT_SPIN_DOWN(-1, wxFbPalette::OnSpinDown)
END_EVENT_TABLE()

wxFbPalette::wxFbPalette(wxWindow *parent,int id)
  : wxPanel(parent,id), m_notebook(NULL)
{
}

void wxFbPalette::PopulateToolbar(PObjectPackage pkg, wxToolBar *toolbar)
{
  unsigned int j = 0;
  while (j < pkg->GetObjectCount())
  {
    wxString widget(pkg->GetObjectInfo(j)->GetClassName().c_str(),wxConvUTF8);
    wxString icon_file(pkg->GetObjectInfo(j)->GetIconFile().c_str(),wxConvUTF8);

    wxBitmap icon;
    icon.LoadFile(icon_file, wxBITMAP_TYPE_XPM);

    toolbar->AddTool(nextId++, widget, icon, widget);
    toolbar->Realize();
    j++;
  }
}

void wxFbPalette::Create()
{
  wxBoxSizer *top_sizer = new wxBoxSizer(wxVERTICAL);

  m_notebook = new wxNotebook(this,-1);

  unsigned int pkg_count = GetData()->GetPackageCount();

  Debug::Print("[Palette] Pages %d",pkg_count);

  for (unsigned int i = 0; i < pkg_count;i++)
  {
    PObjectPackage pkg = GetData()->GetPackage(i);
    string pkg_name = pkg->GetPackageName();

    wxPanel *panel = new wxPanel(m_notebook,-1);
    wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);

    wxPanel *tbPanel = new wxPanel(panel,-1);
    wxBoxSizer *tbSizer = new wxBoxSizer(wxHORIZONTAL);

    wxPanel *sbPanel = new wxPanel(panel,-1);
    wxBoxSizer *sbSizer = new wxBoxSizer(wxHORIZONTAL);

    wxToolBar *toolbar = new wxToolBar(tbPanel, -1, wxDefaultPosition, wxDefaultSize, wxTB_NODIVIDER | wxTB_FLAT);
    toolbar->SetToolBitmapSize(wxSize(22, 22));
    PopulateToolbar(pkg, toolbar);
    m_tv.push_back(toolbar);

    tbSizer->Add(toolbar, 1, wxALL | wxALIGN_CENTER_VERTICAL, 2);
    tbPanel->SetSizer(tbSizer);

    wxSpinButton *sb = new wxSpinButton(sbPanel, -1, wxDefaultPosition, wxDefaultSize, wxSP_HORIZONTAL);
    sb->SetRange(0, (int)pkg->GetObjectCount() - 1);
    sb->SetValue(0);
    m_posVector.push_back(0);
    sbSizer->Add(sb, 0, wxALL | wxALIGN_TOP, 0);
    sbPanel->SetSizer(sbSizer);

    sizer->Add(tbPanel,1,wxEXPAND, 0);
    sizer->Add(sbPanel,0,wxEXPAND, 0);
    panel->SetAutoLayout(true);
    panel->SetSizer(sizer);
    sizer->Fit(panel);
    sizer->SetSizeHints(panel);

    m_notebook->AddPage(panel, wxString(pkg_name.c_str(), wxConvUTF8));

  }
  Title *title = new Title(this,wxT("Component Palette"));
  top_sizer->Add(title,0,wxEXPAND,0);
  //top_sizer->Add(new wxNotebookSizer(m_notebook),1,wxEXPAND,0);
  top_sizer->Add(m_notebook,1,wxEXPAND,0);
  SetAutoLayout(true);
  SetSizer(top_sizer);
  top_sizer->Fit(this);
  top_sizer->SetSizeHints(this);
}

void wxFbPalette::OnSpinUp(wxSpinEvent& e)
{/*
  int page = m_notebook->GetSelection(), i = 0;
  PObjectPackage pkg = GetData()->GetPackage(page);
  int firstHidden = 0;

  // Calcular el primer icono oculto

  wxMenu *popup = new wxMenu();
  for (i=firstHidden; i < pkg->GetObjectCount() ; i++)
  {
    wxString widget(pkg->GetObjectInfo(i)->GetClassName().c_str(),wxConvUTF8);
    wxString icon_file(pkg->GetObjectInfo(i)->GetIconFile().c_str(),wxConvUTF8);

    wxBitmap icon;
    icon.LoadFile(icon_file, wxBITMAP_TYPE_XPM);

    wxMenuItem *item = new wxMenuItem(popup,-1,widget,widget);
    item->SetBitmap(icon);

    popup->Append(item);
    //popup->Append(-1,widget,widget);
  }

  PopupMenu(popup);*/

  int page = m_notebook->GetSelection();
  PObjectPackage pkg = GetData()->GetPackage(page);

  if ((int)pkg->GetObjectCount() - m_posVector[page] - 1 <= 0) return;

  m_posVector[page]++;
  wxToolBar *toolbar = m_tv[page];
  toolbar->DeleteToolByPos(0);
}

void wxFbPalette::OnSpinDown(wxSpinEvent& e)
{
  int page = m_notebook->GetSelection();
  if (m_posVector[page] <= 0) return;

  m_posVector[page]--;
  wxToolBar *toolbar = m_tv[page];
  PObjectPackage pkg = GetData()->GetPackage(page);
  wxString widget(pkg->GetObjectInfo(m_posVector[page])->GetClassName().c_str(),wxConvUTF8);
  wxString icon_file(pkg->GetObjectInfo(m_posVector[page])->GetIconFile().c_str(),wxConvUTF8);
  wxBitmap icon;
  icon.LoadFile(icon_file, wxBITMAP_TYPE_XPM);
  toolbar->InsertTool(0, nextId++, icon, wxNullBitmap, false, NULL, widget, widget);
  toolbar->Realize();
}

void wxFbPalette::OnButtonClick(wxCommandEvent &event)
{
  for (unsigned int i = 0; i < m_tv.size(); i++)
  {
    if (m_tv[i]->FindById(event.GetId()))
    {
      wxString name = m_tv[i]->GetToolShortHelp(event.GetId());
      GetData()->CreateObject(name);
      return;
    }
  }
}

/*
#define ID_FILE_OPEN 1000
#define ID_FILE_SAVE 1001

BEGIN_EVENT_TABLE(ToolPanel,wxPanel)
  EVT_BUTTON(ID_FILE_SAVE,ToolPanel::OnSaveFile)
END_EVENT_TABLE()

ToolPanel::ToolPanel(wxWindow *parent, int id)
  : wxPanel(parent,id)
{
  wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
  wxBitmapButton *button;

  button = new wxBitmapButton(this,ID_FILE_OPEN,AppBitmaps::GetBitmap(wxT("open")),
    wxDefaultPosition,wxSize(24,24));
  sizer->Add(button,0,0,0);

  button = new wxBitmapButton(this,ID_FILE_SAVE,AppBitmaps::GetBitmap(wxT("save")),
    wxDefaultPosition,wxSize(24,24));
  sizer->Add(button,0,0,0);

  button = new wxBitmapButton(this,-1,play_xpm,
    wxDefaultPosition,wxSize(24,24));
  sizer->Add(button,0,0,0);
*/

  /*
  for (int i=0;i<6;i++)
  {
    button = new wxBitmapButton(this,-1,AppBitmaps::GetBitmap(wxT("")),
      wxDefaultPosition,wxSize(24,24));
    //sizer->Add(button,0,wxALL,2);
    sizer->Add(button,0,0,0);
  } */
 /* SetSizer(sizer);
  sizer->SetSizeHints(this);

}

void ToolPanel::OnSaveFile(wxCommandEvent &event)
{
//  GetDocument()->SaveDocument(wxT("c:\\pepe.xml"));
}
*/
/*
PaletteButtonEventHandler::PaletteButtonEventHandler (wxString name,DataObservable *data)
{
  m_name = name;
  m_data = data;
}

BEGIN_EVENT_TABLE(PaletteButtonEventHandler,wxEvtHandler)
  EVT_BUTTON(-1,PaletteButtonEventHandler::OnButtonClick)
END_EVENT_TABLE()

void PaletteButtonEventHandler::OnButtonClick(wxCommandEvent &event)
{
  m_data->CreateObject(m_name);
}

*/
