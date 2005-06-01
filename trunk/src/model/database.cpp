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
// Añadir atributo hidden
// Juan Antonio Ortega (jortegalalmolda@gmail.com)

#include "database.h"
//#include "objects.h"
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
  //InitObjectTypes();
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
   
  if (!obj_info)
  {
    assert(false);
    return PObjectBase();
  }

  if (parent)
  {
    valid_child = parent->ChildTypeOk(obj_info->GetObjectTypeName());
    
    if (!valid_child && parent->GetParent() && 
         parent->GetObjectTypeName() != "sizer" &&
         parent->GetObjectTypeName() != "notebook")
    {
      parent = parent->FindNearAncestor("sizer");
      if (!parent) return PObjectBase();
      valid_child = parent->ChildTypeOk(obj_info->GetObjectTypeName());
    }

    if (!valid_child && parent->GetObjectTypeName() == "sizer")
    {
      PObjectBase sizeritem;
    
      // Esto no debería comprobarse aquí ya que esto pertenece a la lógica
      // de la aplicación, aunque de momento lo vamos a permitir.
      // En el caso de que el objeto padre sea un T_SIZER vamos a comprobar
      // si metiendolo en un T_SIZERITEM es un objeto válido.
      
      // *** NOTA: error de diseño ***
      // la función ChildTypeOk debe ser de ObjectInfo en lugar de ObjectBase
      // como "apaño" se va a crear un objeto temporal para usar la función
      sizeritem = PObjectBase(new ObjectBase("sizeritem"));
      sizeritem->SetObjectTypeName("sizeritem");
      valid_child = sizeritem->ChildTypeOk(obj_info->GetObjectTypeName());
      
      if (valid_child)
      {
        // Pues hay que meterlo en un sizeritem, vamos a preparar el
        // nuevo padre
        sizeritem = CreateObject("sizeritem",parent);
        assert(sizeritem);
        
        parent = sizeritem;
        
        // Vamos a darle unos valores a las propiedades de layout
        // predeterminados según el tipo de objeto
        string obj_type = obj_info->GetObjectTypeName();
        if (obj_type == "container" || obj_type == "notebook")
        {
            sizeritem->GetProperty("option")->SetValue(string("1"));
            sizeritem->GetProperty("flag")->SetValue(string("wxEXPAND | wxALL"));
        }
        else if (obj_type == "widget" || obj_type == "statusbar")
        {
            sizeritem->GetProperty("option")->SetValue(string("0"));
            sizeritem->GetProperty("flag")->SetValue(string("wxALL"));
        }
        else if (obj_type == "sizer")
        {  
            sizeritem->GetProperty("option")->SetValue(string("1"));
            sizeritem->GetProperty("flag")->SetValue(string("wxEXPAND"));
        }
      }
    }
    else if (!valid_child && parent->GetObjectTypeName() == "notebook")
    {
      PObjectBase nbpage;
      Debug::Print("new notebook page");
      nbpage = PObjectBase(new ObjectBase("notebookpage"));
      nbpage->SetObjectTypeName("notebookpage");
      valid_child = nbpage->ChildTypeOk(obj_info->GetObjectTypeName());
      if (valid_child)
      {
        // Pues hay que meterlo en un sizeritem, vamos a preparar el
        // nuevo padre
        nbpage = CreateObject("notebookpage",parent);
        assert(nbpage);
        
        parent = nbpage;
      }
    }
  }
  else
  {
    // si no tiene padre sólo puede ser un objeto T_PROJECT
    valid_child = obj_info->GetObjectTypeName() == "project";
  }

  if (!valid_child)
    return PObjectBase();   


  // Llagados aquí el objeto se crea seguro...
  object = PObjectBase(new ObjectBase(class_name));
  object->SetObjectTypeName(obj_info->GetObjectTypeName()); // *FIXME*


  // lo insertamos en el arbol si procede...
  if (parent)
  {    
    parent->AddChild(object);
    object->SetParent(parent);
  }
 
  // **** NOTA: esto debe ir en el constructor de ObjectBase ****      
  // le añadimos todas sus propiedades del objeto, incluyendo
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
      property->SetValue(prop_info->GetDefaultValue());
      
      // Las propiedades están implementadas con una estructura "map",
      // ello implica que no habrá propiedades duplicadas.
      // En otro caso habrá que asegurarse de que dicha propiedad
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
  // objeto) le añadimos el contador para no repetir nombres.
  
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

bool IncludeInPalette(string type)
{
  return true;
}

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
      
      // En una segunda pasada, añadimos a cada objeto
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
      // comprobamos si hay libraría que importar
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
          // Añadimos la referencia a su clase base
          PObjectInfo base_info  = GetObjectInfo(base_name);
          if (class_info && base_info)
          {
            class_info->AddBaseClass(base_info);
//            DEBUG_PRINT("  " + class_name + " inherits from " + base_name + "\n");
          }  
          elem_base = elem_base->NextSiblingElement("inherits");
        }  
        
        // vamos a añadir la interfaz "C++", predefinida para los componentes
        // y widgets
        if (HasCppProperties(class_info->GetObjectTypeName()))
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

