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

#include "cpppanel.h"
#include "rad/bitmaps.h"
#include "utils/typeconv.h"

#include <wx/notebook.h>

CppPanel::CppPanel(wxWindow *parent, int id)
  : wxPanel (parent,id)
{
  wxBoxSizer *top_sizer = new wxBoxSizer(wxVERTICAL);

//  CppToolBar *toolbar = new CppToolBar(this,-1);  
  wxNotebook *notebook = new wxNotebook(this,-1);

  m_hPanel = new CodeEditor(notebook,-1);
  notebook->AddPage( m_hPanel, wxT("h") );

  m_cppPanel = new CodeEditor(notebook,-1);
  notebook->AddPage( m_cppPanel, wxT("cpp") );

//  top_sizer->Add(toolbar,0,wxEXPAND,0); 
  //top_sizer->Add(new wxNotebookSizer(notebook),1,wxEXPAND,0);
  top_sizer->Add(notebook,1,wxEXPAND,0);
  
  SetSizer(top_sizer);
  SetAutoLayout(true);
  top_sizer->SetSizeHints(this);
  top_sizer->Fit(this);
  top_sizer->Layout();

  m_hCW = PTCCodeWriter(new TCCodeWriter(m_hPanel->GetTextCtrl()));
  m_cppCW = PTCCodeWriter(new TCCodeWriter(m_cppPanel->GetTextCtrl()));
};

void CppPanel::CodeGeneration()
{
  PObjectBase project = GetData()->GetProjectData();
  
  // Vamos a generar el código en el panel
  {
    CppCodeGenerator codegen;

    m_cppPanel->GetTextCtrl()->Freeze();
    m_hPanel->GetTextCtrl()->Freeze();

    codegen.SetHeaderWriter(m_hCW);   
    codegen.SetSourceWriter(m_cppCW);
    codegen.GenerateCode(project);
    m_cppPanel->GetTextCtrl()->Thaw();
    m_hPanel->GetTextCtrl()->Thaw();
  }
  
  // y ahora en el fichero
  {
    CppCodeGenerator codegen;
    
    wxString path, file;
    PProperty ppath = project->GetProperty("path");
    if (ppath)
      path = _WXSTR(ppath->GetValue());
      
    PProperty pfile = project->GetProperty("file");
    if (pfile)
      file = _WXSTR(pfile->GetValue());
      
    if (file == wxT(""))
      file = wxT("wxfb_code");
    
    
    PCodeWriter h_cw(new FileCodeWriter(path + wxFILE_SEP_PATH + file + wxT(".h")));
    PCodeWriter cpp_cw(new FileCodeWriter(path + wxFILE_SEP_PATH + file + wxT(".cpp")));
    
    codegen.SetHeaderWriter(h_cw);
    codegen.SetSourceWriter(cpp_cw);
    codegen.GenerateCode(project);
  }  
}

CodeEditor::CodeEditor(wxWindow *parent, int id)
  : wxPanel(parent,id)
{
  wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
  m_code = new wxTextCtrl(this, -1, wxT(""), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_DONTWRAP|wxTE_READONLY);
  m_code->SetFont(wxFont(10, wxDEFAULT, wxNORMAL, wxNORMAL, 0, wxT("Courier New")));
  sizer->Add(m_code,1,wxEXPAND|wxALL,5);
  SetSizer(sizer);
  sizer->SetSizeHints(this);
}

CppToolBar::CppToolBar(wxWindow *parent, int id)
  : wxPanel(parent,id)
{
  wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
  wxBitmapButton *button;
  /*
  button = new wxBitmapButton(this,-1,AppBitmaps::GetBitmap(wxT("open")),
    wxDefaultPosition,wxSize(24,24));  
  sizer->Add(button,0,0,0);*/

  button = new wxBitmapButton(this,-1,AppBitmaps::GetBitmap(wxT("save")),
    wxDefaultPosition,wxSize(24,24));  
  sizer->Add(button,0,0,0);
  SetSizer(sizer);
  sizer->SetSizeHints(this);
}

TCCodeWriter::TCCodeWriter()
{
  m_tc = NULL;
}

TCCodeWriter::TCCodeWriter(wxTextCtrl *tc )
{
  SetTextCtrl(tc); 
}

void TCCodeWriter::DoWrite(string code)
{
  if (m_tc)  
    m_tc->AppendText(wxString(code.c_str(),wxConvUTF8));
}

void TCCodeWriter::Clear()
{
  if (m_tc)
    m_tc->Clear();
}


FileCodeWriter::FileCodeWriter(const wxString &file)
 : m_filename(file)
{
  m_file.Create(file,true);
}

void FileCodeWriter::DoWrite(string code)
{
  m_file.Write(_WXSTR(code));
}

void FileCodeWriter::Clear()
{
  m_file.Create(m_filename,true);
}
