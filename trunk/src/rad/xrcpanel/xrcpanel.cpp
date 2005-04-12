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
// Panel para c�digo XRC (basado en el panel de CPP)
// C�digo de inicializaci�n de wxStyledTextCtrl
// Juan Antonio Ortega (jortegalalmolda@gmail.com)

#include "xrcpanel.h"
#include "rad/bitmaps.h"
#include "codegen/xrccg.h"
#include "utils/typeconv.h"

XrcPanel::XrcPanel(wxWindow *parent, int id)
  : wxPanel (parent,id)
{
  wxBoxSizer *top_sizer = new wxBoxSizer(wxVERTICAL);

  m_xrcPanel = new CodeEditor(this,-1);
  InitStyledTextCtrl(m_xrcPanel->GetTextCtrl());

  top_sizer->Add(m_xrcPanel,1,wxEXPAND,0);
  
  SetSizer(top_sizer);
  SetAutoLayout(true);
  top_sizer->SetSizeHints(this);
  top_sizer->Fit(this);
  top_sizer->Layout();

  m_cw = PTCCodeWriter(new TCCodeWriter(m_xrcPanel->GetTextCtrl()));
}

void XrcPanel::InitStyledTextCtrl(wxStyledTextCtrl *stc)
{
  stc->SetLexer(wxSTC_LEX_XML);
    
  #ifdef __WXMSW__
  wxFont font(10, wxMODERN, wxNORMAL, wxNORMAL);
  #elif defined(__WXGTK__)
  // Debe haber un bug en wxGTK ya que la familia wxMODERN no es de ancho fijo.
  wxFont font(12, wxMODERN, wxNORMAL, wxNORMAL);
  font.SetFaceName(_T("Monospace"));
  #endif
    
  stc->StyleSetFont(wxSTC_STYLE_DEFAULT, font);
  stc->StyleClearAll();
  stc->StyleSetForeground(wxSTC_H_DOUBLESTRING, *wxRED);
  stc->StyleSetForeground(wxSTC_H_TAG, wxColour(0, 0, 128));
  stc->StyleSetForeground(wxSTC_H_ATTRIBUTE, wxColour(128, 0, 128));
  stc->SetUseTabs(false);
  stc->SetTabWidth(4);
  stc->SetTabIndents(true);
  stc->SetBackSpaceUnIndents(true);
  stc->SetIndent(4);
  stc->SetSelBackground(true, wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHT));
  stc->SetSelForeground(true, wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHTTEXT));

  stc->SetCaretWidth(2);   
}

void XrcPanel::CodeGeneration()
{
  PObjectBase project = GetData()->GetProjectData();
  
  // Vamos a generar el c�digo en el panel
  {
    XrcCodeGenerator codegen;

    m_xrcPanel->GetTextCtrl()->Freeze();

    codegen.SetWriter(m_cw);   
    codegen.GenerateCode(project);
    
    m_xrcPanel->GetTextCtrl()->Thaw();
  }
  
  // y ahora en el fichero
  {
    XrcCodeGenerator codegen;
    
    wxString path, file;
    PProperty ppath = project->GetProperty("path");
    if (ppath)
      path = _WXSTR(ppath->GetValue());
      
    PProperty pfile = project->GetProperty("file");
    if (pfile)
      file = _WXSTR(pfile->GetValue());
      
    if (file == wxT(""))
      file = wxT("wxfb_code");
    
    PCodeWriter cw(new FileCodeWriter(path + wxFILE_SEP_PATH + file + wxT(".xrc")));
    
    codegen.SetWriter(cw);
    codegen.GenerateCode(project);
  } 
}
