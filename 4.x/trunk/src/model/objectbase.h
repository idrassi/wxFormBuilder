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
 * @file objectbase.h
 * @author 
 * @date 
 * @brief 
 */

#ifndef __OBJECTBASE_H__
#define __OBJECTBASE_H__

#include "model/types.h"
#include "utils/wxfbdefs.h"

#include <component.h>
#include <ticpp.h>

#include <iostream>
#include <list>

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
	void AddOption( wxString option, wxString description = wxString() ) { m_options[option] = description; }

	/**
	 * @todo Description needed.
	 * 
	 * @return 
	 */
	unsigned int GetOptionCount() { return ( unsigned int )m_options.size(); }

	/** @todo Description needed. */
	const std::map< wxString, wxString >& GetOptions() { return m_options; }
};

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
	/**  @todo Description needed. */
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
	 * @param customEditor 	Custom editor.  
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
	EventInfo(  const wxString &name,
				const wxString &eventClass,
				const wxString &defValue,
				const wxString &description );

	wxString GetName()           { return m_name; } 		/**< @todo Description needed. */
	wxString GetEventClassName() { return m_eventClass; } 	/**< @todo Description needed. */
	wxString GetDefaultValue()   { return m_defaultValue; } /**< @todo Description needed. */
	wxString GetDescription()    { return m_description; } 	/**< @todo Description needed. */
};

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
	wxString 		m_value;  /**< Value. */

public:
	/**
	 * Constructor.
	 * @todo Description needed.
	 * @param info 	
	 * @param obj 	
	 */
	Property( PPropertyInfo info, PObjectBase obj = PObjectBase() )
	{
		m_object 	= obj;
		m_info 		= info;
	}

	/** @todo Description needed. */
	PObjectBase GetObject() 			{ return m_object.lock(); }

	/** @todo Description needed. */
	wxString GetName() 					{ return m_info->GetName(); }

	/** @todo Description needed. */
	wxString GetValue() 				{ return m_value; }

	/** @todo Description needed. */
	void SetValue( wxString& val ) 		{ m_value = val; }

	/** @todo Description needed. */
	void SetValue( const wxChar* val ) 	{ m_value = val; }

	/** @todo Description needed. */
	PPropertyInfo GetPropertyInfo() { return m_info; }

	/** @todo Description needed. */
	PropertyType  GetType()         { return m_info->GetType();  }

	bool IsDefaultValue(); 	/**< @todo Description needed. */
	bool IsNull();			/**< @todo Description needed. */
	void SetDefaultValue(); /**< @todo Description needed. */

	/**
	 * @todo Description needed.
	 * @param value 
	 */
	void ChangeDefaultValue( const wxString& value )
	{
		m_info->m_def_value = value;
	}

	void SetValue( const wxFontContainer &font ); 				/**< @todo Description needed. */
	void SetValue( const wxColour &colour ); 					/**< @todo Description needed. */
	void SetValue( const wxString &str, bool format = false ); 	/**< @todo Description needed. */
	void SetValue( const wxPoint &point ); 						/**< @todo Description needed. */
	void SetValue( const wxSize &size ); 						/**< @todo Description needed. */
	void SetValue( const int integer ); 						/**< @todo Description needed. */
//	void SetValue( const wxAlignment alignment ); 				/**< @todo */
	void SetValue( const double val ); 							/**< @todo Description needed. */

	wxFontContainer GetValueAsFont(); 							/**< @todo Description needed. */
	wxColour 		GetValueAsColour(); 						/**< @todo Description needed. */
	wxPoint  		GetValueAsPoint(); 							/**< @todo Description needed. */
	wxSize   		GetValueAsSize(); 							/**< @todo Description needed. */
	int      		GetValueAsInteger(); 						/**< @todo Description needed. */
//	wxAlignment 	GetValueAsAlignment(); 						/**< @todo */
	wxString 		GetValueAsString(); 						/**< @todo Description needed. */
	wxBitmap 		GetValueAsBitmap(); 						/**< @todo Description needed. */
	/** @todo Description needed. */
	wxString 		GetValueAsText(); // Replace ('\n',...) in ("\\n",...)

	wxArrayString 	GetValueAsArrayString(); 					/**< @todo Description needed. */
	double 			GetValueAsFloat(); 							/**< @todo Description needed. */

	/**
	 * @todo Description needed.
	 * @param children 
	 */
	void 			SplitParentProperty( std::map< wxString, wxString >* children );

	/**
	 * @todo Description needed.
	 * @param childName
	 */
	wxString 		GetChildFromParent( const wxString& childName );
};

