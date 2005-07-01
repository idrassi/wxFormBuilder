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

/*
  NOTAS:
  
  La implementación realizada para la generación de las rutas relativas
  es un "apaño" y no una solución.
  
  En valor de toda propiedad que sea una ruta de un fichero o un directorio
  debe estar de forma absoluta, de lo contrario no funcionará la generación
  de código.
*/

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
 private:
  bool m_useRelativePath;
  string m_basePath;
  
 public:
  CppTemplateParser(PObjectBase obj, string _template); 
  
  // redefinidas para C++
  PTemplateParser CreateParser(PObjectBase obj, string _template); 
  string RootWxParentToCode();
  //string PropertyToCode(PProperty property); 
  string ValueToCode(PropertyType type, string value);
  
  // genera rutas relativas en los nombres de archivo
  bool UseRelativePath(bool relative = false, string basePath = "");
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
  
  bool m_useRelativePath;
  string m_basePath;
  
  /**
   * Las macros predefinidas no generarán defines.
   */
  set<string> m_predMacros;
  
  void SetupPredefinedMacros();

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
  
  /**
   * Añade un control a una toolbar. Hay que pasarle el objectinfo de tipo
   * wxWindow, donde se encuentra la plantilla, y el objectbase del control
   */
  void GenAddToolbar(PObjectInfo info, PObjectBase obj);
  
 public:
  /**
   * Convierte una cadena de texto a formato "C/C++"
   */
  static string ConvertCppString(string text); 
  
  /**
   * Convierte un path a path relativo.
   */
  //static string ConvertToRelativePath(string path, string basePath);
  
  /**
   * Convierte una cadena de texto con el nombre de un fichero XPM
   * y genera el nombre del identificador de "C/C++" asociado.
   */
  static string ConvertXpmName(string text);
  
  CppCodeGenerator();
    
  /**
   * Configura el escritor de código para el fichero de cabecera.
   */ 
  void SetHeaderWriter(PCodeWriter cw) { m_header = cw; }
  
  /**
   * Configura el escritor de código para el fichero de fuente.
   */
  void SetSourceWriter(PCodeWriter cw) { m_source = cw; }


  /**
   * Configura el path de referencia para generar las rutas relativas
   * al path que se pasa como parámetro.
   *
   * @nota el path se genera con el caracter barra '/' ya que sobre windows
   *       los compiladores interpretan correctamente el path.
   */
  bool UseRelativePath(bool relative = false, string basePath = "");


  /**
   * Genera el código del proyecto.
   */  
  bool GenerateCode(PObjectBase project); 
};


#endif //_CPP_CODE_GEN_
