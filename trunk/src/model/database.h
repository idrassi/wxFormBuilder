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

#ifndef __OBJ_DATABASE__
#define __OBJ_DATABASE__

#include "objectbase.h"
#include "tinyxml.h"
#include <wx/dynlib.h>

class ObjectPackage;
class ObjectDatabase;
class ObjectTypeDictionary;

typedef shared_ptr<ObjectPackage> PObjectPackage;
typedef shared_ptr<ObjectDatabase> PObjectDatabase;

/**
 * Paquete de clases de objetos.
 * Determinará la agrupación en la paleta de componentes.
 */
class ObjectPackage
{
 private:
  string m_name;    // nombre del paquete
  string m_desc;  // breve descripción del paquete

  // Vector con los objetos que están contenidos en el paquete  
  ObjectInfoVector m_objs;
 
 public:
  /**
   * Constructor.
   */  
  ObjectPackage(string name, string desc);
  
  /**
   * Incluye en el paquete la información de un objeto.
   */
  void Add(PObjectInfo obj) { m_objs.push_back(obj); };
  
  /** 
   * Obtiene el nombre del paquete.
   */
  string GetPackageName() { return m_name; }
  
  /**
   * Obtiene el texto que describe el paquete.
   */
  string GetPackageDescription() { return m_desc; }

  /**
   * Obtiene el número de objetos incluidos en el paquete.
   */
  unsigned int GetObjectCount() { return m_objs.size(); }

  /**
   * Obtiene la información de un objeto incluido en el paquete.
   */
  PObjectInfo GetObjectInfo(unsigned int idx);  
};



/**
 * Base de datos de objetos.
 * Todos las informaciones de objetos importadas de los archivos XML, serán
 * almacenados por esta clase.
 */
class ObjectDatabase
{
 private:
  typedef vector<PObjectPackage> PackageVector; 
  
  // diccionario para obtener el valor numérico a partir de la cadena
  // de texto del archivo XML.
  typedef map<string,PropertyType> PTMap;
  
  typedef map<string,PObjectType> ObjectTypeMap;
  typedef vector<wxDynamicLibrary *> CLibraryVector;
  
    
  string m_xmlPath; // directorio donde se encuentran los archivos xml
  string m_iconPath;
  ObjectInfoMap m_objs;
  PackageVector m_pkgs;
  PTMap m_propTypes;
  CLibraryVector m_libs;
  ObjectTypeMap m_types; // registro de tipos de objetos.
  
  /**
   * Inicializa el dicctionario de tipos de propiedades.
   */
  void InitPropertyTypes();
    
  /**
   * Carga los objetos de un paquete con todas sus propiedades salvo
   * los objetos heredados
   */
  PObjectPackage LoadPackage(string file);
  
  /**
   * Importa una librería de componentes y lo asocia a cada clase.
   */
  void ImportComponentLibrary(string libfile);
  
  /**
   * Incluye la información heredada de los objetos de un paquete.
   * En la segunda pasada configura cada paquete con sus objetos base.
   */
  void SetupPackage(string file);
  
  /**
   * Determina si el tipo de objeto hay que incluirlo en la paleta de 
   * componentes.
   */
  bool ShowInPalette(string type);
  bool HasCppProperties(string type);
  
  // rutinas de conversión
  PropertyType ParsePropertyType (string str);
  string       ParseObjectType   (string str); 

  
  PObjectType GetObjectType(string name);
  
  int CountChildrenWithSameType(PObjectBase parent,PObjectType type);
  
  void SetDefaultLayoutProperties(PObjectBase obj);
  
 public:    
  ObjectDatabase();
  ~ObjectDatabase();
  
  PObjectBase NewObject(PObjectInfo obj_info);

  /**
   * Obtiene la información de un objeto a partir del nombre de la clase.
   */
  PObjectInfo GetObjectInfo(string class_name);
  
  /**
   * Configura la ruta donde se encuentran los ficheros con la descripción.
   */
  void SetXmlPath(string path) { m_xmlPath = path; }
  
  /**
   * Configura la ruta donde se encuentran los iconos asociados a los objetos.
   */
  void SetIconPath(string path) { m_iconPath = path; }
  
  /**
   * Obtiene la ruta donde se encuentran los ficheros con la descripción de
   * objetos.
   */
  string GetXmlPath()          { return m_xmlPath; }
  
  /** 
   * Carga las descripciones de objetos a partir del fichero donde se incluyen
   * todos los paquetes.
   */
  bool LoadFile(string file="packages.xml");

  /**
   * Carga las definiciones de tipos de objetos.
   */
  bool LoadObjectTypes();  
  
  /**
   * Fabrica de objetos.
   * A partir del nombre de la clase se crea una nueva instancia de un objeto.
   */
  PObjectBase CreateObject(string class_name, PObjectBase parent = PObjectBase());

  /**
   * Fábrica de objetos a partir de un objeto XML.
   * Este método se usará para cargar un proyecto almacenado.
   */
  PObjectBase CreateObject(TiXmlElement *obj, PObjectBase parent = PObjectBase());

  /**
   * Crea un objeto como copia de otro.
   */
   
  PObjectBase CopyObject(PObjectBase obj);

  /**
   * Obtiene un paquete de objetos.
   */
  PObjectPackage GetPackage(unsigned int idx);
  
  /**
   * Obtiene el número de paquetes registrados.
   */
  unsigned int GetPackageCount() { return m_pkgs.size(); }
  
  /**
   * Resetea los contadores que acompañan al nombre.
   * La propiedad "name" es una propiedad especial, reservada para el nombre
   * de la instancia del objeto. Cada clase de objeto tiene asociado un contador
   * para no duplicar nombre en la creación de nuevos objetos
   * (p.e. m_button1, m_button2 ...)
   */
  void ResetObjectCounters();
};



#endif //__OBJ_DATABASE__
