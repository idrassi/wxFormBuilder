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

#ifndef __OBJ_INSPECT__
#define __OBJ_INSPECT__

#include "wx/wx.h"
#include "wx/grid.h"
#include <wx/notebook.h>

#include "propeditor.h"
#include "rad/appobserver.h"

class ObjectInspector : public DataObserver, public wxPanel
{
 private:
  typedef map<PProperty,PropertyEditor *> ObjInspectorMap;
  ObjInspectorMap m_map;
  
  PObjectBase m_currentSel;
  wxNotebook *m_notebook;
  


  void CreatePropertyPanel(const wxString& name, PObjectBase obj,
                           PObjectInfo obj_info, PropertyMap &map);
  
  void Create();
 protected:
   
 public:
  ObjectInspector(wxWindow *parent, int id);

  void ProjectLoaded();
  void ProjectSaved();
  void ObjectSelected(PObjectBase obj);
  void ObjectCreated(PObjectBase obj);
  void ObjectRemoved(PObjectBase obj);
  void PropertyModified(PProperty prop);
};

#endif //__OBJ_INSPECT__
