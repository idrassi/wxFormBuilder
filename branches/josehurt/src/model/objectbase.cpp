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

#include "objectbase.h"
#include "wx/wx.h"
#include "utils/debug.h"
#include "utils/typeconv.h"

#include <sstream>
int ObjectBase::s_instances = 0;

string OptionList::GetOption(unsigned int idx)
{
  assert (idx < m_options.size());
  
  return m_options[idx];
}

ostream& operator << (ostream &s, ObjectType type)
{
  switch (type)
  {
    case T_WIDGET:
      s << "T_WIDGET";
      break;
    case T_SIZER:
      s << "T_SIZER";
      break;
    case T_FORM:
      s << "T_FORM";
      break;
    case T_SPACER:
      s << "T_SPACER";
      break;
    case T_SIZERITEM:
      s << "T_SIZERITEM";
      break;
    case T_ERROR:
      s << "T_ERROR";
      break;
    case T_INTERFACE:
      s << "T_INTERFACE";
      break;
    case T_COMPONENT:
      s << "T_COMPONENT";
      break;
    case T_PROJECT:
      s << "T_PROJECT";
      break;

  }
  return s;
}



PropertyInfo::PropertyInfo(string name, PropertyType type, string def_value,
                           bool hidden, POptionList opt_list)
{
  m_name = name;
  m_type = type;
  m_def_value = def_value;
  m_hidden = hidden;    //Juan
  m_opt_list = opt_list;
}

PropertyInfo::~PropertyInfo()
{
// Se acabaron los delete's  
//  if (m_opt_list)
//    delete m_opt_list;
}

bool Property::IsDefaultValue()
{
//  return (m_info->GetDefaultValue() == m_value.AsStdString());
  return (m_info->GetDefaultValue() == m_value);
}

void Property::SetDefaultValue()
{
//  m_value = TVariant(GetType(),m_info->GetDefaultValue());
  m_value = m_info->GetDefaultValue();
}

void Property::SetValue(const wxFont &font)
{
  m_value = _STDSTR(TypeConv::FontToString(font));
}
void Property::SetValue(const wxColour &colour)
{
  m_value = _STDSTR(TypeConv::ColourToString(colour));
}
void Property::SetValue(const wxString &str)
{
  m_value = _STDSTR(str);
}

void Property::SetValue(const wxPoint &point)
{
    m_value = _STDSTR(TypeConv::PointToString(point));
}

void Property::SetValue(const wxSize &size)
{
  m_value = _STDSTR(TypeConv::SizeToString(size));
}

wxFont Property::GetValueAsFont()
{
  return TypeConv::StringToFont(_WXSTR(m_value));
}

wxColour Property::GetValueAsColour()
{
  return TypeConv::StringToColour(_WXSTR(m_value));
}
wxPoint Property::GetValueAsPoint()
{
  return TypeConv::StringToPoint(_WXSTR(m_value));
}
wxSize Property::GetValueAsSize()
{
  return TypeConv::StringToSize(_WXSTR(m_value));
}

wxBitmap Property::GetValueAsBitmap()
{
  return TypeConv::StringToBitmap(_WXSTR(m_value));
}

int Property::GetValueAsInteger()
{
  int result = 0;

  switch (GetType())
  {
    case PT_OPTION:
    case PT_MACRO:
      result = TypeConv::GetMacroValue(_WXSTR(m_value));
      break;
    case PT_BITLIST:
      result = TypeConv::BitlistToInt(_WXSTR(m_value));
      break;
    default:
      result = TypeConv::StringToInt(_WXSTR(m_value));
      break;
  }
  return result;
}

wxString Property::GetValueAsString()
{
  return _WXSTR(m_value);
}
///////////////////////////////////////////////////////////////////////////////
const int ObjectBase::INDENT = 2;

ObjectBase::ObjectBase (string class_name)
{
  s_instances++;
  
  m_class = class_name;
  
  Debug::Print("new ObjectBase (%d)",s_instances);
}

/*
PObjectBase ObjectBase::NewInstance (string class_name, PObjectBase parent)
{
  PObjectBase _this(new ObjectBase(class_name));

  _this->SetupInstance(parent);
  
  return _this;
}

void ObjectBase::SetupInstance(PObjectBase parent)
{
  //  this->ObjectDocument::SetupInstance();
  
  if (parent)
  {
    parent->AddChild(GetThis());
    this->SetParent(parent);
  }
}*/

ObjectBase::~ObjectBase()
{
  s_instances--;
  
  // eliminamos la referencia en el padre
  PObjectBase parent = m_parent.lock();

  if (parent)
  {
    PObjectBase pobj(GetThis());
    parent->RemoveChild(pobj);
  }

  Debug::Print("delete ObjectBase (%d)",s_instances);
}

string ObjectBase::GetIndentString(int indent)
{
  int i;
  string s;
  
  for (i=0;i<indent;i++)
    s += " ";

  return s;
}


