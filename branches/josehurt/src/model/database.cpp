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
// A�adir atributo hidden
// Juan Antonio Ortega (jortegalalmolda@gmail.com)

#include "database.h"
#include "objects.h"
#include "utils/stringutils.h"
#include "utils/typeconv.h"
#include "utils/debug.h"

//#define DEBUG_PRINT(x) cout << x

#define OBJINFO_TAG "objectinfo"
#define CODEGEN_TAG "codegen"
#define TEMPLATE_TAG "template"
#define NAME_TAG "name"
#define PROPERTY_TAG "property"
#define OBJECT_TAG "object"
#define CLASS_TAG "class"
#define PACKAGE_TAG "package"
#define PKGDESC_TAG "desc"
#define PRGLANG_TAG "language"
#define HIDDEN_TAG "hidden"     //Juan


ObjectPackage::ObjectPackage(string name, string desc)
{
  m_name = name;
  m_desc = desc;
}

PObjectInfo ObjectPackage::GetObjectInfo(unsigned int idx)
{
  assert (idx < m_objs.size());
  return m_objs[idx];
}


///////////////////////////////////////////////////////////////////////////////

ObjectDatabase::ObjectDatabase()
{
  InitObjectTypes();
//  InitWidgetTypes();
  InitPropertyTypes();
}

ObjectDatabase::~ObjectDatabase()
{
  // destruir todos los objetos
}

PObjectInfo ObjectDatabase::GetObjectInfo(string class_name)
{
  PObjectInfo info;
  ObjectInfoMap::iterator it = m_objs.find(class_name);
  
  if (it != m_objs.end())
    info = it->second;
  
  return info;
}

PObjectPackage ObjectDatabase::GetPackage(unsigned int idx)
{
  assert (idx < m_pkgs.size());
  
  return m_pkgs[idx];
}


/**
 * @todo La herencia de propiedades ha de ser de forma recursiva.
 */
PObjectBase ObjectDatabase::CreateObject(string class_name, PObjectBase parent)
{
  PObjectBase object;
  bool valid_child = false;
  PObjectInfo obj_info = GetObjectInfo(class_name);

  
  // veamos si podemos crear el objeto
  if (parent)
  {
    if (parent->GetObjectType() == T_SIZER && 
      (obj_info->GetObjectType() == T_WIDGET ||
       obj_info->GetObjectType() == T_SIZER  ||
       obj_info->GetObjectType() == T_SPACER))
      valid_child = true;
    else
      valid_child = parent->ChildTypeOk(obj_info->GetObjectType());
  }  
  else
    valid_child = (obj_info->GetObjectType() == T_PROJECT ||
                  obj_info->GetObjectType() == T_SIZERITEM );

  if (!valid_child)
    return PObjectBase();   

       
  if (obj_info)
  { 
    // Instanciamos el objeto concreto
    
    if (obj_info->GetObjectType() == T_WIDGET)
      object = PObjectBase(new WidgetObject(class_name));
    else if (obj_info->GetObjectType() == T_SIZER)
      object = PObjectBase(new SizerObject(class_name));
    else if (obj_info->GetObjectType() == T_FORM)
      object = PObjectBase(new FormObject(class_name));
    else if (obj_info->GetObjectType() == T_PROJECT)
      object = PObjectBase(new ProjectObject(class_name));
    else if (obj_info->GetObjectType() == T_COMPONENT)
      object = PObjectBase(new ComponentObject(class_name));
    else if (obj_info->GetObjectType() == T_SIZERITEM)
    {
      // un sizeritem no tiene nada de especial
      object = PObjectBase(new ObjectBase(class_name));
      object->SetObjectType(obj_info->GetObjectType()); 
    }
    else
      return PObjectBase();
  }  
  else
    return PObjectBase();


  // lo insertamos en el arbol
  if (parent)
  {    
    // si el objeto padre es un sizer hay que crear un objeto sizeritem
    if (parent->GetObjectType() == T_SIZER && object->GetObjectType() != T_SIZERITEM)
    {
      PObjectBase sizeritem(CreateObject("sizeritem"));
      sizeritem->AddChild(object);
      object->SetParent(sizeritem);

      parent->AddChild(sizeritem);
      sizeritem->SetParent(parent);
    }  
    else
    {
      parent->AddChild(object);
      object->SetParent(parent);
    }  
      
    
  }

  // le a�adimos todas sus propiedades del objeto, incluyendo
  // las propiedades heredadas.
  
  object->SetObjectInfo(obj_info);
  
  PPropertyInfo prop_info;
  PObjectInfo class_info = obj_info;

  unsigned int base = 0;  
  while (class_info)
  {  
    unsigned int i;
    for (i = 0; i < class_info->GetPropertyCount(); i++)
    {
      prop_info = class_info->GetPropertyInfo(i);
    
      PProperty property(new Property(prop_info, object));
//      property->SetValue(TVariant(prop_info->GetType(),prop_info->GetDefaultValue()));
      property->SetValue(prop_info->GetDefaultValue());
      
      // Las propiedades est�n implementadas con una estructura "map",
      // ello implica que no habr� propiedades duplicadas.
      // En otro caso habr� que asegurarse de que dicha propiedad
      // no existe.
      // Otra cosa importante, es que el orden en que se insertan
      // las propiedades, de abajo-arriba, esto permite que se pueda redefir
      // alguna propiedad.
      object->AddProperty (prop_info->GetName(), property);
    }
    
    class_info = ( base < obj_info->GetBaseClassCount() ?
                   obj_info->GetBaseClass(base++) : PObjectInfo());
  }  

  // si el objeto tiene la propiedad name (reservada para el nombre del
  // objeto) le a�adimos el contador para no repetir nombres.
  
  obj_info->IncrementInstanceCount();
  
  unsigned int ins = obj_info->GetInstanceCount();
  PProperty pname = object->GetProperty(NAME_TAG);
  if (pname)
  {
//    pname->SetValue(TVariant(PT_TEXT,pname->GetValue().AsStdString() + StringUtils::IntToStr(ins))); 
    pname->SetValue(pname->GetValue() + StringUtils::IntToStr(ins)); 
  }  
  
  return object;
}

