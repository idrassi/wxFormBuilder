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
// Añadir hidden. Juan Antonio Ortega (jortegalalmolda@gmail.com)

#ifndef __OBJ__
#define __OBJ__

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <boost/smart_ptr.hpp>
#include "types.h"
#include "tinyxml.h"

#include "wx/wx.h"
#include "plugins/component.h"

//#include "utils/typeconv.h" // sustituir por variant
using namespace std;
using namespace boost;


///////////////////////////////////////////////////////////////////////////////


ostream& operator << (ostream &s, ObjectType type);

///////////////////////////////////////////////////////////////////////////////


class ObjectBase;
class ObjectInfo;
class Property;
class PropertyInfo;
class OptionList;
class CodeInfo;


typedef shared_ptr<OptionList> POptionList;
typedef shared_ptr<ObjectBase> PObjectBase;
typedef weak_ptr<ObjectBase> WPObjectBase;

typedef shared_ptr<CodeInfo> PCodeInfo;
typedef shared_ptr<ObjectInfo> PObjectInfo;
typedef shared_ptr<Property> PProperty;
typedef shared_ptr<PropertyInfo> PPropertyInfo;

typedef vector< PObjectBase > ObjectVector;
typedef map<string,PProperty> PropertyMap;
typedef map<string, PPropertyInfo> PropertyInfoMap;
typedef vector<PObjectInfo> ObjectInfoVector;
typedef map<string, PObjectInfo> ObjectInfoMap;

///////////////////////////////////////////////////////////////////////////////

class OptionList
{
 private:
   vector<string> m_options;  
 public:
  
  void AddOption(string option)      { m_options.push_back(option); }
  unsigned int GetOptionCount()      { return m_options.size(); }
  string GetOption(unsigned int idx);
};

///////////////////////////////////////////////////////////////////////////////

class PropertyInfo
{
 private: 
  string       m_name;
  PropertyType m_type;
  string       m_def_value;
  POptionList  m_opt_list;
  bool m_hidden; // Juan. Determina si la propiedad aparece o no en XRC
  
 public:

  PropertyInfo(string name, PropertyType type, string def_value, 
               bool hidden = false, POptionList opt_list = POptionList()); //Juan
                     
  ~PropertyInfo();
 
  string       GetDefaultValue()        { return m_def_value;  }
  PropertyType GetType()                { return m_type;       }
  string       GetName()                { return m_name;       }
  POptionList  GetOptionList ()         { return m_opt_list;   }
  bool         IsHidden()               { return m_hidden; } // Juan
  void         SetHidden(bool hidden)   { m_hidden = hidden; } // Juan
};

///////////////////////////////////////////////////////////////////////////////

class Property
{
 private:
  PPropertyInfo m_info; // puntero a su descriptor
  WPObjectBase m_object; // una propiedad siempre pertenece a un objeto

  string m_name;
  string m_value; 
    
 public:
  Property(PPropertyInfo info, PObjectBase obj = PObjectBase())
  {
    m_name = info->GetName();
    m_object = obj;
    m_info = info;
  };
  
  PObjectBase GetObject() { return m_object.lock(); }
  string GetName() { return m_name; };
  string GetValue() { return m_value; };
  void SetValue(string val) { m_value = val; };
  PPropertyInfo GetPropertyInfo() { return m_info; } 
  PropertyType GetType()          { return m_info->GetType();  }

  bool IsDefaultValue();
  void SetDefaultValue();
  
  ////////////////////
  void SetValue(const wxFont &font);
  void SetValue(const wxColour &colour);
  void SetValue(const wxString &str);
  void SetValue(const wxPoint &point);
  void SetValue(const wxSize &size);
  
  wxFont GetValueAsFont();
  wxColour GetValueAsColour();
  wxPoint GetValueAsPoint();
  wxSize GetValueAsSize();
  int GetValueAsInteger();
  wxString GetValueAsString();
  wxBitmap GetValueAsBitmap();
  
};


///////////////////////////////////////////////////////////////////////////////

