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

#ifndef __OBJECTS__
#define __OBJECTS__

#include "objectbase.h"

class SizerObject;
class WidgetObject;
class FormObject;
class ProjectObject;

typedef shared_ptr<SizerObject> PSizerObject;
typedef shared_ptr<ProjectObject> PProjectObject;
typedef shared_ptr<FormObject> PFormObject;
typedef shared_ptr<WidgetObject> PWidgetObject;

/*
class Sizerable
{
 public:
  virtual PObjectBase GetLayout() = 0;
};*/  

class SizerObject : public ObjectBase
{
 public:
  SizerObject(string class_name); 
  
  virtual PObjectBase GetLayout();
  bool ChildTypeOk (ObjectType type);
};



  
class WidgetObject : public ObjectBase
{
 public:
  WidgetObject(string class_name); 

  virtual bool IsContainer();
  PSizerObject GetSizer();
  void SetSizer(PSizerObject sizer);
  void RemoveSizer();

  // si el widget tiene asociada información de layout
  virtual PObjectBase GetLayout();
  
  bool ChildTypeOk (ObjectType type);
};
/*
class ContainerObject : public ObjectBase
{
 public:
  ContainerObject   
};*/

class FormObject : public WidgetObject
{
 public:
  FormObject(string class_name); 
  
  bool IsContainer() { return true; }

  bool ChildTypeOk (ObjectType type);
};
  
class ProjectObject : public ObjectBase
{
 public:
  ProjectObject(string class_name);

  bool ChildTypeOk (ObjectType type);
};

class ComponentObject : public ObjectBase
{
 public:
  ComponentObject(string class_name);
  
  bool ChildTypeOk (ObjectType type) { return false; };
};  
  
  

#endif //__OBJECTS__