/**
 * @class Event
 * @brief 
 * @todo Description needed.
 */
class Event
{
private:
	PEventInfo  	m_info;   /**< Pointer to its descriptor. */
	WPObjectBase 	m_object; /**< Pointer to the owner object. */
	wxString 		m_value;  /**< Handler function name */

public:
	/**
	 * Constructor.
	 * @param info  
	 * @param obj 	
	 * @todo Description needed.
	 */
	Event (	PEventInfo info, PObjectBase obj ) : m_info(info), m_object( obj ) {}

	/**
	 * @todo Description needed.
	 * @param value 
	 */
	void 		SetValue( const wxString &value ) 	{ m_value = value; }
	wxString 	GetValue()                  		{ return m_value; } 			/**< @todo Description needed. */
	wxString 	GetName()                   		{ return m_info->GetName(); } 	/**< @todo Description needed. */
	PObjectBase GetObject()              			{ return m_object.lock(); } 	/**< @todo Description needed. */
	PEventInfo 	GetEventInfo()            			{ return m_info; } 				/**< @todo Description needed. */
};

/**
 * @class PropertyCategory
 * @brief 
 * @todo Description needed.
 */
class PropertyCategory
{
private:
	wxString 							m_name; 		/**< @todo Description needed. */
	std::vector< wxString > 			m_properties; 	/**< @todo Description needed. */
	std::vector< wxString > 			m_events; 		/**< @todo Description needed. */
	std::vector< PPropertyCategory > 	m_categories; 	/**< @todo Description needed. */

public:
	/**
	 * Constructor.
	 * @param name 
	 * @todo Description needed.
	 */
	PropertyCategory( wxString name ) : m_name( name ) {}

	/**
	 * @todo Description needed.
	 * @param name	
	 */
	void AddProperty( wxString name )				{ m_properties.push_back( name ); }

	/**
	 * @todo Description needed.
	 * @param name	
	 */
	void AddEvent( wxString name )					{ m_events.push_back( name ); }

	/**
	 * @todo Description needed.
	 * @param category 	
	 */
	void AddCategory( PPropertyCategory category )	{ m_categories.push_back( category ); }

	/**
	 * @todo Description needed.
	 */
	wxString GetName()								{ return m_name; }

	/**
	 * @todo Description needed.
	 * @param index 
	 */
	wxString GetPropertyName( size_t index )
	{
		if ( index < m_properties.size() )
			return m_properties[ index ];
		else
			return wxEmptyString;
	}

	/**
	 * @todo Description needed.
	 * @param index 
	 */
	wxString GetEventName( size_t index )
	{
		if ( index < m_events.size() )
			return m_events[ index ];
		else
			return wxEmptyString;
	}

	/**
	 * @todo Description needed.
	 * @param index 
	 */
	PPropertyCategory GetCategory( size_t index )
	{
		if ( index < m_categories.size() )
			return m_categories[ index ];
		else
			return PPropertyCategory();
	}

	size_t GetPropertyCount() 	{ return m_properties.size(); } /**< @todo Description needed. */
	size_t GetEventCount() 		{ return m_events.size(); } 	/**< @todo Description needed. */
	size_t GetCategoryCount() 	{ return m_categories.size(); } /**< @todo Description needed. */
};

namespace ticpp
{
	class Document;
	class Element;
}

class ObjectBase : public IObject, public boost::enable_shared_from_this< ObjectBase >
{
	friend class wxFBDataObject;

private:
	wxString     		m_class;  		/**< Class name. */
	wxString     		m_type;   		/**< Object type. */
	WPObjectBase 		m_parent; 		/**< Weak pointer, no reference loops please! */
	ObjectBaseVector 	m_children; 	/**< @todo Description needed. */
	PropertyMap      	m_properties; 	/**< @todo Description needed. */
	EventMap         	m_events; 		/**< @todo Description needed. */
	PObjectInfo      	m_info; 		/**< @todo Description needed. */
	bool 				m_expanded; 	/**< Is expanded in the object tree, allows for saving to file */

protected:
	// Utilites for implementing the tree
	static const int 	INDENT;  						/**< Size of indent. */
	wxString 			GetIndentString( int indent ); 	/**< Gets the string with the indentation. */

	/** @todo Description needed. */
	ObjectBaseVector& GetChildren()     { return m_children; };

	/** @todo Description needed. */
	PropertyMap&      GetProperties()   { return m_properties; };

	/** Create an object element */
	void SerializeObject( ticpp::Element* serializedElement );