void ObjectDatabase::ResetObjectCounters()
{
  ObjectInfoMap::iterator it;
  for (it = m_objs.begin() ; it != m_objs.end() ; it++)
  {
    it->second->ResetInstanceCount();
  }
}

///////////////////////////////////////////////////////////////////////

PObjectBase  ObjectDatabase::CreateObject(TiXmlElement *xml_obj, PObjectBase parent)
{
  if (!xml_obj->Attribute(CLASS_TAG))
    return PObjectBase();
    
  string class_name = xml_obj->Attribute(CLASS_TAG);
  PObjectBase object = CreateObject(class_name,parent);
  
  if (object)
  {
    // modificamos cada propiedad 
    TiXmlElement *xml_prop = xml_obj->FirstChildElement(PROPERTY_TAG);
    while (xml_prop)
    {
      string prop_value;
      string prop_name = xml_prop->Attribute(NAME_TAG);

      TiXmlNode *xml_value = xml_prop->FirstChild();
      if (xml_value && xml_value->ToText())
      {
        prop_value = xml_value->ToText()->Value();
        PProperty prop = object->GetProperty(prop_name);
        if (prop)
        {
          prop->SetValue(prop_value);
//          prop->SetValue(TVariant(prop->GetType(),prop_value));
        }
      }
      xml_prop = xml_prop->NextSiblingElement(PROPERTY_TAG);
    }
    
    // creamos los hijos
    TiXmlElement *child = xml_obj->FirstChildElement(OBJECT_TAG);
    while (child)
    {
      CreateObject(child,object);
      child = child->NextSiblingElement(OBJECT_TAG);
    }
  }
  return object;
}

//////////////////////////////
/*PVisualObject ObjectDatabase::CreateVisualObject(PObjectBase obj, wxObject *parent)
{
  PVisualObject result;
  ComponentMap::iterator it = m_components.find(obj->GetClassName());
  if (it != m_compoenent.end())
  {
    // creamos el objeto y la instancia
    result = PVisualObject(new 
  }
}*/
//////////////////////////////

