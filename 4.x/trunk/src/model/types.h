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
/**
 * @file types.h
 * @author 
 * @date 
 * @brief 
 */

#ifndef __TYPES_H__
#define __TYPES_H__

#include <map>
#include <vector>
#include <boost/smart_ptr.hpp>

#include <wx/wx.h>
#include <wx/string.h>

class ObjectType;

typedef boost::shared_ptr< ObjectType > PObjectType;
typedef boost::weak_ptr< ObjectType > WPObjectType;

/**
 * @class ObjectType
 * @brief Represents the type of object.
 *
 * The types of objects are needed to control location restrictions
 * of objects within the tree. These restrictions are defined
 * in objtypes.xml, where we define all main object types we need.
 *
 * Although all types are designed to be easily modified,
 * currently, en el código hay muchas dependencias con los nombres de tipos
 * concretos. Así que una modificación en el nombre de un tipo casi con toda
 * seguridad causará fallos en el funcionamiento de la aplicación.
 *
 * @todo Translation needed.
 * @todo hay que eliminar las dependencias en el código con los nombres de los
 *       tipos. Para ello lo mejor será definir una serie de atributos asociados
 *       al tipo.
 *       Por ejemplo, los objetos que sean "items" (objetos ficticios
 *       que añaden ciertas propiedades al objeto que contiene como puede ser
 *       un sizeritem), no deben aparecer en el "object tree" y deben mostrar
 *       las propiedades junto con las del objeto que contiene en el "object
 *       inspector". En ese caso, tanto el "object tree" como el
 *        "object inspector" consultarán al tipo si éste tiene el
 *       atributo item a true.
 */
class ObjectType
{
public:
	/**
	 * Constructor.
	 *
	 * @param name 		Object type name.
	 * @param id 		Identifier.
	 * @param hidden 	<b>true</b> if is a hidden object, <b>false</b> otherwise (Default: false).
	 * @param item 		<b>true</b> if is an item type, <b>false</b> otherwise (Default: false).
	 */
	ObjectType( wxString name, int id, bool hidden = false, bool item = false );

	int 		GetId()     { return m_id;     } /**< @return Object type ID. */
	wxString 	GetName()   { return m_name;   } /**< @return Object type name. */
//	bool   		IsHidden() 	{ return m_hidden; }
	bool   		IsItem() 	{ return m_item;   } /**< @return <b>true</b> if is an item type object, <b>false</b> otherwise. */

	/**
	 * Adds the object type to the list of possible children.
	 *
	 * @param type 	Shared pointer to object type.
	 * @param max 	Maximum children accepted by the object to add.
	 */
	void AddChildType( PObjectType type, int max = -1 );

	/**
	 * Finds whether the type passed as parameters are among the possible childrens.
	 *
	 * @param type_id Object type identifier.
	 * @return Maximum number of occurrences of the object as a child.
	 *         -1 = unlimited, 0 = none
	 */
	int FindChildType( int type_id );

	/**
	 * Finds whether the type passed as parameters are among the possible childrens.
	 *
	 * @param type Shared pointer to object type.
	 * @return Maximum number of occurrences of the object as a child.
	 *         -1 = unlimited, 0 = none
	 */
	int FindChildType( PObjectType type );

	/**
	 * @todo Description needed.
	 *
	 * @return 
	 */
	unsigned int GetChildTypeCount();

	/**
	 * @todo Description needed.
	 *
	 * @param idx  
	 */
	PObjectType GetChildType( unsigned int idx );

private:
	/**
	 * Register with the types of children and the maximum number possible of those.
	 * @note We will use smart-pointers of type "weak" because there may be many
	 *       cross-references.
	 */
	typedef std::map< WPObjectType, int > ChildTypeMap;

	int 			m_id; 			/**< Object identifier */
	wxString 		m_name; 		/**< String associated with the type */
	bool 			m_hidden;   	/**< Indicate if it is hidden in the ObjectTree */
	bool 			m_item;     	/**< Indicate if it is an "item".
									 * @todo Translation needed.
									 * @todo Los objetos contenidos en
									 * en un item, muestran las propiedades de éste junto
									 * con las propias del objeto. */
	ChildTypeMap 	m_childTypes; 	/**< Register of potential children */
};

/**
 * Property types.
 */
typedef enum
{
	PT_ERROR,
	PT_BOOL,
	PT_TEXT,
	PT_INT,
	PT_UINT,
	PT_BITLIST,
	PT_INTLIST,
	PT_UINTLIST,
	PT_OPTION,
	PT_MACRO,
	PT_WXSTRING,
	PT_WXPOINT,
	PT_WXSIZE,
	PT_WXFONT,
	PT_WXCOLOUR,
	PT_WXPARENT,
	PT_PATH,
	PT_FILE,
	PT_BITMAP,
	PT_STRINGLIST,
	PT_FLOAT,
	PT_WXSTRING_I18N,
	PT_PARENT,
	PT_CLASS
} PropertyType;

/**
 * @class IntList
 * @brief List of integers.
 */
class IntList
{
private:
	typedef std::vector< int > 	IntVector; 	/**< @todo Description needed. */
	IntVector 					m_ints; 	/**< @todo Description needed. */
	bool 						m_abs; 		/**< @todo Description needed. */

public:
	/**
	 * @todo Description needed.
	 *
	 * @param absolute_value 
	 */
	IntList( bool absolute_value = false ) : m_abs( absolute_value ) {}

	/**
	 * @todo Description needed.
	 *
	 * @param value 			
	 * @param absolute_value 	
	 */
	IntList( wxString value, bool absolute_value = false );

	/**
	 * @todo Description needed.
	 *
	 * @return 
	 */
	unsigned int GetSize() { return ( unsigned int)m_ints.size(); };

	/**
	 * @todo Description needed.
	 *
	 * @param idx  
	 */
	int GetValue( unsigned int idx ) { return m_ints[idx]; };

	/**
	 * @todo Description needed.
	 *
	 * @param value  
	 */
	void Add( int value );

	/** @todo Description needed. */
	void DeleteList();

	/**
	 * @todo Description needed.
	 *
	 * @param str  
	 */
	void SetList( wxString str );

	/** @todo Description needed. */
	wxString ToString();
};

#endif // __TYPES_H__
