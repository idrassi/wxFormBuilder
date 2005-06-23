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
// Written by
//   Jos� Antonio Hurtado - joseantonio.hurtado@gmail.com
//   Juan Antonio Ortega  - jortegalalmolda@gmail.com
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __COMPONENT_H__
#define __COMPONENT_H__


#include "wx/wx.h"
#include <wx/dynarray.h>
#include "tinyxml.h"

#define COMPONENT_TYPE_ABSTRACT 0
#define COMPONENT_TYPE_WINDOW   1
#define COMPONENT_TYPE_SIZER    2

class IComponent;

// interfaz para plugins
// la idea es proporcionar una interfaz para acceder a las propiedades del
// objeto de manera segura desde el plugin.

class IObject
{
 public:
  virtual bool     IsNull (const wxString& pname) = 0;
  virtual int      GetPropertyAsInteger (const wxString& pname) = 0;
  virtual wxFont   GetPropertyAsFont    (const wxString& pname) = 0;
  virtual wxColour GetPropertyAsColour  (const wxString& pname) = 0;
  virtual wxString GetPropertyAsString  (const wxString& pname) = 0;
  virtual wxPoint  GetPropertyAsPoint   (const wxString& pname) = 0;
  virtual wxSize   GetPropertyAsSize    (const wxString& pname) = 0;
  virtual wxBitmap GetPropertyAsBitmap  (const wxString& pname) = 0;
  virtual wxArrayInt GetPropertyAsArrayInt(const wxString& pname) = 0;
  virtual wxArrayString GetPropertyAsArrayString(const wxString& pname) = 0;
};

// interfaz para manejar la vista de un objeto

class IObjectView
{
 public:
  virtual wxWindow* Window() = 0;
  virtual wxSizer*  Sizer() = 0;
  virtual IObject*  Object() = 0;   
};

// Interfaz para almacenar todos los componentes de un plugin
// es una clase abstracta y ser� el objeto que exportar� la DLL.
class IComponentLibrary
{
 public:
    
  // usadas por el plugin para registrar los componentes y macros
  virtual void RegisterComponent(const wxString &text, IComponent *c) = 0;
  virtual void RegisterMacro(const wxString &text, const int value) = 0;

  // usadas por wxFormBuilder para extraer los componentes y macros
  virtual IComponent* GetComponent(unsigned int idx) = 0;
  virtual wxString    GetComponentName(unsigned int idx) = 0;
  virtual wxString    GetMacroName(unsigned int i) = 0;
  virtual int         GetMacroValue(unsigned int i) = 0; 
  
  virtual unsigned int GetMacroCount() = 0;
  virtual unsigned int GetComponentCount() = 0;
};

/**
 * Interfaz para componentes
 */
class IComponent
{
 public:
  /**
   * Crea la instancia del objeto-wx, bien sea un wxWindow* o un wxSizer*
   */  
  virtual wxObject* Create(IObject *obj, wxObject *parent) = 0;
  
  /**
   * Es llamada una vez creado el objeto y sus respectivos hijos.
   * Esta funci�n ser� de utilidad en los objetos "ficticios" tales 
   * como "sizeritem" o "notebookpage", gracias al puntero al primer_hijo 
   * (y �nico) podremos a�adir el objeto al sizer o al notebook.
   *
   * @param obj vista del objeto que se ha creado.
   * @param wxparent widget padre.
   * @param parent vista del objeto padre
   * @param first_child vista del primer hijo.
   */
  virtual void OnCreated(IObjectView *obj, wxWindow *wxparent, 
                         IObjectView *parent,
                         IObjectView *first_child) = 0;

  /**
   * Dada una instancia del objeto obtenemos un nodo XRC.
   */
  virtual TiXmlElement* ExportToXrc(IObject *obj) = 0;
  
  /**
   * Dado un objeto XML en formato XRC devuelve otro objeto XML en formato
   * wxFormBuilder.
   */
  virtual TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj) = 0;
  
  /**
   * Conservar la tabla de manejadores de eventos original del componente.
   *
   * Algunos componentes no deben dejar a wxFormBuilder redefinir su tabla
   * de manejadores de eventos, en aquellos casos devolver "true"
   */
  virtual bool KeepEvtHandler() = 0; // No es necesaria...
  
  
  /**
   *
   */
  virtual int GetComponentType() = 0;
};



// funci�n que nos devolver� la librer�a para ser usada dentro de la aplicaci�n
extern "C" 
{
  IComponentLibrary * GetComponentLibrary();
};



#define BEGIN_LIBRARY()  \
\
extern "C" WXEXPORT IComponentLibrary * GetComponentLibrary()  \
{ \
  IComponentLibrary * lib = new ComponentLibrary();

/*  
#define COMPONENT(name,class)  \
  lib->RegisterComponent(_T(name),new class());
*/

#define MACRO(name) \
  lib->RegisterMacro(_T(#name),name);
  
#define END_LIBRARY()   return lib; }

#define WINDOW_COMPONENT(name,class) \
  _REGISTER_COMPONENT(name,class,COMPONENT_TYPE_WINDOW)

#define SIZER_COMPONENT(name,class) \
  _REGISTER_COMPONENT(name,class,COMPONENT_TYPE_SIZER)

#define ABSTRACT_COMPONENT(name,class) \
  _REGISTER_COMPONENT(name,class,COMPONENT_TYPE_ABSTRACT)

#define _REGISTER_COMPONENT(name,class,type)  \
  {                                     \
    ComponentBase *c = new class();     \
    c->__SetComponentType(type);        \
    lib->RegisterComponent(_T(name),c); \
  }


#endif //__COMPONENT_H__
