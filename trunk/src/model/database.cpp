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

#include "database.h"
//#include "objects.h"
#include "utils/stringutils.h"
#include "utils/typeconv.h"
#include "utils/debug.h"
#include <wx/filename.h>

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
/*
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
  
  object = NewObject(obj_info);

  // lo insertamos en el arbol si procede...
  if (parent)
  {    
    parent->AddChild(object);
    object->SetParent(parent);
  }
 
  return object;
}*/

PObjectBase ObjectDatabase::NewObject(PObjectInfo obj_info)
{
  PObjectBase object;
  
  // Llagados aquí el objeto se crea seguro...
  object = PObjectBase(new ObjectBase(obj_info->GetClassName()));
  object->SetObjectTypeName(obj_info->GetObjectTypeName()); // *FIXME*

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
    pname->SetValue(pname->GetValue() + StringUtils::IntToStr(ins)); 
  
  return object;
}


int ObjectDatabase::CountChildrenWithSameType(PObjectBase parent,PObjectType type)
{
  unsigned int count = 0;
  unsigned int numChildren = parent->GetChildCount();
  for (unsigned int i=0; i < numChildren ; i++)
  {
    if (type == parent->GetChild(i)->GetObjectInfo()->GetObjectType())
      count++;
  }
  
  return count;
}

/**
 * Crea una instancia de classname por debajo de parent.
 * La función realiza la comprobación de tipos para crear el objeto:
 * - Comprueba si el tipo es un tipo-hijo válido de "parent", en cuyo caso
 *   se comprobará también que el número de hijos del mismo tipo no sobrepase
     el máximo definido. El objeto no se crea si supera el máximo permitido.
 * - Si el tipo-hijo no se encuentra entre los definidos para el tipo de 
 *   "parent" se intentará crearlo como hijo de alguno de los tipos hijos con el
 *   flag item a "1". Para ello va recorriendo todos los tipos con flag item,
 *   si no puede crear el objeto, bien por que el tipo no es válido o porque
 *   sobrepasa el máximo permitido si intenta con el siguiente hasta que no queden
 *   más.
 *
 * Nota: quizá sea conveniente que el método cree el objeto sin enlazarlo
 *       en el árbol, para facilitar el undo-redo.
 */