bool ObjectDatabase::LoadFile(string file)
{
  bool result = false;
  TiXmlDocument doc(m_xmlPath + '/' + file);
  result = doc.LoadFile();
  
  if (result)
  {
    // Cargamos el paquete por defecto
    LoadPackage("default.xml");
    
    TiXmlElement* root = doc.FirstChildElement("packages");
    if (root)
    {
      TiXmlElement* elem = root->FirstChildElement(PACKAGE_TAG);
      
      // En primer lugar se carga uno por uno todos los objetos
      // de los archivos xml en una primera pasada.
      while (elem)
      {
        string file = elem->Attribute("file");
        PObjectPackage package = LoadPackage(file);
        if (package)
          m_pkgs.push_back(package);
            
        elem = elem->NextSiblingElement(PACKAGE_TAG); 
      }
      
      // En una segunda pasada, a�adimos a cada objeto
      // sus correspondientes "objetos base" para que puedan heredar
      // sus propiedades
      elem = root->FirstChildElement(PACKAGE_TAG);
      while (elem)
      {
        string file = elem->Attribute("file");
        SetupPackage(file);            
        elem = elem->NextSiblingElement(PACKAGE_TAG);         
      }  
    }
  }
//  else
//  {
//    cout << "Loading error on "<< file <<" file." << endl;
//    system("pause");
//  }

  return result;
}

void ObjectDatabase::SetupPackage(string file)
{
//  DEBUG_PRINT("SETTING-UP " + file + "...");
  
  TiXmlDocument doc(m_xmlPath + '/' + file);
  if (doc.LoadFile())
  {
//    DEBUG_PRINT("OK\n");  
    TiXmlElement* root = doc.FirstChildElement(PACKAGE_TAG);
    if (root)
    {
      // comprobamos si hay librar�a que importar
      if (root->Attribute("lib"))
        ImportComponentLibrary(root->Attribute("lib"));
      
      TiXmlElement* elem_obj = root->FirstChildElement(OBJINFO_TAG);
      while (elem_obj)
      {
        string class_name  = elem_obj->Attribute(CLASS_TAG);
        PObjectInfo class_info = GetObjectInfo(class_name);

        TiXmlElement* elem_base = elem_obj->FirstChildElement("inherits");
        while (elem_base)
        {
          string base_name = elem_base->Attribute(CLASS_TAG);
          // A�adimos la referencia a su clase base
          PObjectInfo base_info  = GetObjectInfo(base_name);
          if (class_info && base_info)
          {
            class_info->AddBaseClass(base_info);
//            DEBUG_PRINT("  " + class_name + " inherits from " + base_name + "\n");
          }  
          elem_base = elem_base->NextSiblingElement("inherits");
        }  
        
        // vamos a a�adir la interfaz "C++", predefinida para los componentes
        // y widgets
        if (class_info->GetObjectType() == T_COMPONENT ||
            class_info->GetObjectType() == T_WIDGET )
        {
          PObjectInfo cpp_interface = GetObjectInfo("C++");
          if (cpp_interface)
            class_info->AddBaseClass(cpp_interface);
        }  
        
        elem_obj = elem_obj->NextSiblingElement(OBJINFO_TAG);
      }  
    }      
  }  
}  

