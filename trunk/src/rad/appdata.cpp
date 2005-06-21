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

#include "appdata.h"
#include "utils/typeconv.h"
#include "utils/debug.h"
#include "codegen/codegen.h"

using namespace TypeConv;


///////////////////////////////////////////////////////////////////////////////
// Comandos
///////////////////////////////////////////////////////////////////////////////

/**
 * Comando para insertar un objeto en el árbol.
 */
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

/**
 * Comando para borrar un objeto.
 */
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

/**
 * Comando para modificar una propiedad.
 */
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

/**
 * Comando para mover de posición un objeto.
 */
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

/**
 * CutObjectCmd ademas de eliminar el objeto del árbol se asegura
 * de eliminar la referencia "clipboard" deshacer el cambio.
 */
class CutObjectCmd : public Command
{
 private:
  // necesario para consultar/modificar el objeto "clipboard"
  ApplicationData *m_data;
  //PObjectBase m_clipboard;
  PObjectBase m_parent;
  PObjectBase m_object;
  int m_oldPos;
  
 protected:
  void DoExecute();
  void DoRestore();
  
 public:
  CutObjectCmd(PObjectBase object, ApplicationData *data);
};

///////////////////////////////////////////////////////////////////////////////
// Implementación de los Comandos
///////////////////////////////////////////////////////////////////////////////

InsertObjectCmd::InsertObjectCmd(PObjectBase object, PObjectBase parent, int pos)
  : m_parent(parent), m_object(object), m_pos(pos)
{}

void InsertObjectCmd::DoExecute()
{
  m_parent->AddChild(m_object);
  m_object->SetParent(m_parent);
  
  if (m_pos >= 0)
    m_parent->ChangeChildPosition(m_object,m_pos);
}

void InsertObjectCmd::DoRestore()
{
  m_parent->RemoveChild(m_object);
  m_object->SetParent(PObjectBase());
}

//-----------------------------------------------------------------------------

RemoveObjectCmd::RemoveObjectCmd(PObjectBase object)
{
  m_object = object;
  m_parent = object->GetParent();
  m_oldPos = m_parent->GetChildPosition(object);
}

void RemoveObjectCmd::DoExecute()
{
  m_parent->RemoveChild(m_object);
  m_object->SetParent(PObjectBase());
}

void RemoveObjectCmd::DoRestore()
{
  m_parent->AddChild(m_object);
  m_object->SetParent(m_parent);
  
  // restauramos la posición
  m_parent->ChangeChildPosition(m_object,m_oldPos);  
}

//-----------------------------------------------------------------------------

ModifyPropertyCmd::ModifyPropertyCmd(PProperty prop, string value)
  : m_property(prop), m_newValue(value)
{
  m_oldValue = prop->GetValue();
}

void ModifyPropertyCmd::DoExecute()
{
  m_property->SetValue(m_newValue);
}

void ModifyPropertyCmd::DoRestore()
{
  m_property->SetValue(m_oldValue);
}

//-----------------------------------------------------------------------------

ShiftChildCmd::ShiftChildCmd(PObjectBase object, int pos)
{
  m_object = object;
  PObjectBase parent = object->GetParent();
  
  assert(parent);
  
  m_oldPos = parent->GetChildPosition(object);
  m_newPos = pos;
}

void ShiftChildCmd::DoExecute()
{
  if (m_oldPos != m_newPos)
  {
    PObjectBase parent (m_object->GetParent());
    parent->ChangeChildPosition(m_object,m_newPos);
  }
}

void ShiftChildCmd::DoRestore()
{
  if (m_oldPos != m_newPos)
  {
    PObjectBase parent (m_object->GetParent());
    parent->ChangeChildPosition(m_object,m_oldPos);
  }
}

//-----------------------------------------------------------------------------

CutObjectCmd::CutObjectCmd(PObjectBase object, ApplicationData *data)
{
  m_data = data;
  m_object = object;
  m_parent = object->GetParent();
  m_oldPos = m_parent->GetChildPosition(object);
}

void CutObjectCmd::DoExecute()
{
  // guardamos el clipboard ???
  //m_clipboard = m_data->GetClipboardObject();
  
  m_data->SetClipboardObject(m_object);
  m_parent->RemoveChild(m_object);
  m_object->SetParent(PObjectBase());
}