PObjectBase ObjectDatabase::CreateObject(string classname, PObjectBase parent)
{
  PObjectBase object;
  PObjectInfo objInfo = GetObjectInfo(classname);
  
  if (!objInfo)
  {
    wxLogError(_("Object not found (") + _WXSTR(classname) + _(")"));
    return PObjectBase();
  }
  
  PObjectType objType = objInfo->GetObjectType();

  if (parent)
  {
    // Comprobamos si el tipo es válido
    PObjectType parentType = parent->GetObjectInfo()->GetObjectType();
    int max = parentType->FindChildType(objType);
    
    // FIXME! Esto es un parche para evitar crear los tipos menubar,statusbar y
    // toolbar en un form que no sea wxFrame.
    // Hay que modificar el conjunto de tipos para permitir tener varios tipos
    // de forms (como childType de project), pero hay mucho código no válido
    // para forms que no sean de tipo "form". Dicho de otra manera, hay 
    // código que dependen del nombre del tipo, cosa que hay que evitar.
    if (parentType->GetName() == "form" && parent->GetClassName() != "Frame" && 
        (objType->GetName() == "statusbar" ||
         objType->GetName() == "menubar" ||
         objType->GetName() == "toolbar"))
      return PObjectBase(); // tipo no válido
    
    if (max != 0) // tipo válido
    {
      bool create = true;
      
      // comprobamos el número de instancias
      if (max > 0 && CountChildrenWithSameType(parent, objType) >= max) 
        create = false;
     
      if (create)
        object = NewObject(objInfo);
    }
    else // max == 0
    {
      // el tipo no es válido, vamos a comprobar si podemos insertarlo
      // como hijo de un "item"
      bool created = false;
      for (unsigned int i=0; !created && i < parentType->GetChildTypeCount(); i++)
      {
        PObjectType childType = parentType->GetChildType(i);
        int max = childType->FindChildType(objType);
        
        if (childType->IsItem() && max != 0)
        {
          max = parentType->FindChildType(childType);
          
          // si el tipo es un item y además el tipo del objeto a crear
          // puede ser hijo del tipo del item vamos a intentar crear la
          // instancia del item para crear el objeto como hijo de este
          if (max < 0 || CountChildrenWithSameType(parent, childType) < max)
          {
            // No hay problemas para crear el item debajo de parent
            PObjectBase item = NewObject(GetObjectInfo(childType->GetName()));
            
            //PObjectBase obj = CreateObject(classname,item);
            PObjectBase obj = NewObject(objInfo);
            
            // la siguiente condición debe cumplirse siempre
            // ya que un item debe siempre contener a otro objeto
            if (obj)
            {            
              // enlazamos item y obj
              item->AddChild(obj);
              obj->SetParent(item);
              
              // sizeritem es un tipo de objeto reservado, para que el uso sea
              // más práctico se asignan unos valores por defecto en función 
              // del tipo de objeto creado
              if (item->GetObjectTypeName() == "sizeritem")
                SetDefaultLayoutProperties(item);
           
              object = item;
              created = true;
            }
            else
              wxLogError(_("Review your definitions file (objtypes.xml)"));
          }
        }
      }
    }
    ///////////////////////////////////////////////////////////////////////
    // Nota: provisionalmente vamos a enlazar el objeto al padre pero
    //       esto debería hacerse fuera para poder implementar el Undo-Redo
    ///////////////////////////////////////////////////////////////////////
    //if (object)
    //{
    //  parent->AddChild(object);
    //  object->SetParent(parent);
    //}
  }
  else // parent == NULL;
  {
    object = NewObject(objInfo);
  }
  
  return object;
}

PObjectBase ObjectDatabase::CopyObject(PObjectBase obj)
{
  assert(obj);
  
  PObjectInfo objInfo = obj->GetObjectInfo();
  
  PObjectBase copyObj = NewObject(objInfo); // creamos la copia
  assert(copyObj);
  
  // copiamos las propiedades
  unsigned int i;
  unsigned int count = obj->GetPropertyCount();
  for (i = 0; i < count; i++)
  {
    PProperty objProp = obj->GetProperty(i);
    assert(objProp);
    
    PProperty copyProp = copyObj->GetProperty(objProp->GetName());
    assert(copyProp);
    
    string propValue = objProp->GetValue();
    copyProp->SetValue(propValue);
  }
  
  // creamos recursivamente los hijos
  count = obj->GetChildCount();
  for (i = 0; i<count; i++)
  {
    PObjectBase childCopy = CopyObject(obj->GetChild(i));
    copyObj->AddChild(childCopy);
    childCopy->SetParent(copyObj);
  }
  
  return copyObj;
}

