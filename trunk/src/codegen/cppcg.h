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

#ifndef _CPP_CODE_GEN_
#define _CPP_CODE_GEN_

#include <set>
#include "codegen.h"

using namespace std;

/**
 * Analizador de plantillas para C++.
 */
class CppTemplateParser : public TemplateParser
{
 public:
  CppTemplateParser(PObjectBase obj, string _template); 
  
  // redefinidas para C++
  PTemplateParser CreateParser(PObjectBase obj, string _template); 
  string RootWxParentToCode();
  //string PropertyToCode(PProperty property); 
  string ValueToCode(PropertyType type, string value);
};

/**
 * Generador de código C++.
 */
class CppCodeGenerator : public CodeGenerator
{
 private:
  typedef enum {P_PRIVATE, P_PROTECTED, P_PUBLIC} Permission;
  
  PCodeWriter m_header;
  PCodeWriter m_source;

  /**
   * Dado un objeto y el nombre de una plantilla, obtiene el código.
   */
  string GetCode(PObjectBase obj, string name);

  /**
   * Guarda el conjunto de clases de objetos del proyecto para generar
   * los includes.
   */
  void FindDependencies(PObjectBase obj, set<PObjectInfo> &info_set);
  
  /**
   * Guarda el conjunto de "includes" que hay que generar para las propiedades
   * PT_XPM_BITMAP.
   */
  void FindXpmProperties(PObjectBase obj, set<string> &set);
  
  /**
   * Guarda todos las propiedades de objetos de tipo "macro" para generar
   * su posterior '#define'.
   */
  void FindMacros(PObjectBase obj, set<string> &macro_set);

  /**
   * Genera la declaración de clases en el fichero de cabecera.
   */
  void GenClassDeclaration(PObjectBase class_obj);   
  
  /**
   * Función recursiva para la declaración de atributos, usada dentro
   * de GenClassDeclaration.
   */
  void GenAttributeDeclaration(PObjectBase obj, Permission perm);
  
  /**
   * Genera la sección de '#include' fichero.
   */
  void GenIncludes(PObjectBase project);
  
  /**
   * Genera la sección de '#include' para las propiedades XPM.
   */
  void GenXpmIncludes(PObjectBase project);
  
  /**
   * Genera la sección de '#define' macro.
   */
  void GenDefines(PObjectBase project);

  /**
   * Genera el constructor de una clase.
   */ 
  void GenConstructor(PObjectBase class_obj);
  
  /**
   * Realiza la construcción de los objetos, configurando las propiedades del
   * objeto y las de layout.
   * El algoritmo es similar al de generación de la vista previa en el designer.
   */
  void GenConstruction(PObjectBase obj, bool is_widget);
  
  /**
   * Configura las propiedades del objeto, tanto las propias como las heredadas.
   * Se le pasa la información de la clase porque recursivamente, realizará
   * la configuración en las super-clases.
   */
  void GenSettings(PObjectInfo info, PObjectBase obj);
  
 public:
  /**
   * Convierte una cadena de texto a formato "C/C++"
   */
  static string ConvertCppString(string text); 
  
  /**
   * Convierte una cadena de texto con el nombre de un fichero XPM
   * y genera el nombre del identificador de "C/C++" asociado.
   */
  static string ConvertXpmName(string text);
    
  /**
   * Configura el escritor de código para el fichero de cabecera.
   */ 
  void SetHeaderWriter(PCodeWriter cw) { m_header = cw; }
  
  /**
   * Configura el escritor de código para el fichero de fuente.
   */
  void SetSourceWriter(PCodeWriter cw) { m_source = cw; }

  /**
   * Genera el código del proyecto.
   */  
  bool GenerateCode(PObjectBase project); 
};


#endif //_CPP_CODE_GEN_
