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
#include "rad/cmdproc.h"
#include <set>

class ApplicationData : public DataObservable
{
 private: 
  
  bool m_changeFlag;        // flag de proyecto modificado
  PObjectDatabase m_objDb;  // Base de datos de objetos  
  PObjectBase m_project; // Proyecto
  PObjectBase m_selObj;     // Objeto seleccionado

  PObjectBase m_clipboard;
  bool m_copyOnPaste; // flag que indica si hay que copiar el objeto al pegar
  CommandProcessor m_cmdProc;
  
  /**
   * Resuelve un posible conflicto de nombres.
   * @note el objeto a comprobar debe estar insertado en proyecto, por tanto
   *       no es válida para arboles "flotantes".
   */
  void ResolveNameConflict(PObjectBase obj);
  
  /**
   * Rutina auxiliar de ResolveNameConflict
   */
  void BuildNameSet(PObjectBase obj, PObjectBase top, set<string> &name_set);
  
  
  int CalcPositionOfInsertion(PObjectBase selected,PObjectBase parent);
  
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
  void CopyObject(PObjectBase obj);
  void PasteObject(PObjectBase parent);
  void InsertObject(PObjectBase obj, PObjectBase parent);
  void MergeProject(PObjectBase project);
  void ModifyProperty(PProperty prop, wxString value); 
  void GenerateCode();
  void MovePosition(PObjectBase, bool right, unsigned int num = 1);
  void Undo();
  void Redo();
  
  // Servicios para los observadores  
  PObjectBase GetSelectedObject();
  PObjectBase GetProjectData();
  PObjectBase GetSelectedForm();
  bool CanUndo() { return m_cmdProc.CanUndo(); }
  bool CanRedo() { return m_cmdProc.CanRedo(); }
  

  

  PObjectPackage GetPackage(unsigned int idx)
    { return m_objDb->GetPackage(idx);}
  
  unsigned int GetPackageCount()
    { return m_objDb->GetPackageCount(); }
  
  PObjectDatabase GetObjectDatabase()
    { return m_objDb; }
  
};

///////////////////////////////////////////////////////////////////////////////
// Comandos
///////////////////////////////////////////////////////////////////////////////

class InsertObjectCmd : public Command
{
 private:
  PObjectBase m_parent;
  PObjectBase m_object;
  int m_pos;
  
 protected:
  void DoExecute();
  void DoRestore();
 
 public:
   InsertObjectCmd(PObjectBase object, PObjectBase parent, int pos = -1);
};

class RemoveObjectCmd : public Command
{
private:
  PObjectBase m_parent;
  PObjectBase m_object;
  int m_oldPos;
  
 protected:
  void DoExecute();
  void DoRestore();
 
 public:
   RemoveObjectCmd(PObjectBase object);
};

class ModifyPropertyCmd : public Command
{
 private:
  PProperty m_property;
  string m_oldValue, m_newValue;
 
 protected:
  void DoExecute();
  void DoRestore();
  
 public:
  ModifyPropertyCmd(PProperty prop, string value);
};

class ShiftChildCmd : public Command
{
 private:
  PObjectBase m_object;
  int m_oldPos, m_newPos;

 protected:
  void DoExecute();
  void DoRestore();
  
 public:
  ShiftChildCmd(PObjectBase object, int pos);

};

#endif //__APP_DATA__
