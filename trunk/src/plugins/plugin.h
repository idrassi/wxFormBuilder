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

#ifndef __PLUGIN_H__
#define __PLUGIN_H__

#include "component.h"
#include "wx/wx.h"
#include <vector>
#include <map>

// Implementaci�n de la librer�a. Este m�dulo debe estar implementado en la
// librer�a.
// En lugar de enlazarlo como un objeto para hacer el plugin
// haremos una plantilla para que el preprocesador la implemente dentro del
// propio m�dulo.

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
  
  typedef struct
  {
    wxString name, syn;
  } ASynonymous;

  vector<AComponent>  m_components;
  vector<AMacro>      m_macros;  
  typedef map<wxString,wxString> SynMap;
  SynMap m_synMap;
  
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
  
  void RegisterMacroSynonymous(const wxString &syn, const wxString &name)
  {
    /*ASynonymous asyn;
    asyn.name = name;
    asyn.syn = syn;
    
    m_synonymous.push_back(asyn);*/
    m_synMap.insert(SynMap::value_type(syn, name));
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
  
  /*wxString GetMacroSynonymous(unsigned int idx)
  {
    if (idx < m_synonymous.size())
      return m_synonymous[idx].syn;
      
    return wxString();
  }
  
  wxString GetSynonymousName(unsigned int idx)
  {
    if (idx < m_synonymous.size())
      return m_synonymous[idx].name;
      
    return wxString();
  }*/
  
  bool FindSynonymous(const wxString& syn, wxString& trans)
  {
    bool found = false;
    SynMap::iterator it = m_synMap.find(syn);
    if (it != m_synMap.end())
    {
      found = true;
      trans = it->second;
    }
    
    return found;
  }
  
  unsigned int GetMacroCount()
  {
    return m_macros.size();
  }
  
  unsigned int GetComponentCount()
  {
    return m_components.size();
  }
  
  /*unsigned int GetSynonymousCount()
  {
    return m_synonymous.size();
  }*/
};

/**
 * Clase base para componentes.
 */
class ComponentBase : public IComponent
{
 private:
  int m_type;
  
 public:
 
  ComponentBase() : m_type(0) {};
  
  void __SetComponentType(int type)
  {
    m_type = (type >= 0 && type <= 2 ? type : COMPONENT_TYPE_ABSTRACT);
  };

  wxObject* Create(IObject *obj, wxObject *parent) { return NULL; }
  void OnCreated(IObjectView *obj, wxWindow *wxparent,
                 IObjectView *parent,
                 IObjectView *first_child) { /* nada */ };

  TiXmlElement* ExportToXrc(IObject *obj) { return NULL; };
  
  TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj) { return NULL; };
  
  bool KeepEvtHandler() { return false; }
  
  int GetComponentType() { return m_type; };
};

#endif // __PLUGIN_H__
