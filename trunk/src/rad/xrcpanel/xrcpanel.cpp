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
// Panel para código XRC (basado en el panel de CPP)
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

  top_sizer->Add(m_xrcPanel,1,wxEXPAND,0);
  
  SetSizer(top_sizer);
  SetAutoLayout(true);
  top_sizer->SetSizeHints(this);
  top_sizer->Fit(this);
  top_sizer->Layout();

  m_cw = PTCCodeWriter(new TCCodeWriter(m_xrcPanel->GetTextCtrl()));
}

void XrcPanel::CodeGeneration()
{
  PObjectBase project = GetData()->GetProjectData();
  
  // Vamos a generar el código en el panel
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