PProperty ObjectBase::GetProperty (string name)
{
  PProperty result;
  
  PropertyMap::iterator it = m_properties.find(name);
  if (it != m_properties.end())
    result = it->second;
  else
  {
    Debug::Print("[ObjectBase::GetProperty] Property %s not found!",name.c_str());
    // este aserto falla siempre que se crea un sizeritem
    // assert(false);
  }

  return result;
}

PProperty ObjectBase::GetProperty (unsigned int idx)
{
  PProperty result;
  
  assert (idx < m_properties.size());
  
  PropertyMap::iterator it = m_properties.begin();
  unsigned int i = 0;
  while (i < idx && it != m_properties.end())
  {
    i++;
    it++;
  }
      
  if (it != m_properties.end())
    result = it->second;
    
  return result;
}

void ObjectBase::AddProperty (string propname, PProperty value)
{
  m_properties.insert(PropertyMap::value_type(propname,value));
}


PObjectBase ObjectBase::FindNearAncestor(ObjectType type)
{
  PObjectBase result;
  PObjectBase parent = GetParent();
  if (parent)
  {
    if (parent->GetObjectType() == type)
      result = parent;
    else
      result = parent->FindNearAncestor(type);
  }
  
  return result;
}

bool ObjectBase::AddChild (PObjectBase obj)
{
  bool result = false;
  if (ChildTypeOk(obj->GetObjectType()))
  {
    m_children.push_back(obj);
    result = true;
  }  

  return result;
}

bool ObjectBase::AddChild (unsigned int idx, PObjectBase obj)
{
  bool result = false;
  if (ChildTypeOk(obj->GetObjectType()) && idx <= m_children.size())
  {
    m_children.insert(m_children.begin() + idx,obj);
    result = true;
  }  
  
  return result;
}

void ObjectBase::RemoveChild (PObjectBase obj)
{
  ObjectVector::iterator it =  m_children.begin();
  while (it != m_children.end() && *it != obj)
    it++;
    
  if (it != m_children.end())
    m_children.erase(it);  
} 

void ObjectBase::RemoveChild (unsigned int idx)
{
  assert (idx < m_children.size());
    
  ObjectVector::iterator it =  m_children.begin() + idx;
  m_children.erase(it);
}

PObjectBase ObjectBase::GetChild (unsigned int idx)
{
  assert (idx < m_children.size());
    
  return m_children[idx];
}

void ObjectBase::PrintOut(ostream &s, int indent)
{
  string ind_str = GetIndentString(indent);
    
  s << ind_str << "[ " << GetClassName() << " ] " << GetObjectType() << endl;
  PropertyMap::const_iterator it_prop;
  for (it_prop = m_properties.begin(); it_prop!= m_properties.end(); it_prop++)
  {
    s << ind_str << "property '" << it_prop->first << "' = '" <<
      it_prop->second->GetValue() << "'" << endl;
  }  

  ObjectVector::const_iterator it_ch;
  for (it_ch = m_children.begin() ; it_ch != m_children.end(); it_ch++)
  {
    (*it_ch)->PrintOut(s,INDENT + indent);
  }  
}

ostream& operator << (ostream &s, PObjectBase obj)
{
  obj->PrintOut(s,0);
  return s;
}

TiXmlElement* ObjectBase::SerializeObject()
{
  TiXmlElement *element = new TiXmlElement("object");
  element->SetAttribute("class",GetClassName());

  for (unsigned int i=0; i< GetPropertyCount(); i++)
  {
    PProperty prop = GetProperty(i);  
    TiXmlElement *prop_element = new TiXmlElement("property");
    prop_element->SetAttribute("name",prop->GetName());
    
    TiXmlText* prop_value = new TiXmlText(prop->GetValue());
    prop_element->LinkEndChild(prop_value);
    element->LinkEndChild(prop_element);
  }
 
  for (unsigned int i=0 ; i < GetChildCount() ; i++)
  {
    PObjectBase child = GetChild(i);  
    TiXmlElement * child_element = child->SerializeObject();
    element->LinkEndChild(child_element);
  }    
  
  return element;
}

TiXmlDocument* ObjectBase::Serialize()
{
  TiXmlDocument *document = new TiXmlDocument("document");
  
  TiXmlElement *element = SerializeObject();
  
  document->LinkEndChild(element);
  return document;        
}    

unsigned int ObjectBase::GetChildPosition(PObjectBase obj)
{
  unsigned int pos = 0;
  while (pos < GetChildCount() && m_children[pos] != obj)
    pos++;
    
  return pos;
}

bool ObjectBase::ChangeChildPosition(PObjectBase obj, unsigned int pos)
{
  unsigned int obj_pos = GetChildPosition(obj);
  
  if (obj_pos == GetChildCount() || pos >= GetChildCount())
    return false;
  
  if (pos == obj_pos)
    return true;
    
  // Procesamos el cambio de posici�n
  RemoveChild(obj);
  AddChild(pos,obj);
  return true;
}