void CutObjectCmd::DoRestore()
{
  // reubicamos el objeto donde estaba
  m_parent->AddChild(m_object);
  m_object->SetParent(m_parent);
  m_parent->ChangeChildPosition(m_object,m_oldPos);  
  
  // restauramos el clipboard
  //m_data->SetClipboardObject(m_clipboard);
  m_data->SetClipboardObject(PObjectBase());
}

///////////////////////////////////////////////////////////////////////////////
// ApplicationData
///////////////////////////////////////////////////////////////////////////////

ApplicationData::ApplicationData()
{
  m_objDb = PObjectDatabase(new ObjectDatabase());
  m_objDb->SetXmlPath("./xml/");
  m_objDb->SetIconPath("./xpm/");
  m_objDb->LoadObjectTypes();
  m_objDb->LoadFile();
}  
  
PObjectBase ApplicationData::GetSelectedObject()
{
  return m_selObj;
}  

PObjectBase ApplicationData::GetSelectedForm()
{
  if (m_selObj->GetObjectTypeName() == "form")
    return m_selObj;
  else
    return m_selObj->FindNearAncestor("form");
}
  

PObjectBase ApplicationData::GetProjectData()
{
  return m_project;
}  

void ApplicationData::BuildNameSet(PObjectBase obj, PObjectBase top, set<string> &name_set)
{
  if (obj != top)
  {
    PProperty nameProp = top->GetProperty("name");
    if (nameProp)
      name_set.insert(nameProp->GetValue());
  }
  
  for (unsigned int i=0; i< top->GetChildCount(); i++)
    BuildNameSet(obj, top->GetChild(i), name_set);  
}

void ApplicationData::ResolveNameConflict(PObjectBase obj)
{
  while (obj && obj->GetObjectInfo()->GetObjectType()->IsItem())
  {
    if (obj->GetChildCount() > 0)
      obj = obj->GetChild(0);
    else
      return;
  }
  
  PProperty nameProp = obj->GetProperty("name");
  if (!nameProp)
    return;
  
  string name = nameProp->GetValue();
    
  // el nombre no puede estar repetido dentro del mismo form
  PObjectBase top = obj->FindNearAncestor("form");
  if (!top)
    top = m_project; // el objeto es un form.
  
  // construimos el conjunto de nombres  
  set<string> name_set;
  BuildNameSet(obj, top, name_set);
  
  // comprobamos si hay conflicto
  set<string>::iterator it = name_set.find(name);
  while (it != name_set.end())
  {
    name = name + "_";
    it = name_set.find(name);
  }
  
  nameProp->SetValue(name);
}

int ApplicationData::CalcPositionOfInsertion(PObjectBase selected,PObjectBase parent)
{
  int pos = -1;
  
  if (parent && selected)
  {
    PObjectBase parentSelected = selected->GetParent();
    while (parentSelected && parentSelected != parent)
    {
      selected = parentSelected;
      parentSelected = selected->GetParent();
    }
    
    if (parentSelected && parentSelected == parent)
      pos = parent->GetChildPosition(selected) + 1;
  }
  
  return pos;
}

void ApplicationData::RemoveEmptyItems(PObjectBase obj)
{
  if (!obj->GetObjectInfo()->GetObjectType()->IsItem())
  {
    bool emptyItem = true;
    
    // esto es un algoritmo ineficiente pero "seguro" con los índices
    while (emptyItem)
    {
      emptyItem = false;
      for (unsigned int i=0; !emptyItem && i<obj->GetChildCount(); i++)
      {
        PObjectBase child = obj->GetChild(i);
        if (child->GetObjectInfo()->GetObjectType()->IsItem() &&
            child->GetChildCount() == 0)
        {
          obj->RemoveChild(child); // borramos el item
          child->SetParent(PObjectBase());
          
          emptyItem = true;        // volvemos a recorrer 
          wxLogWarning(wxT("Empty item removed"));
        }
      }
    }
  }
  
  for (unsigned int i=0; i<obj->GetChildCount() ; i++)
    RemoveEmptyItems(obj->GetChild(i));
}    

///////////////////////////////////////////////////////////////////////////////

