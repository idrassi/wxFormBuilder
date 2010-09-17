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
// Warning!!!!!!
// ObjectBase::GetPropertyCount() != ObjectInfo::GetPropertyCount()
//
// In the first case it will return the total number of properties of the object.
// In the second case only return the number of properties defined for that class.
/**
 * @file types.h
 * @author 
 * @date 
 * @brief 
 */

#ifndef __OBJ__
#define __OBJ__

#include "model/types.h"
#include "utils/wxfbdefs.h"

#include <iostream>
#include <list>

#include <component.h>
#include <ticpp.h>

#include <wx/wx.h>
#include <wx/string.h>

/**
 * @class OptionList
 * @brief 
 *
 * @todo Description needed.
 */
class OptionList
{
private:
	/** @todo Description needed. */
	std::map< wxString, wxString > m_options;

public:
	/**
	 * @todo Description needed.
	 *
	 * @param option 		
	 * @param description 	
	 */
	void AddOption( wxString option, wxString description = wxString() )
	{
		m_options[option] = description;
	}
	/**
	 * @todo Description needed.
	 * 
	 * @return 
	 */
	unsigned int GetOptionCount()
	{
		return ( unsigned int )m_options.size();
	}
	/** @todo Description needed. */
	const std::map< wxString, wxString >& GetOptions()
	{
		return m_options;
	}
};

///////////////////////////////////////////////////////////////////////////////

/**
 * @class PropertyChild
 * @brief 
 * @internal
 * Data Container for children of a Parent property.
 */
class PropertyChild
{
public:
	wxString m_name; 			/**< @todo Description needed. */
	wxString m_defaultValue; 	/**< @todo Description needed. */
	wxString m_description; 	/**< @todo Description needed. */
};

/**
 * @class PropertyChild
 * @brief 
 * @todo Description needed.
 */
class PropertyInfo
{
	friend class Property;

private:
	wxString 					m_name; 		/**< @todo Description needed. */
	PropertyType 				m_type; 		/**< @todo Description needed. */
	wxString       				m_def_value; 	/**< @todo Description needed. */
	POptionList  				m_opt_list; 	/**< @todo Description needed. */
	std::list< PropertyChild > 	m_children; 	/**< Only used for parent properties. */
	bool 						m_hidden; 		/**< Juan. Determines if the property appears or not in XRC. */
	wxString					m_description; 	/**< @todo Description needed. */
	wxString					m_customEditor; /**< An optional custom editor for the property grid. */

public:
	/**
	 * Constructor.
	 * @todo Description needed.
	 * @param name 			Name.
	 * @param type  		Type.
	 * @param def_value 	Default value.  
	 * @param description 	Description.  
	 * @param description 	Custom editor.  
	 * @param opt_list 		Option list.  
	 * @param children 		Children.  
	 */
	PropertyInfo( wxString name, PropertyType type, wxString def_value,
				wxString description, wxString customEditor,
				POptionList opt_list, const std::list< PropertyChild >& children );

	/** Destructor. */
	~PropertyInfo();

	wxString       				GetDefaultValue() 	{ return m_def_value;  	} /**< @todo Description needed. */
	PropertyType 				GetType() 			{ return m_type;       	} /**< @todo Description needed. */
	wxString       				GetName() 			{ return m_name;       	} /**< @todo Description needed. */
	POptionList  				GetOptionList () 	{ return m_opt_list;   	} /**< @todo Description needed. */
	std::list< PropertyChild >* GetChildren() 		{ return &m_children; 	} /**< @todo Description needed. */
	wxString		 			GetDescription	() 	{ return m_description;	} /**< @todo Description needed. */
	wxString					GetCustomEditor() 	{ return m_customEditor; } /**< @todo Description needed. */
};

/**
 * @class EventInfo
 * @brief 
 * @todo Description needed.
 */
class EventInfo
{
private:
	wxString m_name; 			/**< @todo Description needed. */
	wxString m_eventClass; 		/**< @todo Description needed. */
	wxString m_defaultValue; 	/**< @todo Description needed. */
	wxString m_description; 	/**< @todo Description needed. */

public:
	/**
	 * Constructor.
	 * @todo Description needed.
	 * @param name 			
	 * @param eventClass  	
	 * @param defValue 		
	 * @param description 	
	 */
	EventInfo( const wxString &name,
				const wxString &eventClass,
				const wxString &defValue,
				const wxString &description);