PObjectPackage ObjectDatabase::LoadPackage(string file)
{
  PObjectPackage package;
  
//  DEBUG_PRINT("LOADING " + file + "...");
  
  TiXmlDocument doc(m_xmlPath + '/' + file);
  if (doc.LoadFile())
  {
//    DEBUG_PRINT("OK\n");  
    TiXmlElement* root = doc.FirstChildElement(PACKAGE_TAG);
    if (root)
    {
      string pkg_name = root->Attribute(NAME_TAG);
      string pkg_desc = root->Attribute(PKGDESC_TAG);
      
      package = PObjectPackage (new ObjectPackage(pkg_name, pkg_desc));

      
      TiXmlElement* elem_obj = root->FirstChildElement(OBJINFO_TAG);
      
      while (elem_obj)
      {
        string class_name  = elem_obj->Attribute(CLASS_TAG);
        string type        = elem_obj->Attribute("type");
        string widget;
        if (elem_obj->Attribute("widget"))
          widget = elem_obj->Attribute("widget");
        string icon;
        if (elem_obj->Attribute("icon"))
          icon = elem_obj->Attribute("icon");


//        DEBUG_PRINT("  OBJ: '" + class_name + "' TYPE: '" + type + "'\n"); 
        PObjectInfo obj_info(new ObjectInfo(class_name,
                                            ParseObjectType(type)));
//                                            ParseWidgetType(widget)));
        if (icon != "")
          obj_info->SetIconFile(m_iconPath + '/' +icon);
        // parseamos las propiedades
        TiXmlElement* elem_prop = elem_obj->FirstChildElement(PROPERTY_TAG);
        while (elem_prop)
        {
          string pname = elem_prop->Attribute(NAME_TAG);
          bool hidden = false;    //Juan
          if (elem_prop->Attribute(HIDDEN_TAG)){
            int val;
            elem_prop->Attribute(HIDDEN_TAG, &val);
            hidden = val != 0;
          }
          PropertyType ptype = ParsePropertyType(elem_prop->Attribute("type"));
          string def_value;
          POptionList opt_list;
          
//          DEBUG_PRINT("    PROPERTY: '" + pname + "'\n");
              
          // si la propiedad es de tipo "bitlist" debemos parsear cada
          // una de las opciones
          if (ptype == PT_BITLIST || ptype == PT_OPTION)
          {
            opt_list = POptionList(new OptionList());
            TiXmlElement *elem_opt = elem_prop->FirstChildElement("option");
            while(elem_opt)
            {
              string macro_name = elem_opt->Attribute(NAME_TAG);
              opt_list->AddOption(macro_name);
              elem_opt = elem_opt->NextSiblingElement("option");
              
              // vamos a comprobar si la macro est� registrada en la aplicaci�n
              // de los contrario mostraremos un mensaje de advertencia.
//              {
//                int macro;
//                PMacroDictionary dic = MacroDictionary::GetInstance();
//                if (!dic->SearchMacro(macro_name,&macro))
//                  Debug::Print("Macro '%s' not defined!",macro_name.c_str());
//              }
            }
          }
          
          TiXmlText * elem_text = elem_prop->LastChild()->ToText();
          if (elem_text)
            def_value = elem_text->Value();

          // creamos la instancia del descriptor de propiedad
          // Juan
          PPropertyInfo prop_info(new PropertyInfo(pname,ptype,def_value,hidden,opt_list));
            
          // a�adimos el descriptor de propiedad
          obj_info->AddPropertyInfo(prop_info); 
          
          
          elem_prop = elem_prop->NextSiblingElement(PROPERTY_TAG);
        }
        // leemos la descripcion de generacion de c�digo
        TiXmlElement* elem_codegen = elem_obj->FirstChildElement(CODEGEN_TAG);
        while (elem_codegen)
        {
          string language = elem_codegen->Attribute(PRGLANG_TAG);
          PCodeInfo code_info(new CodeInfo());
          
          // leemos cada plantilla de c�digo
          TiXmlElement* elem_template = elem_codegen->FirstChildElement(TEMPLATE_TAG);
          while (elem_template)
          {
            string template_name = elem_template->Attribute(NAME_TAG);
            string template_code;
            
            TiXmlText * elem_code = elem_template->LastChild()->ToText();
            if (elem_code)
              template_code = elem_code->Value();          
              
            code_info->AddTemplate(template_name,template_code);
            elem_template = elem_template->NextSiblingElement(TEMPLATE_TAG);
          }
          
          obj_info->AddCodeInfo(language,code_info);
          elem_codegen = elem_codegen->NextSiblingElement(CODEGEN_TAG);
        };

        
        // a�adimos el descriptor de objeto al registro
        m_objs.insert(ObjectInfoMap::value_type(class_name,obj_info));
        
        // y al grupo
        if (obj_info->GetObjectType() == T_FORM ||
            obj_info->GetObjectType() == T_WIDGET ||
            obj_info->GetObjectType() == T_SIZER ||
            obj_info->GetObjectType() == T_COMPONENT)
          package->Add(obj_info);
        
        elem_obj = elem_obj->NextSiblingElement(OBJINFO_TAG);
      }
    }
  }
//  else
//  {
//    cout << "Loading error on "<< file <<" file." << endl;
//    system("pause");
//  }
  
  
  return package;
}