void ApplicationData::SelectObject(PObjectBase obj)
{
  Debug::Print("Object Selected!");
  m_selObj = obj;
/*  
  if (obj->GetObjectType() != T_FORM)
  {
    m_selForm = shared_dynamic_cast<FormObject>(obj->FindNearAncestor(T_FORM));
  }
  else
    m_selForm = shared_dynamic_cast<FormObject>(obj);*/
    
  DataObservable::NotifyObjectSelected(obj);
}
  
void ApplicationData::CreateObject(wxString name)
{
  Debug::Print("ApplicationData::CreateObject] New %s",name.c_str());

  PObjectBase parent = GetSelectedObject();
  PObjectBase obj;
  if (parent)
  {
    bool created = false;
    
    // Para que sea más práctico, si el objeto no se puede crear debajo
    // del objeto seleccionado vamos a intentarlo en el padre del seleccionado
    // y seguiremos subiendo hasta que ya no podamos crear el objeto.
    while (parent && !created)
    {
      // además, el objeto se insertará a continuación del objeto seleccionado
      obj = m_objDb->CreateObject(string(name.mb_str()),parent);
      
      if (obj)
      {
        int pos = CalcPositionOfInsertion(GetSelectedObject(),parent);
        
        PCommand command(new InsertObjectCmd(obj,parent,pos));
        m_cmdProc.Execute(command);
        created = true;
        ResolveNameConflict(obj);
      }
      else
      {
        // lo vamos a seguir intentando con el padre, pero cuidado, el padre
        // no puede ser un item!
        parent = parent->GetParent();
        while (parent && parent->GetObjectInfo()->GetObjectType()->IsItem())
          parent = parent->GetParent();
      }
    }
  }  
  
  DataObservable::NotifyObjectCreated(obj);

  // Seleccionamos el objeto, si este es un item entonces se selecciona
  // el objeto contenido. ¿Tiene sentido tener un item debajo de un item?
  while (obj && obj->GetObjectInfo()->GetObjectType()->IsItem())
    obj = ( obj->GetChildCount() > 0 ? obj->GetChild(0) : PObjectBase());
  
  if (obj)
    SelectObject(obj);
}
  
void ApplicationData::RemoveObject(PObjectBase obj)
{
  DoRemoveObject(obj,false);
}

void ApplicationData::CutObject(PObjectBase obj)
{
  DoRemoveObject(obj,true);
}

void ApplicationData::DoRemoveObject(PObjectBase obj, bool cutObject)
{
  // Nota:
  //  cuando se va a eliminar un objeto es importante que no se dejen
  //  nodos ficticios ("items") en las hojas del árbol.
  PObjectBase parent = obj->GetParent();
  if (parent)
  {  
    while (parent && parent->GetObjectInfo()->GetObjectType()->IsItem())
    {
      obj = parent;
      parent = obj->GetParent();
    }

    if (cutObject)
    {
      m_copyOnPaste = false;
      PCommand command(new CutObjectCmd(obj,this));
      m_cmdProc.Execute(command);
    }
    else
    {
      PCommand command(new RemoveObjectCmd(obj));
      m_cmdProc.Execute(command);
    }

    DataObservable::NotifyObjectRemoved(obj);
  
    // "parent" será el nuevo objeto seleccionado tras eliminar obj.
    SelectObject(parent);
  }
  else
  {
    if (obj->GetObjectTypeName()!="project")
      assert(false); 
  }
  
  CheckProjectTree(m_project);
}

void ApplicationData::CopyObject(PObjectBase obj)
{
  m_copyOnPaste = true;
    
  // Hacemos una primera copia del objeto, ya que si despues de copiar
  // el objeto se modificasen las propiedades, dichas modificaciones se verian
  // reflejadas en la copia.
  m_clipboard = m_objDb->CopyObject(obj);
  
  CheckProjectTree(m_project);
}