class ObjectBase : public IObject, public enable_shared_from_this<ObjectBase>
{
 private:
  // cuenta de instancias de esta clase, será util para comprobar si 
  // efectivamente no se están produciendo leaks de memoria
  static int s_instances;
    
  string m_class;            // clase que repesenta el objeto
  ObjectType m_type;         // RTTI
  WPObjectBase m_parent;     // nodo padre
        
  ObjectVector m_children;   // hijos        
  PropertyMap  m_properties; // Propiedades del objeto
  PObjectInfo m_info;
  

 protected:
  // utilidades para imprimir el arbol 
  static const int INDENT;  // constante del número de espacios de la indentado
  string GetIndentString(int indent); // obtiene la cadena con el indentado
  
  ObjectVector& GetChildren()   { return m_children; };
  PropertyMap&  GetProperties() { return m_properties; };
  
  // Crea un elemento del objeto  
  virtual TiXmlElement* SerializeObject();
  
  // devuelve el puntero "this"
  PObjectBase GetThis()
  {
    return shared_from_this();
  }


  bool DoChildTypeOk (ObjectType type_child ,ObjectType type_parent);
  /*
   * Configura la instancia en su creación.
   *
   * Este método realiza todas las operaciones necesarias para configurar
   * el objeto en su creación.
   * Las clases derivadas (y esta misma) deberán llamar a esta función en 
   * el método NewInstance. De esta forma, emulamos el comportamiento de un
   * constructor.
   */
//  void SetupInstance(PObjectBase parent = PObjectBase());


 public:
  /**
   * Constructor. (debe ser "protegido" -> NewInstance)
   */
  ObjectBase (string class_name);
  
  // Mejor es que sea el propio objeto quien construya todas sus propiedades...
  //ObjectBase(PObjectInfo obj_info);
  
  /*
   * Pseudo-Constructor.
   * Crea una instancia de un objeto de forma dinámica.
   * De esta forma evitamos los problemas de C++ para usar métodos virtuales
   * en un contructor, o el problema de devolver un shared_ptr en lugar
   * de un puntero normal.
   */
/*  static PObjectBase NewInstance
    (string class_name, PObjectBase parent = PObjectBase());*/
  
  
  /**
   * Destructor.
   */
  virtual ~ObjectBase();

  /**
   * Obtiene el nombre del objeto.
   *
   * @note No confundir con la propiedad nombre que tienen algunos objetos.
   *       Cada objeto tiene un nombre, el cual será el mismo que el usado
   *       como clave en el registro de descriptores.
   */
  string     GetClassName ()            { return m_class;  } 
  
  /**
   * Obtiene el nodo padre.
   */  
  PObjectBase GetParent ()                   { return m_parent.lock();   }

  /**
   * Establece la conexión con el padre.
   */
  void SetParent(PObjectBase parent)  { m_parent = parent; }

  /**
   * Obtiene la propiedad identificada por el nombre.
   *
   * @note Notar que no existe el método SetProperty, ya que la modificación
   *       se hace a través de la referencia.
   */
  PProperty GetProperty (string name);
  
  /**
   * Añade una propiedad al objeto.
   * 
   * Este método será usado por el registro de descriptores para crear la
   * instancia del objeto.
   * Los objetos siempre se crearán a través del registro de descriptores.
   */
  void AddProperty (string propname, PProperty value);

  /**
   * Obtiene el número de propiedades del objeto.
   */
  unsigned int GetPropertyCount() { return m_properties.size(); }
  
