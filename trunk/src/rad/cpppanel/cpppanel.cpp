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
  InitStyledTextCtrl(m_hPanel->GetTextCtrl());
  notebook->AddPage( m_hPanel, wxT("h") );

  m_cppPanel = new CodeEditor(notebook,-1);
  InitStyledTextCtrl(m_cppPanel->GetTextCtrl());
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

void CppPanel::InitStyledTextCtrl(wxStyledTextCtrl *stc)
{
    stc->SetLexer(wxSTC_LEX_CPP);
    stc->SetKeyWords(0, _T("asm auto bool break case catch char class const const_cast \
       continue default delete do double dynamic_cast else enum explicit \
       export extern false float for friend goto if inline int long \
       mutable namespace new operator private protected public register \
       reinterpret_cast return short signed sizeof static static_cast \
       struct switch template this throw true try typedef typeid \
       typename union unsigned using virtual void volatile wchar_t \
       while")); 
    
    #ifdef __WXMSW__
    wxFont font(10, wxMODERN, wxNORMAL, wxNORMAL);
    #elif defined(__WXGTK__)
    // Debe haber un bug en wxGTK ya que la familia wxMODERN no es de ancho fijo.
    wxFont font(12, wxMODERN, wxNORMAL, wxNORMAL);
    font.SetFaceName(_T("Monospace"));
    #endif
    stc->StyleSetFont(wxSTC_STYLE_DEFAULT, font);
    stc->StyleClearAll();
    stc->StyleSetBold(wxSTC_C_WORD, true);
    stc->StyleSetForeground(wxSTC_C_STRING, *wxRED);
    stc->StyleSetForeground(wxSTC_C_STRINGEOL, *wxRED);
    stc->StyleSetForeground(wxSTC_C_PREPROCESSOR, wxColour(0, 128, 0));
    stc->StyleSetForeground(wxSTC_C_COMMENT, wxColour(49, 106, 197));
    stc->StyleSetForeground(wxSTC_C_COMMENTLINE, wxColour(49, 106, 197));
    stc->StyleSetForeground(wxSTC_C_COMMENTDOC, wxColour(49, 106, 197));
    stc->StyleSetForeground(wxSTC_C_COMMENTLINEDOC, wxColour(49, 106, 197));
    stc->StyleSetForeground(wxSTC_C_NUMBER, wxColour(128, 0, 128));
    stc->SetUseTabs(false);
    stc->SetTabWidth(4);
    stc->SetTabIndents(true);
    stc->SetBackSpaceUnIndents(true);
    stc->SetIndent(4);
    stc->SetSelBackground(true, wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHT));
    stc->SetSelForeground(true, wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHTTEXT));
    
    stc->SetCaretWidth(2);   
}

void CppPanel::CodeGeneration()
{
  PObjectBase project = GetData()->GetProjectData();

  wxString path, file;
  bool useRelativePath = false;
  
  PProperty pCodeGen = project->GetProperty("code_generation");
  if (pCodeGen)
  {
    if (!TypeConv::FlagSet  (wxT("C++"),_WXSTR(pCodeGen->GetValue())))
      return;
  }
    
  // Obtenemos el path de salida
  PProperty ppath = project->GetProperty("path");
  if (ppath)
    path = _WXSTR(ppath->GetValue());
    
  // Obtenemos el nombre del fichero
  PProperty pfile = project->GetProperty("file");
  if (pfile)
    file = _WXSTR(pfile->GetValue());
      
  if (file == wxT(""))
    file = wxT("noname");

  // Comprobamos si hay que usar rutas relativas o absolutas en la generación
  PProperty pRelPath = project->GetProperty("relative_path");
  if (pRelPath)
    useRelativePath = (pRelPath->GetValueAsInteger() ? true : false);
 
 
  // Vamos a generar el código en el panel
  {
    CppCodeGenerator codegen;
    //codegen.SetBasePath(ppath->GetValue());
    //codegen.SetRelativePath(useRelativePath);
    codegen.UseRelativePath(useRelativePath,_STDSTR(path));

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
    codegen.UseRelativePath(useRelativePath,_STDSTR(path));
    
    if (!path.IsEmpty())
    {
      PCodeWriter h_cw(new FileCodeWriter(path + wxFILE_SEP_PATH + file + wxT(".h")));
      PCodeWriter cpp_cw(new FileCodeWriter(path + wxFILE_SEP_PATH + file + wxT(".cpp")));
    
      codegen.SetHeaderWriter(h_cw);
      codegen.SetSourceWriter(cpp_cw);
      codegen.GenerateCode(project);
      wxLogMessage(wxT("Code generated on \'%s\'."),path.c_str());
    }
    else
      wxLogError(wxT("You must set a path for files"));
  }  
}

CodeEditor::CodeEditor(wxWindow *parent, int id)
  : wxPanel(parent,id)
{
  wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
  m_code = new wxStyledTextCtrl(this, -1);
  wxFont font(10, wxMODERN, wxNORMAL, wxNORMAL);
  m_code->StyleSetFont(wxSTC_STYLE_DEFAULT, font);
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

TCCodeWriter::TCCodeWriter(wxStyledTextCtrl *tc )
{
  SetTextCtrl(tc); 
}

void TCCodeWriter::DoWrite(string code)
{
  if (m_tc)  
    m_tc->AddText(wxString(code.c_str(),wxConvUTF8));
}

void TCCodeWriter::Clear()
{
  if (m_tc)
    m_tc->ClearAll(); //*!*
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
