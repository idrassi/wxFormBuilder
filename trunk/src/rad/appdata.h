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

#ifndef __APP_DATA__
#define __APP_DATA__

#include "rad/appobserver.h"
#include "model/database.h"

class ApplicationData : public DataObservable
{
 private: 
  
  bool m_changeFlag;        // flag de proyecto modificado
  PObjectDatabase m_objDb;  // Base de datos de objetos  
  PObjectBase m_project; // Proyecto
  PObjectBase m_selObj;     // Objeto seleccionado

  PObjectBase m_clipboard;
  
  
  
 public:
  ApplicationData();

  // Operaciones sobre los datos
  bool LoadProject(const wxString &filename);
  void SaveProject(const wxString &filename);
  void NewProject();
  void SelectObject(PObjectBase obj);
  void CreateObject(wxString name);
  void RemoveObject(PObjectBase obj);
  void CutObject(PObjectBase obj);
  void PasteObject(PObjectBase parent);
  void InsertObject(PObjectBase obj, PObjectBase parent);
  void MergeProject(PObjectBase project);
  void ModifyProperty(PProperty prop, wxString value); 
  void GenerateCode();
  void MovePosition(PObjectBase, bool right, unsigned int num = 1);
  
  // Servicios para los observadores  
  PObjectBase GetSelectedObject();
  PObjectBase GetProjectData();
  PObjectBase GetSelectedForm();
  

  

  PObjectPackage GetPackage(unsigned int idx)
    { return m_objDb->GetPackage(idx);}
  
  unsigned int GetPackageCount()
    { return m_objDb->GetPackageCount(); }
  
  PObjectDatabase GetObjectDatabase()
    { return m_objDb; }
  
};

#endif //__APP_DATA__