	wxString GetName()           { return m_name; } 		/**< @todo Description needed. */
	wxString GetEventClassName() { return m_eventClass; } 	/**< @todo Description needed. */
	wxString GetDefaultValue()   { return m_defaultValue; } /**< @todo Description needed. */
	wxString GetDescription()    { return m_description; } 	/**< @todo Description needed. */
};

///////////////////////////////////////////////////////////////////////////////

/**
 * @class Property
 * @brief 
 * @todo Description needed.
 */
class Property
{
private:
	PPropertyInfo 	m_info;   /**< Pointer to its descriptor. */
	WPObjectBase 	m_object; /**< Pointer to the owner object. */
	wxString 		m_value;  /**< Property value. */

public:
	/**
	 * Constructor.
	 * @todo Description needed.
	 * @param info 	
	 * @param obj 	
	 */
	Property( PPropertyInfo info, PObjectBase obj = PObjectBase() )
	{
		m_object = obj;
		m_info = info;
	}

	PObjectBase GetObject() 			{ return m_object.lock(); }
	wxString GetName() 					{ return m_info->GetName(); }
	wxString GetValue() 				{ return m_value; }
	void SetValue( wxString& val ) 		{ m_value = val; }
	void SetValue( const wxChar* val ) 	{ m_value = val; }

	PPropertyInfo GetPropertyInfo() { return m_info; }
	PropertyType  GetType()         { return m_info->GetType();  }

	bool IsDefaultValue();
	bool IsNull();
	void SetDefaultValue();
	void ChangeDefaultValue( const wxString& value )
	{
		m_info->m_def_value = value;
	}

	////////////////////
	void SetValue( const wxFontContainer &font );
	void SetValue( const wxColour &colour );
	void SetValue( const wxString &str, bool format = false );
	void SetValue( const wxPoint &point );
	void SetValue( const wxSize &size );
	void SetValue( const int integer );
//	void SetValue( const wxAlignment alignment ); TODO
	void SetValue( const double val );

	wxFontContainer GetValueAsFont();
	wxColour 		GetValueAsColour();
	wxPoint  		GetValueAsPoint();
	wxSize   		GetValueAsSize();
	int      		GetValueAsInteger();
//	wxAlignment 	GetValueAsAlignment(); TODO
	wxString 		GetValueAsString();
	wxBitmap 		GetValueAsBitmap();
	wxString 		GetValueAsText(); 		// sustituye los ('\n',...) por ("\\n",...)

	wxArrayString 	GetValueAsArrayString();
	double 			GetValueAsFloat();
	void 			SplitParentProperty( std::map< wxString, wxString >* children );
	wxString 		GetChildFromParent( const wxString& childName );
};

class Event
{
private:
	PEventInfo  	m_info;   /**< Pointer to its descriptor. */
	WPObjectBase 	m_object; /**< Pointer to the owner object. */
	wxString 		m_value;  /**< Handler function name */

public:
	Event (	PEventInfo 	info, PObjectBase obj)
    : m_info(info), m_object(obj)
	{}

	void 		SetValue(const wxString &value) { m_value = value; }
	wxString 	GetValue()                  	{ return m_value; }
	wxString 	GetName()                   	{ return m_info->GetName(); }
	PObjectBase GetObject()              		{ return m_object.lock(); }
	PEventInfo 	GetEventInfo()            		{ return m_info; }
};

class PropertyCategory
{
private:
	wxString m_name;
	std::vector< wxString > m_properties;
	std::vector< wxString > m_events;
	std::vector< PPropertyCategory > m_categories;

public:

	PropertyCategory( wxString name ) : m_name( name ){}
	void AddProperty( wxString name ){ m_properties.push_back( name ); }
	void AddEvent( wxString name ){ m_events.push_back( name ); }
	void AddCategory( PPropertyCategory category ){ m_categories.push_back( category ); }
	wxString GetName(){ return m_name; }
	wxString GetPropertyName( size_t index )
	{
		if ( index < m_properties.size() )
			return m_properties[ index ];
		else
			return wxEmptyString;
	}

	wxString GetEventName( size_t index )
	{
		if ( index < m_events.size() )
			return m_events[ index ];
		else
			return wxEmptyString;
	}

	PPropertyCategory GetCategory( size_t index )
	{
		if ( index < m_categories.size() )
			return m_categories[ index ];
		else
			return PPropertyCategory();
	}

