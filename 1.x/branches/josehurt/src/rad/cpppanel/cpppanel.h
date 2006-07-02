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

#ifndef __CPP_PANEL__
#define __CPP_PANEL__

#include "wx/wx.h"
#include "codegen/codegen.h"
#include "codegen/cppcg.h"
#include "rad/appobserver.h"
#include "wx/file.h"


#include <boost/smart_ptr.hpp>

using namespace boost;

class TCCodeWriter : public CodeWriter
{
 private: 
  wxTextCtrl *m_tc;
 protected:
  void DoWrite(string code);
  
 public:
  TCCodeWriter();
  TCCodeWriter(wxTextCtrl *tc);
  
  void SetTextCtrl (wxTextCtrl *tc) { m_tc = tc; }
  void Clear();
};

class FileCodeWriter : public CodeWriter
{
 private: 
  wxFile m_file;
  wxString m_filename;

 protected:
  void DoWrite(string code);
  
 public:
  FileCodeWriter(const wxString &file);
  void Clear();
};


typedef shared_ptr<TCCodeWriter> PTCCodeWriter;

class CodeEditor : public wxPanel
{
 private:
  wxTextCtrl *m_code; 
 public:
  CodeEditor(wxWindow *parent, int id);   
  wxTextCtrl *GetTextCtrl() { return m_code; }
};


class CppPanel : public wxPanel, public DataObserver
{
 private:
  CodeEditor *m_cppPanel;
  CodeEditor *m_hPanel;
  PTCCodeWriter m_hCW;
  PTCCodeWriter m_cppCW;
  
 public:
  CppPanel(wxWindow *parent, int id);   
  
  void CodeGeneration();
};


class CppToolBar : public wxPanel
{
 public:
   CppToolBar(wxWindow *parent, int id); 
};



#endif //__CPP_PANEL__
