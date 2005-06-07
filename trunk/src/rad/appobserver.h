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

#ifndef __APP_OBSERVER__
#define __APP_OBSERVER__

#include "model/objectbase.h"
#include "model/database.h"
#include "wx/wx.h"
#include <vector>

class DataObserver;
//class ItemPopupMenu;

/**
 * Interfaz para manejar el modelo de datos de la aplicación.
 */
class DataObservable
{
 private:
   typedef vector<DataObserver *> ObserverVector;
   ObserverVector m_observers;
   bool m_lock;
   //friend class ItemPopupMenu;

 protected:
   // Notifican a cada observador el evento correspondiente
   void NotifyProjectLoaded();
   void NotifyProjectSaved();
   void NotifyObjectSelected(PObjectBase obj); 
   void NotifyObjectCreated(PObjectBase obj); 
   void NotifyObjectRemoved(PObjectBase obj);
   void NotifyPropertyModified(PProperty prop);
   void NotifyProjectRefresh();
   void NotifyCodeGeneration();
   
 public: 
  DataObservable() { m_lock = false; }  
  virtual ~DataObservable() {};
    
  // notar que los observadores se pasan como punteros normales, el motivo
  // es que, generalmente, las implementaciones de DataObserver serán objetos
  // de la GUI, por tanto es el propio framework quien gestiona la vida del
  // objeto.
  void AddDataObserver(DataObserver *o);
  void RemoveDataObserver(DataObserver *o);

  // Realizan cambios en el modelo de datos.
  virtual bool LoadProject(const wxString &filename) = 0;
  virtual void SaveProject(const wxString &filename) = 0;
  virtual void NewProject() = 0;
  virtual void SelectObject(PObjectBase obj) = 0;
  virtual void CreateObject(wxString name) = 0;
  virtual void RemoveObject(PObjectBase obj) = 0;
  virtual void CutObject(PObjectBase obj) = 0;
  virtual void PasteObject(PObjectBase parent) = 0;
  virtual void InsertObject(PObjectBase obj, PObjectBase parent) = 0;
  virtual void MergeProject(PObjectBase project) = 0;
  virtual void ModifyProperty(PProperty prop, wxString value) = 0;
  virtual void GenerateCode() = 0;
  virtual void MovePosition(PObjectBase, bool right, unsigned int num = 1) = 0;
  virtual void Undo() = 0;
  virtual void Redo() = 0;
  
  // Obtienen información del modelo de datos
  virtual PObjectPackage GetPackage(unsigned int idx) = 0;
  virtual unsigned int GetPackageCount() = 0;
  virtual PObjectDatabase GetObjectDatabase() = 0;

  virtual PObjectBase GetSelectedObject() = 0;
  virtual PObjectBase GetSelectedForm() = 0;
  virtual PObjectBase GetProjectData() = 0;
  
  virtual bool CanUndo() = 0;
  virtual bool CanRedo() = 0;
};

/**
 * Interfaz para manejar los eventos de notificación del modelo de datos
 */
class DataObserver
{
 private:
  DataObservable *m_data;  
   
 public:
  
  DataObserver() { m_data = NULL; }  
  virtual ~DataObserver() {};

  // Establece el objeto observable
  void SetData(DataObservable *data) { m_data = data; };
  DataObservable *GetData() { return m_data; }
  
  virtual void ProjectLoaded() {}
  virtual void ProjectSaved() {}
  virtual void ObjectSelected(PObjectBase obj) {}
  virtual void ObjectCreated(PObjectBase obj) {}
  virtual void ObjectRemoved(PObjectBase obj) {}
  virtual void PropertyModified(PProperty prop) {}
  virtual void ProjectRefresh() {}
  virtual void CodeGeneration() {}
};


#endif //__APP_OBSERVER__
