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

#include "appdata.h"
#include "utils/typeconv.h"
#include "utils/debug.h"
#include "codegen/codegen.h"

using namespace TypeConv;

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
      obj = m_objDb->CreateObject(string(name.mb_str()),parent);
      if (obj)
      {    
        PCommand command(new InsertObjectCmd(obj,parent));
        m_cmdProc.Execute(command);
        created = true;
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
  // Nota:
  //  cuando se va a eliminar un objeto es importante que no se dejen
  //  nodos ficticios ("items") en las hojas del árbol.
  PObjectBase parent = obj->GetParent();
  while (parent && parent->GetObjectInfo()->GetObjectType()->IsItem())
  {
    obj = parent;
    parent = obj->GetParent();
  }

  PCommand command(new RemoveObjectCmd(obj));
  m_cmdProc.Execute(command);

  DataObservable::NotifyObjectRemoved(obj);
  
  // "parent" será el nuevo objeto seleccionado tras eliminar obj.
  SelectObject(parent);
}

void ApplicationData::CutObject(PObjectBase obj)
{
  m_clipboard = obj;
  RemoveObject(obj);
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
    PObjectBase obj = 
      m_objDb->CreateObject(m_clipboard->GetObjectInfo()->GetClassName(), parent);
    
    if (obj)
    {
      PObjectBase aux = obj;
      while (aux && aux->GetObjectInfo() != m_clipboard->GetObjectInfo())
        aux = ( aux->GetChildCount() > 0 ? aux->GetChild(0) : PObjectBase());
        
      if (aux && aux != obj)
      {
        // sustituimos aux por m_clipboard
        PObjectBase auxParent = aux->GetParent();
        auxParent->RemoveChild(aux);
        aux->SetParent(PObjectBase());
        
        auxParent->AddChild(m_clipboard);
        m_clipboard->SetParent(auxParent);
      }
      else
        obj = m_clipboard;
        
      // y finalmente insertamos en el arbol        
      PCommand command(new InsertObjectCmd(obj,parent));
      m_cmdProc.Execute(command);
        
      m_clipboard.reset();
      
    }
    DataObservable::NotifyProjectRefresh();
  }
}

void ApplicationData::InsertObject(PObjectBase obj, PObjectBase parent)
{
  // FIXME! comprobar obj se puede colgar de parent
  PCommand command(new InsertObjectCmd(obj,parent));
  m_cmdProc.Execute(command);  
  DataObservable::NotifyProjectRefresh(); 
}

void ApplicationData::MergeProject(PObjectBase project)
{
  // FIXME! comprobar obj se puede colgar de parent
  for (unsigned int i=0; i<project->GetChildCount(); i++)
  {
    //m_project->AddChild(project->GetChild(i));
    //project->GetChild(i)->SetParent(m_project);
    InsertObject(project->GetChild(i),m_project);
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
    }
  }
}

void ApplicationData::Undo()
{
  m_cmdProc.Undo();
  DataObservable::NotifyProjectRefresh();
}

void ApplicationData::Redo()
{
  m_cmdProc.Redo();
  DataObservable::NotifyProjectRefresh();
}


//////////////////////////////////////////////////////////////////////////////
InsertObjectCmd::InsertObjectCmd(PObjectBase object, PObjectBase parent)
  : m_parent(parent), m_object(object)
{}

void InsertObjectCmd::DoExecute()
{
  m_parent->AddChild(m_object);
  m_object->SetParent(m_parent);
}

void InsertObjectCmd::DoRestore()
{
  m_parent->RemoveChild(m_object);
  m_object->SetParent(PObjectBase());
}

//-----------------

RemoveObjectCmd::RemoveObjectCmd(PObjectBase object)
{
  m_object = object;
  m_parent = object->GetParent();
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
}

//-----------------

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

//-----------------

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