void ObjectDatabase::ImportComponentLibrary(string libfile)
{
  typedef ComponentLibraryBase* (*PFGetComponentLibrary)();
  wxString path = _WXSTR(m_xmlPath) + wxT('/') + _WXSTR(libfile);
  
  // intentamos cargar la DLL
  wxDynamicLibrary *library = new wxDynamicLibrary(path);

  if (library->IsLoaded())
  {
    m_libs.push_back(library);
    PFGetComponentLibrary GetComponentLibrary = 
      (PFGetComponentLibrary)library->GetSymbol(_("GetComponentLibrary"));

    if (GetComponentLibrary)
    {
      Debug::Print("[Database::ImportComponentLibrary] Importing %s library",
        libfile.c_str());
        
      ComponentLibraryBase *comp_lib = GetComponentLibrary();
    
      // importamos todos los componentes
      for (unsigned int i=0; i<comp_lib->GetComponentCount(); i++)
      {
        wxString class_name = comp_lib->GetComponentName(i);
        ComponentBase *comp = comp_lib->GetComponent(i);
        
        // buscamos la clase
        PObjectInfo class_info = GetObjectInfo(_STDSTR(class_name));
        if (class_info)
          class_info->SetComponent(comp);
        else
          Debug::Print("[Database::ImportComponentLibrary] ObjectInfo %s not found!",
                        _STDSTR(class_name).c_str());
      }
      
      // A�adimos al diccionario de macros todas las macros definidas en la
      // biblioteca
      for (unsigned int i=0; i<comp_lib->GetMacroCount(); i++)
      {
        PMacroDictionary dic = MacroDictionary::GetInstance();
        wxString name = comp_lib->GetMacroName(i);
        int value = comp_lib->GetMacroValue(i);
        dic->AddMacro(_STDSTR(name),value);
      }
    }
    else
      Debug::Print("[Database::ImportComponentLibrary] %s is not a valid component library",
        libfile.c_str());
  
  }
  else
    Debug::Print("[Database::ImportComponentLibrary] Error loading library %s.",
                 libfile.c_str());

}

PropertyType ObjectDatabase::ParsePropertyType (string str)
{
  PropertyType result;
  PTMap::iterator it = m_propTypes.find(str);
  if (it != m_propTypes.end())
    result = it->second;
  else
    result = PT_ERROR;
  
  return result;

}

ObjectType  ObjectDatabase::ParseObjectType   (string str)
{
  ObjectType result;
  
  OTMap::iterator it = m_objTypes.find(str);
  if (it != m_objTypes.end())
    result = it->second;
  else
    result = T_ERROR;
  
  return result;

}

//WidgetType  ObjectDatabase::ParseWidgetType   (string str)
//{
//  WidgetType result;
//  
//  WTMap::iterator it = m_widgetTypes.find(str);
//  if (it != m_widgetTypes.end())
//    result = it->second;
//  else
//    result = W_GENERIC;
//    
//  return result;
//}


#define OT(x,y) m_objTypes.insert(OTMap::value_type(x,y))
void ObjectDatabase::InitObjectTypes()
{
 OT("widget",T_WIDGET);
 OT("project",T_PROJECT);
 OT("sizer",T_SIZER);
 OT("sizeritem",T_SIZERITEM);
 OT("component",T_COMPONENT);
 OT("interface",T_INTERFACE);
 OT("form",T_FORM);
 OT("spacer",T_SPACER);
}

//#define WT(x,y) m_widgetTypes.insert(WTMap::value_type(x,y))
//void ObjectDatabase::InitWidgetTypes()
//{
//  WT("wxPanel",W_PANEL);
//  WT("wxButton",W_BUTTON);
//  WT("wxComboBox",W_COMBO_BOX);
//  WT("wxTextCtrl",W_TEXT_CTRL);
//  WT("wxStaticText",W_STATIC_TEXT);
//  WT("wxBoxSizer",W_BOX_SIZER);
//  WT("wxFlexGridSizer",W_FLEX_GRID_SIZER);
//  WT("wxGridSizer",W_GRID_SIZER);
//  WT("spacer",W_SPACER);
//  WT("sizeritem",W_SIZERITEM);
//  WT("wxCheckBox",W_CHECK_BOX);
//  WT("wxGrid",W_GRID);
//  WT("wxStaticBitmap",W_STATIC_BITMAP);
//}

#define PT(x,y) m_propTypes.insert(PTMap::value_type(x,y))
void ObjectDatabase::InitPropertyTypes()
{
  PT("bool",PT_BOOL);
  PT("text",PT_TEXT);
  PT("bitlist",PT_BITLIST);
  PT("intlist",PT_INTLIST);
  PT("option",PT_OPTION);
  PT("macro",PT_MACRO);
  PT("path",PT_PATH);
  PT("wxString",PT_WXSTRING);
  PT("wxPoint",PT_WXPOINT);
  PT("wxSize",PT_WXSIZE);
  PT("wxFont",PT_WXFONT);
  PT("wxColour",PT_WXCOLOUR);
  PT("bitmap",PT_BITMAP);
}
