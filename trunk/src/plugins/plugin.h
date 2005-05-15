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

#ifndef __PLUGIN_H__
#define __PLUGIN_H__

#include "component.h"
#include "wx/wx.h"
#include <vector>


// Implementación de la librería. Este módulo debe estar implementado en la
// librería.
// En lugar de enlazarlo como un objeto para hacer el plugin
// haremos una plantilla para que el preprocesador la implemente dentro del
// propio módulo.

using namespace std;

class ComponentLibrary : public IComponentLibrary
{
 private:
  typedef struct
  {
    wxString name;
    IComponent *component;
  }AComponent;
  
  typedef struct 
  {
    wxString name;
    int value;
  } AMacro;

  vector<AComponent> m_components;
  vector<AMacro>     m_macros;  
  
 public:
  virtual ~ComponentLibrary() {};

  void RegisterComponent(const wxString &text, IComponent *c)
  {
    AComponent comp;
    comp.component = c;
    comp.name = text;
    
    m_components.push_back(comp);
  }
  
  void RegisterMacro(const wxString &text, const int value)
  {
    AMacro macro;
    macro.name = text;
    macro.value = value;
    
    m_macros.push_back(macro);
  }

  IComponent* GetComponent(unsigned int idx)
  {
    if (idx < m_components.size())
      return m_components[idx].component;
    return NULL;
  }

  wxString GetComponentName(unsigned int idx)
  {
    if (idx < m_components.size())
      return m_components[idx].name;

    return wxString();
  }
  
  wxString GetMacroName(unsigned int idx)
  {
    if (idx < m_macros.size())
      return m_macros[idx].name;

    return wxString();
  }
  
  int GetMacroValue(unsigned int idx)
  {
    if (idx < m_macros.size())
      return m_macros[idx].value;

    return 0;
  }
  
  unsigned int GetMacroCount()
  {
    return m_macros.size();
  }
  
  unsigned int GetComponentCount()
  {
    return m_components.size();
  }
};

/**
 * Clase base para componentes.
 */
class ComponentBase : public IComponent
{
 public:

  wxObject* Create(IObject *obj, wxObject *parent) { return NULL; }
  void OnCreated(IObjectView *obj, wxWindow *wxparent,
                 IObjectView *parent,
                 IObjectView *first_child) { /* nada */ };

  TiXmlElement* ExportToXrc(IObject *obj) { return NULL; };
  
  TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj) { return NULL; };
};

#endif // __PLUGIN_H__
