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
// Juan Antonio Ortega (jortegalalmolda@gmail.com)

#ifndef __XRC_PANEL__
#define __XRC_PANEL__

#include "wx/wx.h"
#include "codegen/codegen.h"
#include "rad/cpppanel/cpppanel.h"
#include "rad/appobserver.h"
#include "wx/file.h"

class XrcPanel : public wxPanel, public DataObserver
{
 private:
  CodeEditor *m_xrcPanel;
  PTCCodeWriter m_cw;
  
  void InitStyledTextCtrl(wxStyledTextCtrl *stc);
 public:
  XrcPanel(wxWindow *parent, int id);   
  
  void CodeGeneration();
};


#endif //__XRC_PANEL__