	size_t GetPropertyCount() { return m_properties.size(); }
	size_t GetEventCount() { return m_events.size(); }
	size_t GetCategoryCount() { return m_categories.size(); }
};

///////////////////////////////////////////////////////////////////////////////
namespace ticpp
{
	class Document;
	class Element;
}

class ObjectBase : public IObject, public boost::enable_shared_from_this<ObjectBase>
{
	friend class wxFBDataObject;
private:
	wxString     m_class;  // class name
	wxString     m_type;   // type of object
	WPObjectBase m_parent; // weak pointer, no reference loops please!

	ObjectBaseVector 	m_children;
	PropertyMap      	m_properties;
	EventMap         	m_events;
	PObjectInfo      	m_info;
	bool 				m_expanded; // is expanded in the object tree, allows for saving to file

protected:
	// utilites for implementing the tree
	static const int 	INDENT;  						// size of indent
	wxString 			GetIndentString(int indent); 	// obtiene la cadena con el indentado

	ObjectBaseVector& GetChildren()     { return m_children; };
	PropertyMap&      GetProperties()   { return m_properties; };

	// Create an object element
	void SerializeObject( ticpp::Element* serializedElement );

	// Get "this" pointer
	PObjectBase GetThis() { return shared_from_this(); }

public:

	/// Constructor.
	ObjectBase (wxString class_name);

	/// Destructor.
	virtual ~ObjectBase();

	/**
	* Sets whether the object is expanded in the object tree or not.
	*/
	void SetExpanded( bool expanded ){ m_expanded = expanded; }

	/**
	* Gets whether the object is expanded in the object tree or not.
	*/
	bool GetExpanded(){ return m_expanded; }

	/**
	* Get the name of the object.
	*
	* @note Do not confuse with the name property with some objects.
	*       Each object has a name, which will be the same as that used
	*       as the key in the registry of descriptors.
	*/
	wxString GetClassName () { return m_class;  }

	/** Gets the parent object */
	PObjectBase GetParent () { return m_parent.lock(); }

	/** Links the object to a parent */
	void SetParent(PObjectBase parent)  { m_parent = parent; }

	/**
	* Get the property identified by name.
	*
	* @note Note that SetProperty method doesn't exists, since modification
	*       is done through the reference.
	*/
	PProperty GetProperty( wxString name );

	PEvent GetEvent( wxString name );

	/**
	* Adds a property to the object.
	*
	* This method will be used in the descriptors registry to create the
	* object instance.
	* The objects are always created through the descriptors registry.
	*/
	void AddProperty( PProperty value );

	void AddEvent( PEvent event );

	/**
	* Gets the number of object properties.
	*/
	unsigned int GetPropertyCount() { return (unsigned int)m_properties.size(); }

	unsigned int GetEventCount()    { return m_events.size(); }

	/**
	* Gets an object property.
	* @todo This function should throw an exception if passed property is not found
	*        and simplifies the code by not having to do many checks.
	* For example, the code without exceptions would be something like:
	*
	* @code
	*
	* PProperty plabel = obj->GetProperty("label");
	* PProperty ppos = obj->GetProperty("pos");
	* PProperty psize = obj->GetProperty("size");
	* PProperty pstyle = obj->GetProperty("style");
	*
	* if (plabel && ppos && psize && pstyle)
	* {
	*   wxButton *button = new wxButton(parent,-1,
	*    plabel->GetValueAsString(),
	*    ppos->GetValueAsPoint(),
	*    psize->GetValueAsSize(),
	*    pstyle->GetValueAsInteger());
	* }
	* else
	* {
	*   // manejo del error
	* }
	*
	* @endcode
	*
	* with exceptions:
	*
	* @code
	*
	* try
	* {
	*   wxButton *button = new wxButton(parent,-1,
	*     obj->GetProperty("label")->GetValueAsString(),
	*     obj->GetProperty("pos")->GetValueAsPoint(),
	*     obj->GetProperty("size")->GetValueAsSize(),
	*     obj->GetProperty("style")->GetValueAsInteger());
	* }
	* catch (...)
	* {
	*   // error handling
	* }
	*
	* @endcode
	*
	*/
	PProperty GetProperty (unsigned int idx); // throws ...;

	PEvent GetEvent (unsigned int idx); // throws ...;