	/** Get "this" pointer */
	PObjectBase GetThis() { return shared_from_this(); }

public:
	/**
	 * Constructor.
	 * @param class_name Class name.
	 */
	ObjectBase ( wxString class_name );

	/** Virtual destructor. */
	virtual ~ObjectBase();

	/** Sets whether the object is expanded in the object tree or not. */
	void SetExpanded( bool expanded ){ m_expanded = expanded; }

	/** Gets whether the object is expanded in the object tree or not. */
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
	 * @note SetProperty method doesn't exists, since modification
	 *       is done through the reference.
	 */
	PProperty GetProperty( wxString name );

	/**
	 * @todo Description needed.
	 * @param name 
	 */
	PEvent GetEvent( wxString name );

	/**
	 * Adds a property to the object.
	 *
	 * This method will be used in the descriptors registry to create the
	 * object instance.
	 * The objects are always created through the descriptors registry.
	 */
	void AddProperty( PProperty value );

	/**
	 * @todo Description needed.
	 * @param event 
	 */
	void AddEvent( PEvent event );

	/** Gets the number of object properties.
	 * @note ObjectBase::GetPropertyCount() != ObjectInfo::GetPropertyCount()
	 *
	 * In the first case it will return the total number of properties of the object.
	 * In the second case only return the number of properties defined for that class.
	 */
	unsigned int GetPropertyCount() { return ( unsigned int )m_properties.size(); }

	/** Gets the number of object events. */
	unsigned int GetEventCount()    { return m_events.size(); }

	/**
	 * Gets an object property.
	 * @todo This function should throw an exception if passed property is not found
	 * 		and simplifies the code by not having to do many checks.
	 * 		For example, the code without exceptions would be something like:
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
	 *   // Error handling here.
	 * }
	 *
	 * @endcode
	 *
	 * With exceptions:
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
	 *   // Error handling here.
	 * }
	 *
	 * @endcode
	 */
	PProperty GetProperty ( unsigned int idx ); // throws ...;

	/**
	 * @todo Description needed.
	 * @param idx 
	 */
	PEvent GetEvent ( unsigned int idx ); // throws ...;

	/**
	 * Returns the first ancestor whose type matches the passed parameter.
	 *
	 * It will be useful to find the parent widget.
	 */
	PObjectBase FindNearAncestor( wxString type );

	/**
	 * @todo Description needed.
	 * @param type 
	 */
	PObjectBase FindNearAncestorByBaseClass( wxString type );

	/** @todo Description needed. */
	PObjectBase FindParentForm();

	/** Gets the xml document from the tree taking current node as root node. */
	void Serialize( ticpp::Document* serializedDocument );

	/**
	 * Adds a child to the object.
	 * This function is virtual, because it can change behavior
	 * depending on the type of object.
	 *
	 * @return true if the child was added successfully and false otherwise.
	 */
	virtual bool AddChild    ( PObjectBase );

	/** @todo Description needed. */
	virtual bool AddChild    ( unsigned int idx, PObjectBase obj );

	/** Returns the position of the child or GetChildCount() in if not found. */
	unsigned int GetChildPosition( PObjectBase obj );

	/**
	 * Changes child position.
	 * @param obj Object.
	 * @param pos Position.
	 * @return @true if success, @false otherwise.
	 */
	bool ChangeChildPosition( PObjectBase obj, unsigned int pos );

	/** Returns the position among its siblings */
/*  unsigned int GetPosition();
	bool ChangePosition( unsigned int pos );*/

	/** Removes a child of the object. */
	void RemoveChild( PObjectBase obj );

	/** @todo Description needed. */
	void RemoveChild( unsigned int idx );

	/** Removes all object's children. */
	void RemoveAllChildren(){ m_children.clear(); }

	/** Gets a child of the object. */
	PObjectBase GetChild( unsigned int idx );

	/** Gets the number of children of the object. */
	unsigned int  GetChildCount() { return ( unsigned int )m_children.size(); }

	/**
	 * Checks if passed object type is valid as a child of the object.
	 * This routine is important because it defines the restrictions of location.
	 */
	//bool ChildTypeOk( wxString type );
	bool ChildTypeOk( PObjectType type );

	/** @todo A single function that returns object type like GetObjectType(). */
	bool IsContainer() 	{ return ( GetObjectTypeName() == "container" ); }
	/** @todo A single function that returns object type like GetObjectType(). */
	bool IsWizardPage() { return ( GetObjectTypeName() == "wizardpage" ); }

	/** @todo Description needed. */
	PObjectBase GetLayout();

