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

#ifndef __TYPES__
#define __TYPES__

#include <wx/wx.h>
#include <wx/string.h>

#include <map>
#include <vector>
#include <boost/smart_ptr.hpp>

class ObjectType;

typedef boost::shared_ptr< ObjectType > PObjectType;
typedef boost::weak_ptr< ObjectType > WPObjectType;

/**
 * Represents the type of object.
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
	ObjectType(wxString name, int id, bool hidden = false, bool item = false);

	int 		GetId()     { return m_id;     }
	wxString 	GetName()   { return m_name;   }
//	bool   		IsHidden() 	{ return m_hidden; }
	bool   		IsItem() 	{ return m_item;   }

	/**
	* Adds the object type to the list of possible children.
	*/
	void AddChildType( PObjectType type, int max = -1 );

	/**
	* Finds whether the type passed as parameters are among the possible childrens.
	* @return Maximum number of occurrences of the object as a child.
	*         -1 = unlimited, 0 = none
	*/
	int FindChildType( int type_id );
	int FindChildType( PObjectType type );

	unsigned int GetChildTypeCount();
	PObjectType GetChildType( unsigned int idx );

private:
	/**
	* Register with the types of children and the maximum number possible of those.
	* @note We will use smart-pointers of type "weak" because there may be many
	*       cross-references.
	*/
	typedef std::map< WPObjectType, int > ChildTypeMap;

	int m_id; 			// Pbject identifier */
	wxString m_name; 	// String associated with the type */
	bool m_hidden;   	// Indicate if it is hidden in the ObjectTree */
	bool m_item;     	/* 	Indicate if it is an "item". Los objetos contenidos en
							en un item, muestran las propiedades de éste junto
							con las propias del objeto. */

	/** Register of potential children */
	ChildTypeMap m_childTypes;
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
/*
typedef enum
{
	W_NO_WIDGET,
	W_GENERIC,    // Case that our widget is not included
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
* List of integers.
*/
class IntList
{
private:
	typedef std::vector< int > IntVector;
	IntVector m_ints;
	bool m_abs;

public:
	IntList( bool absolute_value = false )
	:
	m_abs( absolute_value )
	{
	}

	IntList( wxString value, bool absolute_value = false );

	unsigned int GetSize() { return ( unsigned int)m_ints.size(); };
	int GetValue( unsigned int idx ) { return m_ints[idx]; };
	void Add( int value );
	void DeleteList();
	void SetList( wxString str );
	wxString ToString();
};

#endif // __TYPES__