	/**
	* Returns the first ancestor whose type matches the passed parameter.
	*
	* It will be useful to find the parent widget.
	*/
	PObjectBase FindNearAncestor( wxString type );
	PObjectBase FindNearAncestorByBaseClass( wxString type );
	PObjectBase FindParentForm();

	/**
	* Gets the xml document from the tree taking current node as root node.
	*/
	void Serialize( ticpp::Document* serializedDocument );

	/**
	* Adds a child to the object.
	* This function is virtual, because it can change behavior
	* depending on the type of object.
	*
	* @return true if the child was added successfully and false otherwise.
	*/
	virtual bool AddChild    ( PObjectBase );
	virtual bool AddChild    ( unsigned int idx, PObjectBase obj );

	/**
	* Returns the position of the child or GetChildCount () in if not found.
	*/
	unsigned int GetChildPosition( PObjectBase obj );
	bool ChangeChildPosition( PObjectBase obj, unsigned int pos );

	/**
	* Returns the position among its siblings
	*/
/*  unsigned int GetPosition();
	bool ChangePosition( unsigned int pos );*/

	/**
	* Removes a child of the object.
	*/
	void RemoveChild( PObjectBase obj );
	void RemoveChild( unsigned int idx );
	void RemoveAllChildren(){ m_children.clear(); }

	/**
	* Gets a child of the object.
	*/
	PObjectBase GetChild( unsigned int idx );

	/**
	* Gets the number of children of the object.
	*/
	unsigned int  GetChildCount() { return (unsigned int)m_children.size(); }

	/**
	* Checks if passed object type is valid as a child of the object.
	* This routine is important because it defines the restrictions of location.
	*/
	//bool ChildTypeOk( wxString type );
	bool ChildTypeOk( PObjectType type );
// TODO: a single function that returns object type like GetObjectType()
	bool IsContainer() 	{ return ( GetObjectTypeName() == "container" ); }

	bool IsWizardPage() { return ( GetObjectTypeName() == "wizardpage" ); }

	PObjectBase GetLayout();

	/**
	* Returns the type of object.
	*
	* Must be redefined in every derived class.
	*/
	wxString GetObjectTypeName() { return m_type; }
	void SetObjectTypeName( wxString type ) { m_type = type; }

	/**
	* Returns the object descriptor.
	*/
	PObjectInfo GetObjectInfo() { return m_info; };
	void SetObjectInfo( PObjectInfo info ) { m_info = info; };

	/**
	* Returns the depth of the object in the tree.
	*/
	int Deep();

	/**
	* Prints the tree in a stream.
	*/
	//virtual void PrintOut(ostream &s, int indent);

	/**
	* Insertion operator overload.
	*/
	friend std::ostream& operator << (std::ostream &s, PObjectBase obj);

	//
	// IObject interface implementation for use within plugins.
	//
	bool 			IsNull 						( const wxString& pname );
	int      		GetPropertyAsInteger 		( const wxString& pname );
//	wxAlignment 	GetPropertyAsAlignment 		( const wxString& pname ); TODO
	wxFontContainer GetPropertyAsFont    		( const wxString& pname );
	wxColour 		GetPropertyAsColour  		( const wxString& pname );
	wxString 		GetPropertyAsString  		( const wxString& pname );
	wxPoint  		GetPropertyAsPoint   		( const wxString& pname );
	wxSize   		GetPropertyAsSize    		( const wxString& pname );
	wxBitmap 		GetPropertyAsBitmap  		( const wxString& pname );
	double	 		GetPropertyAsFloat	  		( const wxString& pname );

	wxArrayInt    	GetPropertyAsArrayInt 		( const wxString& pname );
	wxArrayString 	GetPropertyAsArrayString  	( const wxString& pname );
	wxString 		GetChildFromParentProperty 	( const wxString& parentName, const wxString& childName );
};

///////////////////////////////////////////////////////////////////////////////

/**
* Class that stores a set of code templates.
*/
class CodeInfo
{
private:
	typedef std::map< wxString, wxString > TemplateMap;
	TemplateMap m_templates;
public:
	wxString 	GetTemplate( wxString name );
	void 		AddTemplate( wxString name, wxString _template );
	void 		Merge( PCodeInfo merger );
};

///////////////////////////////////////////////////////////////////////////////

/**
* Object or metaobject informations.
*/
class ObjectInfo
{
public:
	/**
	* Constructor.
	*/
	ObjectInfo(wxString class_name, PObjectType type, WPObjectPackage package, bool startGroup = false );

