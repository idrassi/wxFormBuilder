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

#ifndef __TYPES__
#define __TYPES__

#include <vector>
#include <string>
#include <map>
#include <boost/smart_ptr.hpp>

#include "wx/wx.h"

using namespace std;
using namespace boost;

class ObjectType;

typedef shared_ptr<ObjectType> PObjectType;
typedef weak_ptr<ObjectType> WPObjectType;

/**
 * Representa el tipo de objeto.
 *
 * Los tipos de objetos son necesarios para controlar las restricciones de
 * ubicaci�n de los objetos dentro del �rbol. Dichas restricciones vendr�n 
 * establecidas en el fichero objtypes.xml, y en principio se pueden definir 
 * tantos tipos de objetos como sean necesarios.
 *
 * Aunque el conjunto de tipos est� pensado para que sea f�cilmente modificable,
 * actualmente, en el c�digo hay muchas dependencias con los nombres de tipos 
 * concretos. As� que una modificaci�n en el nombre de un tipo casi con toda 
 * seguridad causar� fallos en el funcionamiento de la aplicaci�n.
 * 
 * @todo hay que eliminar las dependencias en el c�digo con los nombres de los
 *       tipos. Para ello lo mejor ser� definir una serie de atributos asociados
 *       al tipo. 
 *       Por ejemplo, los objetos que sean "items" (objetos ficticios
 *       que a�aden ciertas propiedades al objeto que contiene como puede ser
 *       un sizeritem), no deben aparecer en el "object tree" y deben mostrar
 *       las propiedades junto con las del objeto que contiene en el "object 
 *       inspector". En ese caso, tanto el "object tree" como el
 *        "object inspector" consultar�n al tipo si �ste tiene el
 *       atributo item a true.
 */
class ObjectType
{
 public:
 
  ObjectType(string name, int id, bool hidden = false, bool item = false);
  
  int    GetId()     { return m_id;     }
  string GetName()   { return m_name;   }
  bool   IsHidden()  { return m_hidden; }
  bool   IsItem()    { return m_item;   }

  
  /**
   * A�ade el tipo de objeto a la lista de posibles hijos.
   */
  void AddChildType(PObjectType type, int max = -1);
  
  /**
   * Busca si el tipo pasado como par�metros est� entre sus posibles
   * hijos.
   * @return numero m�ximo de ocurrencias del objeto como hijo.
   *         -1 = numero ilimitado, 0 = ninguna
   */
  int FindChildType(int type_id);
  int FindChildType(PObjectType type);
  
 private: 
  
  /**
   * Registro con los tipos de los hijos posibles y el n�mero m�ximo
   * de estos.
   * @note vamos a usar smart-pointers de tipo "weak" ya que puede haber muchas
   *       referencias cruzadas.
   */
  typedef map<WPObjectType, int> ChildTypeMap;
  
  int m_id;        /**< identificador num�rico del tipo de objeto */
  string m_name;   /**< cadena de texto asociado al tipo */
  bool m_hidden;   /**< indica si est� oculto en el ObjectTree */
  bool m_item;     /**< indica si es un "item". Los objetos contenidos en
                     *  en un item, muestran las propiedades de �ste junto
                     *  con las propias del objeto.
                     */

  ChildTypeMap m_childTypes; /**< registro de posibles hijos */
};

/**
 * Tipos de propiedades.
 */
typedef enum
{
  PT_ERROR,
  PT_BOOL,
  PT_TEXT,
  PT_INTEGER, 
  PT_BITLIST,
  PT_INTLIST,
  PT_OPTION,
  PT_MACRO,
  PT_WXSTRING,
  PT_WXPOINT,
  PT_WXSIZE,
  PT_WXFONT,
  PT_WXCOLOUR,
  PT_PATH,
  PT_BITMAP
} PropertyType;
/*  
typedef enum
{
  W_NO_WIDGET,
  W_GENERIC,    // para el caso de que nuestro widget no est� incluido
  W_BUTTON,
  W_COMBO_BOX,
  W_TEXT_CTRL,
  W_STATIC_TEXT,
  W_PANEL,
  W_BOX_SIZER,
  W_GRID_SIZER,
  W_FLEX_GRID_SIZER,
  W_CHECK_BOX,
  W_SPACER,
  W_SIZERITEM,
  W_GRID,
  W_STATIC_BITMAP
  //W_PLUGIN
} WidgetType;
*/
/**
 * Lista de enteros.
 */
class IntList
{
  private:
    typedef vector<int> IntVector;
    IntVector m_ints;
    
  public:
   IntList() {};
   IntList(string value);
   
   unsigned int GetSize() { return m_ints.size(); };
   int GetValue(unsigned int idx) { return m_ints[idx]; };
   void Add(int value) { m_ints.push_back(value); };
   void DeleteList();
   void SetList(string str);
   string ToString();
};


#endif // __TYPES__