	/**
	 * Returns the type of object.
	 *
	 * Must be redefined in every derived class.
	 */
	wxString GetObjectTypeName() { return m_type; }

	/**
	 * Sets the type of object.
	 *
	 * @param type Object type.
	 */
	void SetObjectTypeName( wxString type ) { m_type = type; }

	/** Returns the object descriptor. */
	PObjectInfo GetObjectInfo() { return m_info; };

	/** @todo Description needed. */
	void SetObjectInfo( PObjectInfo info ) { m_info = info; };

	/** Returns the depth of the object in the tree. */
	int Deep();

	/** Prints the tree in a stream. */
	//virtual void PrintOut(ostream &s, int indent);

	/** Insertion operator overload. */
	friend std::ostream& operator << (std::ostream &s, PObjectBase obj);

	// IObject interface implementation for use within plugins.

	bool 			IsNull 						( const wxString& pname ); /**< @todo Description needed. */
	int      		GetPropertyAsInteger 		( const wxString& pname ); /**< @todo Description needed. */
//	wxAlignment 	GetPropertyAsAlignment 		( const wxString& pname ); /**< @todo */
	wxFontContainer GetPropertyAsFont    		( const wxString& pname ); /**< @todo Description needed. */
	wxColour 		GetPropertyAsColour  		( const wxString& pname ); /**< @todo Description needed. */
	wxString 		GetPropertyAsString  		( const wxString& pname ); /**< @todo Description needed. */
	wxPoint  		GetPropertyAsPoint   		( const wxString& pname ); /**< @todo Description needed. */
	wxSize   		GetPropertyAsSize    		( const wxString& pname ); /**< @todo Description needed. */
	wxBitmap 		GetPropertyAsBitmap  		( const wxString& pname ); /**< @todo Description needed. */
	double	 		GetPropertyAsFloat	  		( const wxString& pname ); /**< @todo Description needed. */
	wxArrayInt    	GetPropertyAsArrayInt 		( const wxString& pname ); /**< @todo Description needed. */
	wxArrayString 	GetPropertyAsArrayString  	( const wxString& pname ); /**< @todo Description needed. */

	/**
	 * @todo Description needed.
	 * @param parentName  	
	 * @param childName 	
	 */
	wxString 		GetChildFromParentProperty( const wxString& parentName, const wxString& childName );
};

/**
 * @class CodeInfo
 * Class that stores a set of code templates.
 */
class CodeInfo
{
private:
	/** @todo Description needed. */
	typedef std::map< wxString, wxString > TemplateMap;

	/** @todo Description needed. */
	TemplateMap m_templates;

public:
	/** @todo Description needed. */
	wxString 	GetTemplate( wxString name );

	/** @todo Description needed. */
	void 		AddTemplate( wxString name, wxString _template );

	/** @todo Description needed. */
	void 		Merge( PCodeInfo merger );
};

/**
 * @class ObjectInfo
 * Object or metaobject informations.
 */
class ObjectInfo
{
public:
	/**
	 * Constructor.
	 * @param class_name Class name.
	 * @param type		Object type.
	 * @param package 	Weak pointer to ObjectPackage.
	 * @param startGroup Sets if it is a starting group object: if @true a toolbar separator will be placed in palette toolbar.
	 */
	ObjectInfo(wxString class_name, PObjectType type, WPObjectPackage package, bool startGroup = false );

	/** Virtual destructor. */
	virtual ~ObjectInfo() {};

	/** @todo Description needed. */
	PPropertyCategory GetCategory(){ return m_category; }

	/** @todo Description needed.
	 * @note ObjectBase::GetPropertyCount() != ObjectInfo::GetPropertyCount()
	 *
	 * In the first case it will return the total number of properties of the object.
	 * In the second case only return the number of properties defined for that class.
	 */
	unsigned int GetPropertyCount() { return ( unsigned int )m_properties.size(); }

	/** @todo Description needed. */
	unsigned int GetEventCount()    { return (unsigned int)m_events.size();     }

	/**
	 * Gets the property descriptor.
	 * @param name Descriptor name.
	 */
	PPropertyInfo GetPropertyInfo( wxString name );

	/**
	 * Gets the property descriptor.
	 * @param idx Descriptor index.
	 */
	PPropertyInfo GetPropertyInfo( unsigned int idx );

	/** @todo Description needed. */
	PEventInfo GetEventInfo( wxString name );

	/**
	 * @todo Description needed.
	 * @param idx 	
	 */
	PEventInfo GetEventInfo( unsigned int idx );

