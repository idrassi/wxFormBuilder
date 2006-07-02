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

#include "objects.h"

SizerObject::SizerObject(string class_name)
  : ObjectBase(class_name)
{
  SetObjectType(T_SIZER);
}


PObjectBase SizerObject::GetLayout()
{
  PObjectBase result;
  
  if (GetParent() != NULL && GetParent()->GetObjectType()==T_SIZERITEM)
    result = GetParent();
    
  return result;
}  

bool SizerObject::ChildTypeOk (ObjectType type)
{
  bool result = false;
  
  if (type == T_SIZERITEM)
    result = true;
   
  
  return result;
}  

///////////////////////////////////////////////////////////////////////////////

WidgetObject::WidgetObject(string class_name)
  : ObjectBase(class_name)
{
  SetObjectType(T_WIDGET);
}

bool WidgetObject::ChildTypeOk (ObjectType type)
{
  bool result = false;
  
  if (IsContainer() &&
     (!GetSizer() && type == T_WIDGET || type == T_SIZER && GetChildCount()==0))
    result = true;
    
  return result;
}
  

void WidgetObject::SetSizer(PSizerObject sizer)
{
  ObjectVector::iterator it =  GetChildren().begin();
  if (it != GetChildren().end())
  {
    for ( ; it != GetChildren().end(); it++)
    {
      PObjectBase obj = *it;
      obj->SetParent(sizer);
      sizer->AddChild(obj);
    }
    
    // borramos todos los hijos
    GetChildren().erase(GetChildren().begin(), GetChildren().end());
  }
  ObjectBase::AddChild(sizer);
  sizer->SetParent(PObjectBase(this));
}

void WidgetObject::RemoveSizer()
{
}  

PSizerObject WidgetObject::GetSizer()
{
  PSizerObject result;
  
  if (GetChildCount() == 1 && GetChild(0)->GetObjectType() == T_SIZER)
  {
    result = shared_dynamic_cast<SizerObject>(GetChild(0)); 
  }
    
  return result;
}  

bool WidgetObject::IsContainer()
{
  // esto es un parche provisional!
  if (GetClassName() == "wxPanel")
    return true;
    
  // To-Do hay que crear un tipo nuevo de Widget (ContainerObject)
  // que sea capaz de contener nuevos widgets
  
    
  return false;
}  

PObjectBase WidgetObject::GetLayout()
{
  PObjectBase result;
  
  if (GetParent() && GetParent()->GetObjectType()==T_SIZERITEM)
    result = GetParent();
    
  return result;
}  

///////////////////////////////////////////////////////////////////////////////

FormObject::FormObject(string class_name)
  : WidgetObject(class_name)
{
  SetObjectType(T_FORM);
}


bool FormObject::ChildTypeOk (ObjectType type)
{
  bool result = false;
  
  if (type == T_COMPONENT)
    result = true;
  else
    result = WidgetObject::ChildTypeOk(type);
    
  return result;
}  


///////////////////////////////////////////////////////////////////////////////

ProjectObject::ProjectObject(string class_name)
  : ObjectBase(class_name)
{
  SetObjectType(T_PROJECT);
}


bool ProjectObject::ChildTypeOk (ObjectType type)
{
  bool result = false;
  if (type == T_FORM)
    result = true;
  
  return result; 
}
 
///////////////////////////////////////////////////////////////////////////////


ComponentObject::ComponentObject(string class_name)
  : ObjectBase(class_name)
{
  SetObjectType(T_COMPONENT);
}

