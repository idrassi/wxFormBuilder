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

#include "palette.h"
#include "model/objectbase.h"
#include "bitmaps.h"
#include "utils/debug.h"
#include "rad/title.h"
#include "icons/play.xpm"

#define ID_PALETTE_BUTTON 999
#define ID_ABOUT 100
#define ID_QUIT  101 

wxWindowID wxFbPalette::nextId = wxID_HIGHEST + 2;

BEGIN_EVENT_TABLE(wxFbPalette, wxPanel)
    EVT_TOOL(-1, wxFbPalette::OnButtonClick)
END_EVENT_TABLE()

wxFbPalette::wxFbPalette(wxWindow *parent,int id)
  : wxPanel(parent,id), m_notebook(NULL)
{
}

void wxFbPalette::Create()
{
  wxBoxSizer *top_sizer = new wxBoxSizer(wxVERTICAL);
  
  m_notebook = new wxNotebook(this,-1);

//  unsigned int pkg_count = ApplicationDocument::GetInstance()->GetPackageCount();
  unsigned int pkg_count = GetData()->GetPackageCount();
  
  Debug::Print("[Palette] Pages %d",pkg_count);
  
  for (unsigned int i = 0; i< pkg_count;i++)
  {
    PObjectPackage pkg = GetData()->GetPackage(i);
    string pkg_name = pkg->GetPackageName();

    wxPanel *panel = new wxPanel(m_notebook,-1);

    wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
    Debug::Print("[Palette] Page %s Items %d",pkg_name.c_str(), pkg->GetObjectCount());
    wxToolBar *toolbar = new wxToolBar(panel, -1, wxDefaultPosition, wxDefaultSize, wxTB_NODIVIDER | wxTB_FLAT);
    toolbar->SetToolBitmapSize(wxSize(22, 22));
    
    unsigned int j;
    for (j=0;j<pkg->GetObjectCount();j++)
    {
      wxString widget(pkg->GetObjectInfo(j)->GetClassName().c_str(),wxConvUTF8);
      wxString icon_file(pkg->GetObjectInfo(j)->GetIconFile().c_str(),wxConvUTF8);

      wxBitmap icon;
      icon.LoadFile(icon_file,wxBITMAP_TYPE_XPM);
      
      //wxBitmapButton *button = new wxBitmapButton(panel,-1,icon,wxDefaultPosition,wxSize(32,32));
      //button->SetToolTip(widget);
      toolbar->AddTool(nextId++, widget, icon, widget);

      //button->PushEventHandler(new PaletteButtonEventHandler(widget,GetData()));
      //sizer->Add(button,0, wxALL, 2);
    }
    toolbar->Realize();
    m_tv.push_back(toolbar);
    sizer->Add(toolbar, 0, wxALL | wxALIGN_CENTER_VERTICAL, 2);
    panel->SetAutoLayout(true);
    panel->SetSizer(sizer);
    sizer->Fit(panel);
    sizer->SetSizeHints(panel);

    m_notebook->AddPage(panel,wxString(pkg_name.c_str(),wxConvUTF8));

  }
/*
  wxStaticText *text = new wxStaticText(this,-1,wxT("COMPONENT PALETTE"),wxDefaultPosition,wxDefaultSize,wxSIMPLE_BORDER);
  text->SetBackgroundColour(wxColour(100,100,100));
  text->SetForegroundColour(*wxWHITE);
  text->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxBOLD, 0, wxT("")));*/
  Title *title = new Title(this,wxT("COMPONENT PALETTE"));
  top_sizer->Add(title,0,wxEXPAND,0);
  top_sizer->Add(new wxNotebookSizer(m_notebook),1,wxEXPAND,0);
  SetAutoLayout(true);
  SetSizer(top_sizer);
  top_sizer->Fit(this);
  top_sizer->SetSizeHints(this);

}

void wxFbPalette::OnButtonClick(wxCommandEvent &event)
{
  for (int i = 0; i < m_tv.size(); i++)
  {
    if (m_tv[i]->FindById(event.GetId()))
    {
      wxString name = m_tv[i]->GetToolShortHelp(event.GetId());
      GetData()->CreateObject(name);
      return;
    }
  }
}  


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


  /*
  for (int i=0;i<6;i++)
  {
    button = new wxBitmapButton(this,-1,AppBitmaps::GetBitmap(wxT("")),
      wxDefaultPosition,wxSize(24,24));  
    //sizer->Add(button,0,wxALL,2);
    sizer->Add(button,0,0,0);
  } */ 
  SetSizer(sizer);
  sizer->SetSizeHints(this);

}  

void ToolPanel::OnSaveFile(wxCommandEvent &event)
{
//  GetDocument()->SaveDocument(wxT("c:\\pepe.xml"));
}  


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