bool ObjectDatabase::HasCppProperties(string type)
{
   return (type == "component" || type == "widget" ||
           type == "container" || type == "notebook" || type == "menubar" ||
           type == "statusbar");
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

        PObjectInfo obj_info(new ObjectInfo(class_name, GetObjectType(type)));
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
              
              // vamos a comprobar si la macro está registrada en la aplicación
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
            
          // añadimos el descriptor de propiedad
          obj_info->AddPropertyInfo(prop_info); 
          
          
          elem_prop = elem_prop->NextSiblingElement(PROPERTY_TAG);
        }
        // leemos la descripcion de generacion de código
        TiXmlElement* elem_codegen = elem_obj->FirstChildElement(CODEGEN_TAG);
        while (elem_codegen)
        {
          string language = elem_codegen->Attribute(PRGLANG_TAG);
          PCodeInfo code_info(new CodeInfo());
          
          // leemos cada plantilla de código
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

        
        // añadimos el descriptor de objeto al registro
        m_objs.insert(ObjectInfoMap::value_type(class_name,obj_info));
        
        // y al grupo
        if (ShowInPalette(obj_info->GetObjectTypeName()))
          package->Add(obj_info);
        
        elem_obj = elem_obj->NextSiblingElement(OBJINFO_TAG);
      }
    }
  }

  return package;
}

bool ObjectDatabase::ShowInPalette(string type)
{
  return ( type == "form" || type == "widget" || type == "sizer" ||
           type == "component" || type == "container" || type == "spacer" ||
           type == "notebook" || type == "menubar" || type == "menu" ||
           type == "menuitem" || type == "statusbar");
}


void ObjectDatabase::ImportComponentLibrary(string libfile)
{
  typedef IComponentLibrary* (*PFGetComponentLibrary)();
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
        
      IComponentLibrary *comp_lib = GetComponentLibrary();
    
      // importamos todos los componentes
      for (unsigned int i=0; i<comp_lib->GetComponentCount(); i++)
      {
        wxString class_name = comp_lib->GetComponentName(i);
        IComponent *comp = comp_lib->GetComponent(i);
        
        // buscamos la clase
        PObjectInfo class_info = GetObjectInfo(_STDSTR(class_name));
        if (class_info)
          class_info->SetComponent(comp);
        else
          Debug::Print("[Database::ImportComponentLibrary] ObjectInfo %s not found!",
                        _STDSTR(class_name).c_str());
      }
      
      // Añadimos al diccionario de macros todas las macros definidas en la
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
  {
    result = PT_ERROR;
    assert(false);
  }
  
  return result;

}

string  ObjectDatabase::ParseObjectType   (string str)
{
  return str;
}


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

bool ObjectDatabase::LoadObjectTypes()
{
  bool result = false;
  TiXmlDocument doc(m_xmlPath + '/' + "objtypes.xml");
  result = doc.LoadFile();
  
  if (result)
  {
    // se realizará en dos pasos, primero importamos cada uno de los ObjectTypes
    // definidos y a continuación se añadirán los posibles ObjectTypes hijos
    // de cada uno.
    TiXmlElement* root = doc.FirstChildElement("definitions");
    if (root)
    {
      TiXmlElement* elem = root->FirstChildElement("objtype");
      while (elem)
      {
        bool hidden = false, item = false;
        string name = elem->Attribute("name");
        if (elem->Attribute("hidden") && string(elem->Attribute("hidden"))=="1")
          hidden = true;
        if (elem->Attribute("item") && string(elem->Attribute("item"))=="1")
          item = true;
          
        int id = m_types.size();  
        PObjectType objType(new ObjectType(name,id,hidden,item));
        m_types.insert(ObjectTypeMap::value_type(name,objType));
        
        elem = elem->NextSiblingElement("objtype");
      }
        
      // ahora continuamos registrando añadiendo las referencias de cada
      // posible hijo
      elem = root->FirstChildElement("objtype");
      while (elem)
      {
        string name = elem->Attribute("name");
        
        // obtenemos el objType
        PObjectType objType = GetObjectType(name);
        wxLogMessage(wxString::Format(_("ObjectType %s can be parent of..."),name.c_str()));
        TiXmlElement *child = elem->FirstChildElement("childtype");
        while (child)
        {
          int nmax = -1; // sin límite
          string childname = child->Attribute("name");
          wxLogMessage(wxString::Format(_("%s"),childname.c_str()));
          
          
          if (child->Attribute("nmax"))
            //nmax = StringUtils::StrToInt(child->Attribute("nmax"));
            nmax = 1;
          
          PObjectType childType = GetObjectType(childname);
          assert(childType);
          
          objType->AddChildType(childType, nmax);
          
          child = child->NextSiblingElement("childtype");
        }
        elem = elem->NextSiblingElement("objtype");
      }
    }
  }
  else
    wxLogError("Error loading object types");
  return true;
}

PObjectType ObjectDatabase::GetObjectType(string name)
{
  PObjectType type;
  ObjectTypeMap::iterator it = m_types.find(name);
  if (it != m_types.end())
    type = it->second;
    
  return type;
}

