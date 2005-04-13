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

#ifndef __XRC_FILTER__
#define __XRC_FILTER__

#include "model/objectbase.h"

/**
 * Filtro de conversión de/a formato XRC.
 */
class XrcFilter
{
 private: 
  /**
   * Documento XML que contiene la información de todos los componentes
   * contemplados en el formato XRC (xrc.xml)
   */
  TiXmlDocument m_xrcDb;  
  
  /**
   * Dado el nombre de una clase obtiene la información XRC para dicha clase,
   * o NULL si no está definida en el formato XRC.
   */
  TiXmlElement* GetXrcClassInfo(const string &classname);
  
  /**
   * Enlaza todas las propiedades de un objeto en un nodo XML.
   */
  void LinkValues(TiXmlElement *element, TiXmlElement *xrcInfo,
                  const PObjectBase obj);
  /**
   * "Cuelga" de propElement el valor de la propiedad prop.
   */
  void LinkValue(const PProperty prop, TiXmlElement *propElement);
  
  /**
   * "Cuelga" de propElement la descripción de la fuente font en el formato
   * XRC
   */
  void LinkFont(const wxFont &font, TiXmlElement *propElement);  
  
  /**
   * Devuelve el nombre de la clase. Será el resultado de GetClassName()
   * salvo para Dialog, Frame y Panel, que devolverá wxDialog, wxFrame y
   * wxPanel respectivamente.
   */
  string GetClassName(const PObjectBase obj);

  /**
   * Dado un objeto, crea un árbol XML en formato XRC
   */
  TiXmlElement* GetElement(PObjectBase project);

  
 public: 
    
   XrcFilter(); 
    
  /**
   * Obtiene el documento XML en formato XRC de un proyecto wxFB.
   */
  TiXmlDocument *GetXrcDocument (PObjectBase project);

  
  /**
   * Dado un árbol XML en formato XRC, crea el arbol de objetos asociado.
   */
  PObjectBase GetObject(TiXmlElement *xrcObj);

};

/**
 * Filtro de importación de un fichero XRC.
 */
//class XrcLoader
//{
// public:
//  void LoadFile(string file, PObjectBase parent);
//};

#endif //__XRC_FILTER__