  /**
   * Obtiene una propiedad del objeto.
   * @todo esta función deberá lanzar una excepción en caso de no encontrarse
   *       dicha propiedad, así se simplifica el código al no tener que hacer
   *       tantas comprobaciones.
   * Por ejemplo, el código sin excepciones sería algo así:
   *
   * @code
   *
   * PProperty plabel = obj->GetProperty("label");
   * PProperty ppos = obj->GetProperty("pos");
   * PProperty psize = obj->GetProperty("size");
   * PProperty pstyle = obj->GetProperty("style");
   *
   * if (plabel && ppos && psize && pstyle)
   * {
   *   wxButton *button = new wxButton(parent,-1,
   *    plabel->GetValueAsString(),
   *    ppos->GetValueAsPoint(),
   *    psize->GetValueAsSize(),
   *    pstyle->GetValueAsInteger());
   * }
   * else
   * {
   *   // manejo del error
   * }
   * 
   * @endcode
   *
   * y con excepciones:
   *
   * @code
   * 
   * try
   * {
   *   wxButton *button = new wxButton(parent,-1,
   *     obj->GetProperty("label")->GetValueAsString(),
   *     obj->GetProperty("pos")->GetValueAsPoint(),
   *     obj->GetProperty("size")->GetValueAsSize(),
   *     obj->GetProperty("style")->GetValueAsInteger());
   * }
   * catch (...)
   * {
   *   // manejo del error
   * }
   * 
   * @endcode
   *
   */
  PProperty    GetProperty (unsigned int idx); // throws ...;
  
  /**
   * Devuelve el primer antecesor cuyo tipo coincida con el que se pasa
   * como parámetro.
   *
   * Será útil para encontrar el widget padre.
   */
  PObjectBase FindNearAncestor(ObjectType type);
  
  /**
   * Obtiene el documento xml del arbol tomando como raíz el nodo actual.
   */
  TiXmlDocument* Serialize();
  
  /**
   * Añade un hijo al objeto.
   * Esta función es virtual, debido a que puede variar el comportamiento
   * según el tipo de objeto.
   *
   * @return true si se añadió el hijo con éxito y false en caso contrario.
   */
  virtual bool AddChild    (PObjectBase);
  virtual bool AddChild    (unsigned int idx, PObjectBase obj); 

  /**
   * Devuelve la posicion del hijo o GetChildCount() en caso de no encontrarlo
   */
  unsigned int GetChildPosition(PObjectBase obj);
  bool ChangeChildPosition(PObjectBase obj, unsigned int pos);

  /**
   * devuelve la posición entre sus hermanos
   */  
/*  unsigned int GetPosition();
  bool ChangePosition(unsigned int pos);*/
  
  
  /**
   * Elimina un hijo del objeto.
   */
  void RemoveChild (PObjectBase obj);
  void RemoveChild (unsigned int idx);

  /**
   * Obtiene un hijo del objeto.
   */
  PObjectBase GetChild (unsigned int idx);
  
  /**
   * Obtiene el número de hijos del objeto.
   */
  unsigned int  GetChildCount()    { return m_children.size(); }
  
  /**
   * Comprueba si el tipo de objeto pasado es válido como hijo del objeto.
   * Esta rutina es importante, ya que define las restricciónes de ubicación.
   */
  bool ChildTypeOk (ObjectType type);
  
  bool IsContainer() { return (GetObjectType() == T_CONTAINER); }
  
  PObjectBase GetLayout();

  /**
   * Devuelve el tipo de objeto.
   *
   * Deberá ser redefinida en cada clase derivada.
   */
  ObjectType GetObjectType() { return m_type; }
  void SetObjectType(ObjectType type) { m_type = type; }
  
  /**
   * Devuelve el descriptor del objeto.
   */
  PObjectInfo GetObjectInfo() { return m_info; };
  void SetObjectInfo(PObjectInfo info) { m_info = info; };
  
  /**
   * Imprime el arbol en un stream.
   */
  virtual void PrintOut(ostream &s, int indent);
  
  /**
   * Sobrecarga del operador inserción.
   */
  friend ostream& operator << (ostream &s, PObjectBase obj);
  
  /////////////////////////
  // Implementación de la interfaz IObject para su uso dentro de los
  // plugins
  