	virtual ~ObjectInfo() {};

	PPropertyCategory GetCategory(){ return m_category; }

	unsigned int GetPropertyCount() { return (unsigned int)m_properties.size(); }
	unsigned int GetEventCount()    { return (unsigned int)m_events.size();     }

	/**
	* Gets the property descriptor.
	*/
	PPropertyInfo GetPropertyInfo( wxString name );
	PPropertyInfo GetPropertyInfo( unsigned int idx );

	PEventInfo GetEventInfo( wxString name );
	PEventInfo GetEventInfo( unsigned int idx );

	/**
	* Adds a property descriptor to the object descriptor.
	*/
	void AddPropertyInfo( PPropertyInfo pinfo );

	/**
	 * Adds a event descriptor.
	 */
	void AddEventInfo( PEventInfo evtInfo );

	/**
	* Add a default value for an inherited property.
	* @param baseIndex Index of base class returned from AddBaseClass.
	* @param propertyName Property of base class to assign a default value to.
	* @param defaultValue Default value of the inherited property.
	*/
	void AddBaseClassDefaultPropertyValue( size_t baseIndex, const wxString& propertyName, const wxString& defaultValue );

	/**
	* Get a default value for an inherited property.
	* @param baseIndex Index of base class in the base class vector
	* @param propertName Name of the property to get the default value for
	* @return The default value for the property
	*/
	wxString GetBaseClassDefaultPropertyValue( size_t baseIndex, const wxString& propertyName );

	/**
	* Devuelve el tipo de objeto, será util para que el constructor de objetos
	* sepa la clase derivada de ObjectBase que ha de crear a partir del
	* descriptor.
	*/
	wxString GetObjectTypeName() { return m_type->GetName();   }

	PObjectType GetObjectType() { return m_type; }

	wxString GetClassName () { return m_class;  }

	/**
	* Prints the descriptor in a stream.
	*/
	//virtual void PrintOut(ostream &s, int indent);

	/**
	* Insertion operator overload.
	*/
	friend std::ostream& operator << ( std::ostream &s, PObjectInfo obj );

	// Will be useful to generate the name of the object
	unsigned int GetInstanceCount() { return m_numIns; }
	void IncrementInstanceCount()   { m_numIns++; }
	void ResetInstanceCount() 		{ m_numIns = 0; }

	/**
	* Adds information about an object to all base classes.
	*/
	size_t AddBaseClass( PObjectInfo base )
	{
		m_base.push_back(base);
		return m_base.size() - 1;
	}

	/**
	* Check if the type is derived from the given parameter.
	*/
	bool IsSubclassOf( wxString classname );

	PObjectInfo GetBaseClass( unsigned int idx );
	unsigned int GetBaseClassCount();

	//
	void SetIconFile( wxBitmap icon ) { m_icon = icon; };
	wxBitmap GetIconFile() { return m_icon; }

	void SetSmallIconFile( wxBitmap icon ) { m_smallIcon = icon; };
	wxBitmap GetSmallIconFile() { return m_smallIcon; }

	void AddCodeInfo( wxString lang, PCodeInfo codeinfo );
	PCodeInfo GetCodeInfo( wxString lang );

	PObjectPackage GetPackage();

	bool IsStartOfGroup() { return m_startGroup; }

	/**
	* Assigns a component to the class.
	*/
	void SetComponent( IComponent *c ) 	{ m_component = c; };
	IComponent* GetComponent() 			{ return m_component; };

private:
	wxString 		m_class; 	// Class name (object type)
	PObjectType 	m_type;     // Object type
	WPObjectPackage m_package; 	// Package that the object comes from

	PPropertyCategory m_category;

	wxBitmap 	m_icon;
	wxBitmap 	m_smallIcon; 	// The icon for the property grid toolbar
	bool 		m_startGroup; 	// Place a separator in the palette toolbar just before this widget

	std::map< wxString, PCodeInfo > m_codeTemp;  // Code templates K=language_name T=PCodeInfo

	unsigned int m_numIns;  	// Number of instances of object

	std::map< wxString, PPropertyInfo > m_properties;
	std::map< wxString, PEventInfo >    m_events;

	std::vector< PObjectInfo > m_base; // Base classes
	std::map< size_t, std::map< wxString, wxString > > m_baseClassDefaultPropertyValues;
	IComponent* m_component;  	// componente asociado a la clase los objetos del designer
};

#endif
