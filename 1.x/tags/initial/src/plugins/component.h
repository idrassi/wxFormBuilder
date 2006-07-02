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

#ifndef __COMPONENT_H__
#define __COMPONENT_H__


#include "wx/wx.h"
#include <wx/dynarray.h>

class ComponentBase;

// interfaz para plugins
// la idea es proporcionar una interfaz para acceder a las propiedades del
// objeto de manera segura desde el plugin.

class IObject
{
 public:
  virtual int      GetPropertyAsInteger (const wxString& pname) = 0;
  virtual wxFont   GetPropertyAsFont    (const wxString& pname) = 0;
  virtual wxColour GetPropertyAsColour  (const wxString& pname) = 0;
  virtual wxString GetPropertyAsString  (const wxString& pname) = 0;
  virtual wxPoint  GetPropertyAsPoint   (const wxString& pname) = 0;
  virtual wxSize   GetPropertyAsSize    (const wxString& pname) = 0;
  virtual wxBitmap GetPropertyAsBitmap  (const wxString& pname) = 0;
  virtual wxArrayInt GetPropertyAsIntegerArray(const wxString& pname) = 0;
};

// Interfaz para almacenar todos los componentes de un plugin
// es una clase abstracta y ser� el objeto que exportar� la DLL.
class ComponentLibraryBase
{
 public:
    
  // usadas por el plugin para registrar los componentes y macros
  virtual void RegisterComponent(const wxString &text, ComponentBase *c) = 0;
  virtual void RegisterMacro(const wxString &text, const int value) = 0;

  // usadas por wxFormBuilder para extraer los componentes y macros
  virtual ComponentBase* GetComponent(unsigned int idx) = 0;
  virtual wxString       GetComponentName(unsigned int idx) = 0;
  virtual wxString       GetMacroName(unsigned int i) = 0;
  virtual int            GetMacroValue(unsigned int i) = 0; 
  
  virtual unsigned int GetMacroCount() = 0;
  virtual unsigned int GetComponentCount() = 0;
};

class ComponentBase
{
 public:
  /**
   * Crea la instancia del objeto, bien sea un wxWindow* o un wxSizer*
   */  
  virtual wxObject* Create(IObject *obj, wxObject *parent) = 0;

   // de momento s�lo nos hace falta que cree la instancia, el resto
   // de informaci�n lo toma del archivo XML.
};

// funci�n que nos devolver� la librer�a para ser usada dentro de la aplicaci�n
extern "C" 
{
  ComponentLibraryBase * GetComponentLibrary();
};



#define BEGIN_LIBRARY()  \
\
extern "C" WXEXPORT ComponentLibraryBase * GetComponentLibrary()  \
{ \
  ComponentLibraryBase * lib = new ComponentLibrary();
  
#define COMPONENT(name,class)  \
  lib->RegisterComponent(_T(name),new class());

#define MACRO(name) \
  lib->RegisterMacro(_T(#name),name);
  
#define END_LIBRARY()   return lib; }


#endif //__COMPONENT_H__