  int      GetPropertyAsInteger (const wxString& pname);
  wxFont   GetPropertyAsFont    (const wxString& pname);
  wxColour GetPropertyAsColour  (const wxString& pname);
  wxString GetPropertyAsString  (const wxString& pname);
  wxPoint  GetPropertyAsPoint   (const wxString& pname);
  wxSize   GetPropertyAsSize    (const wxString& pname);
  wxBitmap GetPropertyAsBitmap  (const wxString& pname);
  wxArrayInt GetPropertyAsIntegerArray(const wxString& pname);
  
  
  
};

///////////////////////////////////////////////////////////////////////////////

/**
 * Clase que guarda un conjunto de plantillas de código.
 */
class CodeInfo
{
 private:
  typedef map<string,string> TemplateMap;
  TemplateMap m_templates;
 public:
  string GetTemplate(string name);
  void AddTemplate(string name, string _template);
};

///////////////////////////////////////////////////////////////////////////////

/**
 * Información de objeto o MetaObjeto.
 */ 
class ObjectInfo
{
 public:
  /**
   * Constructor.
   */
  ObjectInfo(string class_name,
             ObjectType type = T_WIDGET);
             //WidgetType widget = W_GENERIC);

  virtual ~ObjectInfo() {};
  
  unsigned int GetPropertyCount() { return m_properties.size(); }
  
  /**
   * Obtiene el descriptor de la propiedad.
   */
  PPropertyInfo GetPropertyInfo(string name);
  PPropertyInfo GetPropertyInfo(unsigned int idx);
  
  /**
   * Añade un descriptor de propiedad al descriptor de objeto.
   */
  void AddPropertyInfo(PPropertyInfo pinfo);

  /**
   * Devuelve el tipo de widget asociado al objeto.
   *
   * Este atributo será util para saber como se representa el objeto,
   * permitiendo así, añadir widgets propios derivados de los widgets
   * originales.
   */
//  WidgetType GetWidgetType() { return m_widget; }
  
  /**
   * Devuelve el tipo de objeto, será util para que el constructor de objetos
   * sepa la clase derivada de ObjectBase que ha de crear a partir del
   * descriptor.
   */
  ObjectType GetObjectType() { return m_type;   }
  
  string GetClassName () { return m_class;  } 

  /**
   * Imprime el descriptor en un stream.
   */  
  virtual void PrintOut(ostream &s, int indent);
    
  
  /**
   * Sobrecarga del operador inserción.
   */
  friend ostream& operator << (ostream &s, PObjectInfo obj);

  // nos serán utiles para generar el nombre del objeto  
  unsigned int GetInstanceCount() { return m_numIns; }
  void IncrementInstanceCount()   { m_numIns++; }
  void ResetInstanceCount() { m_numIns = 0; }
    
  /**
   * Añade la información de un objeto al conjunto de clases base.
   */
  void AddBaseClass(PObjectInfo base) {  m_base.push_back(base); }

  PObjectInfo GetBaseClass(unsigned int idx);
  unsigned int GetBaseClassCount();
  
  
  //
  void SetIconFile(string icon) { m_icon = icon; };
  string GetIconFile() { return m_icon; }
    
  void AddCodeInfo(string lang, PCodeInfo codeinfo);  
  PCodeInfo GetCodeInfo(string lang);
  
  /**
   * Le asigna un componente a la clase.
   */
  void SetComponent(ComponentBase *c) { m_component = c; };
  ComponentBase* GetComponent() { return m_component; };
  
 private:
  typedef map<string,PCodeInfo> CodeInfoMap;  
  string m_class;         // nombre de la clase (tipo de objeto)
//  WidgetType m_widget;    // tipo de widget     (para una preview)
  ObjectType m_type;      // tipo del objeto [widget, sizer, sizeritem]
  string m_icon;

  CodeInfoMap m_codeTemp;  // plantillas de codigo K=language_name T=PCodeInfo

  unsigned int m_numIns;  // número de instancias del objeto

  PropertyInfoMap m_properties;
  ObjectInfoVector m_base; // clases base
  ComponentBase* m_component;  // componente asociado a la clase los objetos del
                               // designer
};

#endif 
