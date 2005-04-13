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
// Generación de código XRC
// Juan Antonio Ortega (jortegalalmolda@gmail.com)

#ifndef _XRC_CODE_GEN_
#define _XRC_CODE_GEN_

#include "codegen.h"

using namespace std;

/**
 * Generador de código XRC.
 */
class XrcCodeGenerator : public CodeGenerator
{
 private:
  PCodeWriter m_cw;
  
  /**
   * Documento XML que contiene la información de todos los componentes
   * contemplados en el formato XRC (xrc.xml)
   */
  TiXmlDocument m_xrcDb;
  
  TiXmlElement* GetXrcClassInfo(const string &classname);
  void LinkValues(TiXmlElement *element, TiXmlElement *xrcInfo,
                  const PObjectBase obj);
  
  /**
   * Dado un objeto, crea un árbol XML en formato XRC
   */
  TiXmlElement* GetElement(PObjectBase project);
  
  /**
   * Determina si XRC soporta la clase "className"
   */
  bool IsSupported(const string& className);
  
  /**
   * Devuelve el nombre de la clase. Será el resultado de GetClassName()
   * salvo para Dialog, Frame y Panel, que devolverá wxDialog, wxFrame y
   * wxPanel respectivamente.
   */
  string GetClassName(const PObjectBase obj);
  
  /**
   * Devuelve un nodo de TinyXml con el nombre de la propiedad traducida
   * a XRC.
   */
  TiXmlElement* GetPropNameElement(const PProperty prop);
  
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
   * Determina si la propiedad prop debe aparecer en el código XRC. Devuelve
   * falso para propiedades inexistentes en XRC y para propiedades sin valor
   */
  bool IsHidden(const PProperty prop);
  
 public:
    
  /**
   * Constructor.
   */
  XrcCodeGenerator();

  /**
   * Configura el escritor de código para el fichero XML.
   */
  void SetWriter(PCodeWriter cw) { m_cw = cw; }

  /**
   * Genera el código XRC del proyecto.
   */  
  bool GenerateCode(PObjectBase project); 
};


#endif //_XRC_CODE_GEN_
