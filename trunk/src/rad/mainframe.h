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
// Añadido include para panel XRC y declaración de m_xrc
// Juan Antonio Ortega (jortegalalmolda@gmail.com)

#ifndef __MAIN_FRAME__
#define __MAIN_FRAME__

#include "wx/wx.h"
#include "palette.h"
#include "inspector/objinspect.h"
#include "objecttree/objecttree.h"
//#include "designpanel.h"
#include "rad/designer/visualeditor.h"
//#include "codeeditor.h"
#include "rad/cpppanel/cpppanel.h"
#include "rad/xrcpanel/xrcpanel.h"
#include "rad/appobserver.h"

class MainFrame : public DataObserver, public wxFrame
{
 private:
  #ifdef __WXFB_DEBUG__
  wxLog * m_old_log;
  wxLogWindow * m_log;
  #endif //__WXFB_DEBUG__

  wxNotebook *m_notebook;
  wxFbPalette *m_palette;
  ObjectTree *m_objTree;
  ObjectInspector *m_objInsp;
  ToolPanel *m_toolPanel;
//  DesignPanel *m_design;
  VisualEditor *m_visualEdit;
//  CodeEditorPanel *m_h;
//  CodeEditorPanel *m_cpp;
  CppPanel *m_cpp;
  XrcPanel *m_xrc;
  
  DECLARE_EVENT_TABLE()
 public:
  MainFrame(DataObservable *data,wxWindow *parent, int id = -1);
  ~MainFrame();
  void RestorePosition(const wxString &name);
  void SavePosition(const wxString &name);
  void OnSaveProject(wxCommandEvent &event);
  void OnOpenProject(wxCommandEvent &event);
  void OnNewProject(wxCommandEvent &event);
  void OnGenerateCode(wxCommandEvent &event);
  void OnAbout(wxCommandEvent &event);
  void OnExit(wxCommandEvent &event);
  void OnClose(wxCloseEvent &event);
  void OnImportXrc(wxCommandEvent &event);
  
  void ProjectLoaded();
  void ProjectSaved();
  void ObjectSelected(PObjectBase obj);
  void ObjectCreated(PObjectBase obj);
  void ObjectRemoved(PObjectBase obj);
  void PropertyModified(PProperty prop);
  void CodeGeneration();
};  



#endif //__MAIN_FRAME__