	/** Adds a property descriptor to the object descriptor. */
	void AddPropertyInfo( PPropertyInfo pinfo );

	/** Adds a event descriptor. */
	void AddEventInfo( PEventInfo evtInfo );

	/**
	* Add a default value for an inherited property.
	* @param baseIndex 		Index of base class returned from AddBaseClass.
	* @param propertyName 	Name of base class to assign a default value to.
	* @param defaultValue 	Default value of the inherited property.
	*/
	void AddBaseClassDefaultPropertyValue( size_t baseIndex, const wxString& propertyName, const wxString& defaultValue );

	/**
	* Get a default value for an inherited property.
	* @param baseIndex 		Index of base class in the base class vector
	* @param propertyName 	Name of the property to get the default value for
	* @return The default value for the property.
	*/
	wxString GetBaseClassDefaultPropertyValue( size_t baseIndex, const wxString& propertyName );

	/**
	 * @todo Translation needed.
	 * Devuelve el tipo de objeto, será util para que el constructor de objetos
	 * sepa la clase derivada de ObjectBase que ha de crear a partir del
	 * descriptor.
	 */
	wxString GetObjectTypeName() { return m_type->GetName();   }

	/** @todo Description needed. */
	PObjectType GetObjectType() { return m_type; }

	/** @todo Description needed. */
	wxString GetClassName () { return m_class;  }

	/** Prints the descriptor in a stream. */
	//virtual void PrintOut(ostream &s, int indent);

	/** Insertion operator overload. */
	friend std::ostream& operator << ( std::ostream &s, PObjectInfo obj );

	/** Will be useful to generate the name of the object. */
	unsigned int GetInstanceCount() { return m_numIns; }

	/** @todo Description needed. */
	void IncrementInstanceCount()   { m_numIns++; }

	/** @todo Description needed. */
	void ResetInstanceCount() 		{ m_numIns = 0; }

	/** Adds information about an object to all base classes. */
	size_t AddBaseClass( PObjectInfo base )
	{
		m_base.push_back(base);
		return m_base.size() - 1;
	}

	/** Check if the type is derived from the given parameter. */
	bool IsSubclassOf( wxString classname );

	/** @todo Description needed. */
	PObjectInfo GetBaseClass( unsigned int idx );

	/** @todo Description needed. */
	unsigned int GetBaseClassCount();

	/** @todo Description needed. */
	void SetIconFile( wxBitmap icon ) { m_icon = icon; };

	/** @todo Description needed. */
	wxBitmap GetIconFile() { return m_icon; }

	/** @todo Description needed. */
	void SetSmallIconFile( wxBitmap icon ) { m_smallIcon = icon; };

	/** @todo Description needed. */
	wxBitmap GetSmallIconFile() { return m_smallIcon; }

	/** @todo Description needed. */
	void AddCodeInfo( wxString lang, PCodeInfo codeinfo );

	/** @todo Description needed. */
	PCodeInfo GetCodeInfo( wxString lang );

	/** @return Shared pointer to object package */
	PObjectPackage GetPackage();

	/** @return @true if a component is a staring group component, @false otherwise. */
	bool IsStartOfGroup() { return m_startGroup; }

	/** Assigns a component to the class. */
	void SetComponent( IComponent *c ) 	{ m_component = c; };

	/** Gets a component from the class. */
	IComponent* GetComponent() 			{ return m_component; };

private:
	wxString 			m_class; 	/**< Class name (object type). */
	PObjectType 		m_type;     /**< Object type. */
	WPObjectPackage 	m_package; 	/**< Package that the object comes from. */
	PPropertyCategory 	m_category; /**< Category. */

	wxBitmap 	m_icon; 		/**< @todo Description needed. */
	wxBitmap 	m_smallIcon; 	/**< The icon for the property grid toolbar. */
	bool 		m_startGroup; 	/**< Place a separator in the palette toolbar just before this widget. */

	std::map< wxString, PCodeInfo > 	m_codeTemp;  	/**< Code templates K=language_name T=PCodeInfo. */
	unsigned int 						m_numIns;  		/**< Number of instances of object. */
	std::map< wxString, PPropertyInfo > m_properties; 	/**< Properties. */
	std::map< wxString, PEventInfo >    m_events; 		/**< Events. */
	std::vector< PObjectInfo > 			m_base; 		/**< Base classes. */

	/** @todo Description needed. */
	std::map< size_t, std::map< wxString, wxString > > m_baseClassDefaultPropertyValues;
	IComponent* m_component; /**< Component associated with the class designer objects. */
};

#endif //__OBJECTBASE_H__