///////////////////////////////////////////////////////////////////////////////
int ObjectBase::GetPropertyAsInteger (const wxString& pname)
{
  PProperty property = GetProperty(_STDSTR(pname));
  if (property)
    return property->GetValueAsInteger();
  else
    return 0;
}

wxFont   ObjectBase::GetPropertyAsFont    (const wxString& pname)
{
  PProperty property = GetProperty(_STDSTR(pname));
  if (property)
    return property->GetValueAsFont();
  else
    return wxFont();
}

wxColour ObjectBase::GetPropertyAsColour  (const wxString& pname)
{
  PProperty property = GetProperty(_STDSTR(pname));
  if (property)
    return property->GetValueAsColour();
  else
    return wxColour();
}

wxString ObjectBase::GetPropertyAsString  (const wxString& pname)
{
  PProperty property = GetProperty(_STDSTR(pname));
  if (property)
    return property->GetValueAsString();
  else
    return wxString();
}

wxPoint  ObjectBase::GetPropertyAsPoint   (const wxString& pname)
{
  PProperty property = GetProperty(_STDSTR(pname));
  if (property)
    return property->GetValueAsPoint();
  else
    return wxPoint();
}

wxSize   ObjectBase::GetPropertyAsSize    (const wxString& pname)
{
  PProperty property = GetProperty(_STDSTR(pname));
  if (property)
    return property->GetValueAsSize();
  else
    return wxSize();
}

wxBitmap ObjectBase::GetPropertyAsBitmap  (const wxString& pname)
{
  PProperty property = GetProperty(_STDSTR(pname));
  if (property)
    return property->GetValueAsBitmap();
  else
    return wxBitmap();
}

wxArrayInt ObjectBase::GetPropertyAsIntegerArray(const wxString& pname)
{
  wxArrayInt array;
  PProperty property = GetProperty(_STDSTR(pname));
  if (property)
  {
    IntList il;
    il.SetList(property->GetValue());
    for (unsigned int i=0; i < il.GetSize() ; i++)
      array.Add(il.GetValue(i));
  }
  
  return array;
}
          
///////////////////////////////////////////////////////////////////////////////

ObjectInfo::ObjectInfo(string class_name,
                       ObjectType type)
//                       WidgetType widget)
{
  m_class = class_name;
//  m_widget = widget;
  m_type = type;
  m_numIns = 0;
  m_component = NULL;
}

PPropertyInfo ObjectInfo::GetPropertyInfo(string name)
{
  PPropertyInfo result;
  
  PropertyInfoMap::iterator it = m_properties.find(name);
  if (it != m_properties.end())
    result = it->second;
    
  return result;
}

PPropertyInfo ObjectInfo::GetPropertyInfo(unsigned int idx)
{
  PPropertyInfo result;
  
  assert (idx < m_properties.size());
  
  PropertyInfoMap::iterator it = m_properties.begin();
  unsigned int i = 0;
  while (i < idx && it != m_properties.end())
  {
    i++;
    it++;
  }
      
  if (it != m_properties.end())
    result = it->second;
    
  return result;
}
void ObjectInfo::AddPropertyInfo(PPropertyInfo prop)
{
  m_properties.insert(PropertyInfoMap::value_type(prop->GetName(), prop));
}


PObjectInfo ObjectInfo::GetBaseClass(unsigned int idx)
{
  assert (idx < m_base.size());
  return m_base[idx];
}  
unsigned int ObjectInfo::GetBaseClassCount()
{
  return m_base.size();
}


void ObjectInfo::PrintOut(ostream &s, int indent)
{
  string ind_str = "";
  for (int i=0;i<indent;i++)
    ind_str = ind_str + " ";
  
  s << ind_str << "[ " << GetClassName() << " ] " << GetObjectType() << endl;
  PropertyInfoMap::const_iterator it_prop;
  for (it_prop = m_properties.begin(); it_prop!= m_properties.end(); it_prop++)
  {
    s << ind_str << "property '" << it_prop->first << "' type = '" <<
      it_prop->second->GetType() << "' with value = '" <<
      it_prop->second->GetDefaultValue() << "' by default" << endl;
  }  
}

void ObjectInfo::AddCodeInfo(string lang, PCodeInfo codeinfo)
{
  m_codeTemp.insert(CodeInfoMap::value_type(lang, codeinfo));
}

PCodeInfo ObjectInfo::GetCodeInfo(string lang)
{
  PCodeInfo result;
  CodeInfoMap::iterator it = m_codeTemp.find(lang);
  if (it != m_codeTemp.end())
    result = it->second;
    
  return result;
}

ostream& operator << (ostream &s, PObjectInfo obj)
{
  obj->PrintOut(s,0);
  return s;
}

///////////////////////////////////////////////////////////////////////////////
string CodeInfo::GetTemplate(string name)
{
  string result;
  
  TemplateMap::iterator it = m_templates.find(name);
  if (it != m_templates.end())
    result = it->second;
    
  return result;
}

void CodeInfo::AddTemplate(string name, string _template)
{
  m_templates.insert(TemplateMap::value_type(name,_template));
}