void ObjectDatabase::SetDefaultLayoutProperties(PObjectBase sizeritem)
{
  assert(sizeritem->GetObjectTypeName() == "sizeritem");
  
  string obj_type = sizeritem->GetChild(0)->GetObjectTypeName();
  
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
  else if (obj_type == "sizer" || obj_type == "splitter")
  {  
    sizeritem->GetProperty("option")->SetValue(string("1"));
    sizeritem->GetProperty("flag")->SetValue(string("wxEXPAND"));
  }
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
    
    if (parent)
    {
      // enlazamos
      parent->AddChild(object);
      object->SetParent(parent);
    }
    
    // creamos los hijos
    TiXmlElement *child = xml_obj->FirstChildElement(OBJECT_TAG);
    while (child)
    {
      PObjectBase childObj = CreateObject(child,object);      
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
    LoadCodeGen("default.cppcode");
    
    TiXmlElement* root = doc.FirstChildElement("packages");
    if (root)
    {
      TiXmlElement* elem = root->FirstChildElement(PACKAGE_TAG);
      
      // En primer lugar se carga uno por uno todos los objetos
      // de los archivos xml en una primera pasada.
      while (elem)
      {
        string file = elem->Attribute("file");
        wxFileName fn(_WXSTR(file));
        fn.SetExt(_T("cppcode"));
        
        PObjectPackage package = LoadPackage(file);
        if (package)
        {
          m_pkgs.push_back(package);
          LoadCodeGen(_STDSTR(fn.GetFullName()));
        }
            
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
    
    // imprimimos las macros declaradas pero no importadas.
    #ifdef __WXFB_DEBUG__
    MacroSet::iterator it;
    //Debug::Print("Missing macros of component libraries");
    wxLogMessage(_("Missing macros of component libraries"));
    for (it = m_macroSet.begin(); it != m_macroSet.end(); it++)
    {
      wxLogMessage(_WXSTR(*it));
      //Debug::Print((char*)(*it).c_str());
    }
    #endif
    
    
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
           type == "statusbar" || type == "toolbar" || type == "splitter");
}

void ObjectDatabase::LoadCodeGen(string file)
{
  TiXmlDocument doc(m_xmlPath + '/' + file);
  if (doc.LoadFile())
  {
    // leemos la descripcion de generacion de código
    TiXmlElement* elem_codegen = doc.FirstChildElement("codegen");
    if (elem_codegen)
    {
      string language = elem_codegen->Attribute("language");
      
      // leemos cada plantilla de código
      TiXmlElement* elem_templates = elem_codegen->FirstChildElement("templates");
      while (elem_templates)
      {
        string class_name = elem_templates->Attribute("class");
        TiXmlElement *elem_template = elem_templates->FirstChildElement("template");
        PCodeInfo code_info(new CodeInfo());
        
        while (elem_template)
        {
          string template_name = elem_template->Attribute("name");
          string template_code;
          
          TiXmlText * elem_code = elem_template->LastChild()->ToText();
          if (elem_code)
            template_code = elem_code->Value();          
            
          code_info->AddTemplate(template_name,template_code);
          elem_template = elem_template->NextSiblingElement("template");
        }
        
        PObjectInfo obj_info = GetObjectInfo(class_name);
        if (obj_info)
          obj_info->AddCodeInfo(language, code_info);
          
        elem_templates = elem_templates->NextSiblingElement("templates");
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
              
              m_macroSet.insert(macro_name);
              // vamos a comprobar si la macro está registrada en la aplicación
              // de los contrario mostraremos un mensaje de advertencia.
              /*{
                int macro;
                PMacroDictionary dic = MacroDictionary::GetInstance();
                if (!dic->SearchMacro(macro_name,&macro))
                  wxLogWarning(_("Macro '%s' not defined on component library!"),_WXSTR(macro_name).c_str());
              }*/
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
        /*
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
        */
        
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
           type == "menuitem" || type == "statusbar" || type == "submenu" ||
           type == "toolbar" || type == "tool" || type == "splitter");
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
        m_macroSet.erase(_STDSTR(name));
      }
      
      /*for (unsigned int i = 0; i < comp_lib->GetSynonymousCount(); i++)
      {
        PMacroDictionary dic = MacroDictionary::GetInstance();
        wxString syn = comp_lib->GetMacroSynonymous(i);
        wxString name = comp_lib->GetSynonymousName(i);
        dic->AddSynonymous(_STDSTR(syn), _STDSTR(name));
      }*/
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
  //PT("xpm_bitmap",PT_XPM_BITMAP);
  PT("stringlist",PT_STRINGLIST);
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
        //wxLogMessage(wxString::Format(_("ObjectType %s can be parent of..."),name.c_str()));
        TiXmlElement *child = elem->FirstChildElement("childtype");
        while (child)
        {
          int nmax = -1; // sin límite
          string childname = child->Attribute("name");
          //wxLogMessage(wxString::Format(_("%s"),childname.c_str()));
          
          
          if (child->Attribute("nmax"))
            nmax = TypeConv::StringToInt(_WXSTR(child->Attribute("nmax")));
            //nmax = 1;
          
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
    wxLogError(_("Error loading object types"));
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