void ApplicationData::PasteObject(PObjectBase parent)
{ 
  if (m_clipboard)
  {
    // Vamos a hacer un pequeño truco, intentaremos crear un objeto nuevo
    // del mismo tipo que el guardado en m_clipboard debajo de parent.
    // El objeto devuelto quizá no sea de la misma clase que m_clipboard debido
    // a que esté incluido dentro de un "item".
    // Por tanto, si el objeto devuelto es no-nulo, entonces vamos a descender
    // en el arbol hasta que el objeto sea de la misma clase que m_clipboard,
    // momento en que cambiaremos dicho objeto por m_clipboard.
    //
    // Ejemplo:
    //
    //  m_clipboard :: wxButton
    //  parent      :: wxBoxSizer
    //
    //  obj = CreateObject(m_clipboard->GetObjectInfo()->GetClassName(), parent)
    //
    //  obj :: sizeritem
    //              /
    //           wxButton   <- Cambiamos este por m_clipboard
    PObjectBase old_parent = parent;
    
    PObjectBase obj = 
      m_objDb->CreateObject(m_clipboard->GetObjectInfo()->GetClassName(), parent);
    
    int pos = -1;
    
    if (!obj)
    {
      // si no se ha podido crear el objeto vamos a intentar crearlo colgado
      // del padre de "parent" y además vamos a insertarlo en la posición
      // siguiente a "parent"
      PObjectBase selected = parent;
      parent = selected->GetParent();
      while (parent && parent->GetObjectInfo()->GetObjectType()->IsItem())
      {
        selected = parent;
        parent = selected->GetParent();
      }
      
      if (parent)
      {
        obj = m_objDb->CreateObject(m_clipboard->GetObjectInfo()->GetClassName(), parent);
        
        if (obj)
          pos = CalcPositionOfInsertion(selected,parent);
      }
    }
    
    if (obj)
    {
      PObjectBase clipboard(m_clipboard);
      if (m_copyOnPaste)
        clipboard = m_objDb->CopyObject(m_clipboard);
    
      PObjectBase aux = obj;
      while (aux && aux->GetObjectInfo() != clipboard->GetObjectInfo())
        aux = ( aux->GetChildCount() > 0 ? aux->GetChild(0) : PObjectBase());
        
      if (aux && aux != obj)
      {
        // sustituimos aux por clipboard
        PObjectBase auxParent = aux->GetParent();
        auxParent->RemoveChild(aux);
        aux->SetParent(PObjectBase());
        
        auxParent->AddChild(clipboard);
        clipboard->SetParent(auxParent);
      }
      else
        obj = clipboard;
        
      // y finalmente insertamos en el arbol 
      PCommand command(new InsertObjectCmd(obj,parent,pos));
      m_cmdProc.Execute(command);
      
      if (!m_copyOnPaste)
        m_clipboard.reset();
    
      DataObservable::NotifyProjectRefresh();
      
      // vamos a mantener seleccionado el nuevo objeto creado
      // pero hay que tener en cuenta que es muy probable que el objeto creado
      // sea un "item"
      while (obj && obj->GetObjectInfo()->GetObjectType()->IsItem())
      {
        assert(obj->GetChildCount() > 0);
        obj = obj->GetChild(0);
      }
    
      SelectObject(obj);    
    }
  }
  
  CheckProjectTree(m_project);
}

void ApplicationData::InsertObject(PObjectBase obj, PObjectBase parent)
{
  // FIXME! comprobar obj se puede colgar de parent
//  if (parent->GetObjectInfo()->GetObjectType()->FindChildType(
//    obj->GetObjectInfo()->GetObjectType()))
//  {
    PCommand command(new InsertObjectCmd(obj,parent));
    m_cmdProc.Execute(command);  
    DataObservable::NotifyProjectRefresh(); 
//  }
}

void ApplicationData::MergeProject(PObjectBase project)
{
  // FIXME! comprobar obj se puede colgar de parent
  for (unsigned int i=0; i<project->GetChildCount(); i++)
  {
    //m_project->AddChild(project->GetChild(i));
    //project->GetChild(i)->SetParent(m_project);
    
    PObjectBase child = project->GetChild(i);
    RemoveEmptyItems(child);
    
    InsertObject(child,m_project);
  }
  DataObservable::NotifyProjectRefresh(); 
}
  
void ApplicationData::ModifyProperty(PProperty prop, wxString str)
{
  PObjectBase object = prop->GetObject();
  
  if (_STDSTR(str) != prop->GetValue())
  {
    PCommand command(new ModifyPropertyCmd(prop,_STDSTR(str)));
    m_cmdProc.Execute(command);

    DataObservable::NotifyPropertyModified(prop);
  }  
}
  

void ApplicationData::SaveProject(const wxString &filename)
{
  TiXmlDocument *doc = m_project->Serialize();
  doc->SaveFile(filename.mb_str());
  m_projectFile = _STDSTR(filename);
  delete doc;
  
  DataObservable::NotifyProjectSaved();
}  

bool ApplicationData::LoadProject(const wxString &file)
{
  Debug::Print("LOADING");
  
  bool result = false;
  
  TiXmlDocument *doc = new TiXmlDocument();
  if (doc->LoadFile(file.mb_str()))
  {
    m_objDb->ResetObjectCounters();
    
    TiXmlElement *root = doc->RootElement();
    PObjectBase proj = m_objDb->CreateObject(root);
    if (proj && proj->GetObjectTypeName()== "project")
    {
      PObjectBase old_proj = m_project;
      //m_project = shared_dynamic_cast<ProjectObject>(proj);
      m_project = proj;
      m_selObj = m_project;
      result = true;
      m_cmdProc.Reset();
      m_projectFile = _STDSTR(file);
      DataObservable::NotifyProjectLoaded();
    }
  }
  delete doc;  
 
  return result;
}

void ApplicationData::NewProject()
{
  m_project = m_objDb->CreateObject("Project");
  m_selObj = m_project;
  m_cmdProc.Reset();
  DataObservable::NotifyProjectRefresh();  
}

void ApplicationData::GenerateCode()
{
  DataObservable::NotifyCodeGeneration();
}


void ApplicationData::MovePosition(PObjectBase obj, bool right, unsigned int num)
{
  PObjectBase noItemObj = obj;
  
  PObjectBase parent = obj->GetParent();
  if (parent)
  {
    // Si el objeto está incluido dentro de un item hay que desplazar
    // el item
    while (parent && parent->GetObjectInfo()->GetObjectType()->IsItem())
    {
      obj = parent;
      parent = obj->GetParent();
    }
        
    unsigned int pos = parent->GetChildPosition(obj);
    
    // nos aseguramos de que los límites son correctos
    
    unsigned int children_count = parent->GetChildCount();
    
    if ((right && num + pos < children_count) ||
        !right  && (num <= pos))
    {
      pos = (right ? pos+num : pos-num);
      
      PCommand command(new ShiftChildCmd(obj,pos));
      m_cmdProc.Execute(command);
      DataObservable::NotifyProjectRefresh();
      SelectObject(noItemObj); 
    }
  }
}

void ApplicationData::Undo()
{
  m_cmdProc.Undo();
  DataObservable::NotifyProjectRefresh();
  CheckProjectTree(m_project);
}

void ApplicationData::Redo()
{
  m_cmdProc.Redo();
  DataObservable::NotifyProjectRefresh();
  CheckProjectTree(m_project);
}


void ApplicationData::ToggleExpandLayout(PObjectBase obj)
{
  if (obj)
  {
    PObjectBase parent = obj->GetParent();
    if (parent && parent->GetObjectTypeName() == "sizeritem")
    {
      PProperty propFlag = parent->GetProperty("flag");
      assert(propFlag);
      
      wxString value;
      wxString currentValue = propFlag->GetValueAsString();
      
      value = 
        (TypeConv::FlagSet(wxT("wxEXPAND"),currentValue) ?
         TypeConv::ClearFlag(wxT("wxEXPAND"),currentValue) :
         TypeConv::SetFlag(wxT("wxEXPAND"),currentValue));
         
      ModifyProperty(propFlag,value);
    }
  }
}

void ApplicationData::ToggleStretchLayout(PObjectBase obj)
{
  if (obj)
  {
    PObjectBase parent = obj->GetParent();
    if (parent && parent->GetObjectTypeName() == "sizeritem")
    {
      PProperty propOption = parent->GetProperty("option");
      assert(propOption);
      
      string value = ( propOption->GetValue() == "1" ? "0" : "1");
      
      ModifyProperty(propOption, _WXSTR(value));
    }
  }
}

void ApplicationData::CheckProjectTree(PObjectBase obj)
{
  assert(obj);
  for (unsigned int i=0; i< obj->GetChildCount(); i++)
  {
    PObjectBase child = obj->GetChild(i);
    if (child->GetParent() != obj)
      wxLogError(wxString::Format(wxT("Parent of object \'%s\' is wrong!"),child->GetPropertyAsString(wxT("name")).mb_str()));
      
    CheckProjectTree(child);
  }
}

string ApplicationData::GetProjectPath()
{
  return _STDSTR(::wxPathOnly(_WXSTR(m_projectFile)));
}

//////////////////////////////////////////////////////////////////////////////
