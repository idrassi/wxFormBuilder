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

#ifndef __OBJ_DATABASE__
#define __OBJ_DATABASE__

#include "model/types.h"
#include "utils/wxfbdefs.h"

#include <set>
#include <map>

#include <wx/dynlib.h>

class ObjectDatabase;
class ObjectTypeDictionary;
class PropertyCategory;

typedef boost::shared_ptr< ObjectDatabase > PObjectDatabase;

namespace ticpp
{
	class Element;
}

/**
 * @class ObjectPackage
 * @brief Package object classes.
 * 
 * Identify a group in the component palette.
 */
class ObjectPackage
{
private:
	wxString m_name; /**< Package name. */
	wxString m_desc; /**< Brief package description */
	wxBitmap m_icon; /**< The icon for the notebook page */

	/** Objects that are contained in the package */
	std::vector< PObjectInfo > m_objs;

public:
	/** Constructor.
	 *
	 * @param name Package name.
	 * @param desc Brief package description.
	 * @param icon The icon for the notebook page.
	 */
	ObjectPackage( wxString name, wxString desc, wxBitmap icon );

	/** Adds object's informations in the package.
	 * 
	 * @param obj Object to add.
	 */
	void Add( PObjectInfo obj ) { m_objs.push_back( obj ); };

	/** Gets the package name. */
	wxString GetPackageName() { return m_name; }

	/** Gets the text describing the package. */
	wxString GetPackageDescription() { return m_desc; }

	/** Gets the package icon. */
	wxBitmap GetPackageIcon() { return m_icon; }

	/** Gets the number of objects included in the package. */
	unsigned int GetObjectCount() { return ( unsigned int )m_objs.size(); }

	/** Gets the information about an object included in the package.
	 *
	 * @param idx Object index.
	 */
	PObjectInfo GetObjectInfo( unsigned int idx );

	/**
	 * If two XML files specify the same package name, then they merged to one package with this.
	 * This allows one package to be split across multiple XML files.
	 *
	 * @param package Package where to add data into.
	 */
	void AppendPackage( PObjectPackage package );
};

class IComponentLibrary;

/**
 * @class ObjectDatabase
 * @brief Object's database
 * 
 * Imported object informations from XML files will be stored in this class.
 */
class ObjectDatabase
{
public:
	/**
	 * Checks if a given object type owns c++ properties.
	 *
	 * @param type Object type.
	 * @return True if a given object type owns c++ properties, false otherwise
	 */
	static bool HasCppProperties( wxString type );

private:
	/** @todo Description needed. */
	typedef std::vector<PObjectPackage> PackageVector;

	/** Map the property type string to the property type number */
	typedef std::map< wxString, PropertyType > PTMap;

	/** @todo Description needed. */
	typedef std::map< wxString, PObjectType > ObjectTypeMap;

	/** @todo Description needed. */
#ifdef __WXMAC__
	/** @note std::vector< wxDynamicLibrary * > on other platforms */
	typedef std::vector< void * > LibraryVector;
#else
	/** @note std::vector< void * > on wxMAC */
	typedef std::vector< wxDynamicLibrary * > LibraryVector;
#endif

	/** @todo Description needed. */
	typedef void ( *PFFreeComponentLibrary )( IComponentLibrary* lib );

	/** @todo Description needed. */
	typedef std::map< PFFreeComponentLibrary, IComponentLibrary * > ComponentLibraryMap;

	/** @todo Description needed. */
	typedef std::set<wxString> MacroSet;

	/** @todo Description needed. */
	typedef std::map< wxString, PCodeInfo > LangTemplateMap;

	/** @todo Description needed. */
	typedef std::map< PropertyType, LangTemplateMap > PTLangTemplateMap;

	wxString 							m_xmlPath; 			/**< XML file path. */
	wxString 							m_iconPath; 		/**< Icon file path. */
	wxString 							m_pluginPath; 		/**< Plugin library file path. */
	std::map< wxString, PObjectInfo > 	m_objs; 			/**< @todo Description needed. */
	PackageVector 						m_pkgs; 			/**< @todo Description needed. */
	PTMap 								m_propTypes; 		/**< @todo Description needed. */
	LibraryVector 						m_libs; 			/**< @todo Description needed. */
	ComponentLibraryMap 				m_componentLibs; 	/**< @todo Description needed. */
	ObjectTypeMap 						m_types; 			/**< Registered object types */

	/**
	 * @todo Translation needed.
	 * 
	 * Para comprobar que no se nos han quedado macros sin añadir en las
	 * liberias de componentes, vamos a crear un conjunto con las macros
	 * definidas en los XML, y al importar las librerías vamos a ir eliminando
	 * dichas macros del conjunto, quedando al final las macros que faltan
	 * por registrar en la librería.
	 */
	MacroSet 							m_macroSet;

	/** Used so libraries are only imported once, even if multiple libraries use them. */
	std::set< wxString > 				m_importedLibraries;

	/** @todo Description needed. */
	PTLangTemplateMap 					m_propertyTypeTemplates;

	/** Initialize the property type map. */
	void InitPropertyTypes();

	/**
	 * Loads code generation templates from an XML file.
	 * 
	 * @param file XML file name.
	 */
	void LoadCodeGen( const wxString& file );

	/**
	 * Loads objects and their properties (except inherited ones) from a package.
	 * 
	 * @param file 		Package file name.
	 * @param iconPath 	Path to icon files included in the package
	 */
	PObjectPackage LoadPackage( const wxString& file, const wxString& iconPath = wxEmptyString );

	/**
	 * @todo Description needed.
	 * 
	 * @param elem_obj  
	 * @param obj_info  
	 * @param category  
	 * @param types 	
	 */
	void ParseProperties( ticpp::Element* elem_obj, PObjectInfo obj_info, PPropertyCategory category, std::set< PropertyType >* types );

	/**
	 * @todo Description needed.
	 * 
	 * @param elem_obj 
	 * @param obj_info 
	 * @param category 
	 */
	void ParseEvents    ( ticpp::Element* elem_obj, PObjectInfo obj_info, PPropertyCategory category );

	/**
	 * Associates an imported component library to a specified class.
	 *
	 * @param libfile Component library file name.
	 * @param manager Manager.
	 *
	 * @throw wxFBException if the library could not be imported.
	 */
	void ImportComponentLibrary( wxString libfile, PwxFBManager manager );

	/**
	 * Includes information inherited from the objects of a package.
	 * In a second step, it configures each package with its base objects.
	 * 
	 * @param file  	Package file name.
	 * @param path 		Package file path.
	 * @param manager 	Manager.
	 */
	void SetupPackage( const wxString& file, const wxString& path, PwxFBManager manager );

	/**
	 * Determines whether the object type must be included in the component palette.
	 *
	 * @param type Object type to check.
	 */
	bool ShowInPalette( wxString type );

	/// Conversion routines
	/**
	 * @todo Description needed.
	 * 
	 * @param str 
	 */
	PropertyType ParsePropertyType ( wxString str );

	/**
	 * @todo Description needed.
	 * 
	 * @param str 
	 */
	wxString ParseObjectType ( wxString str );

	/**
	 * @todo Description needed.
	 * 
	 * @param name 
	 */
	PObjectType GetObjectType( wxString name );

	/**
	 * @todo Description needed.
	 * 
	 * @param parent 	
	 * @param type 		
	 */
	int CountChildrenWithSameType( PObjectBase parent, PObjectType type );

	/**
	 * @todo Description needed.
	 * 
	 * @param obj 
	 */
	void SetDefaultLayoutProperties( PObjectBase obj );

public:
	/** Constructor. */
	ObjectDatabase();

	/** Destructor. */
	~ObjectDatabase();

	/**
	 * @todo The inheritance of property must be recursive.
	 * @todo Description needed.
	 */
	PObjectBase NewObject( PObjectInfo obj_info );

	/**
	 * Gets the information about an object from class name.
	 *
	 * @param class_name Object info class name.
	 */
	PObjectInfo GetObjectInfo( wxString class_name );

	/**
	 * Sets the XML file path where are stored object definitions.
	 *
	 * @param path Path to XML file.
	 */
	void SetXmlPath( const wxString& path ) { m_xmlPath = path; }

	/**
	 * Sets the path where the icons associated to objects are stored.
	 *
	 * @param path Path to icon files directory.
	 */
	void SetIconPath( const wxString& path )  { m_iconPath = path; }

	/**
	 * Sets the plugin path.
	 *
	 * @param path Plugin path.
	 */
	void SetPluginPath( const wxString& path ) { m_pluginPath = path; }

	/** Gets the XML file path where are stored object definitions. */
	wxString GetXmlPath() 		{ return m_xmlPath; 	}

	/** Gets the path where the icons associated to objects are stored. */
	wxString GetIconPath()		{ return m_iconPath; 	}

	/** Gets the plugin path. */
	wxString GetPluginPath() 	{ return m_pluginPath; 	}

	/** Loads object types definitions. */
	bool LoadObjectTypes();

	/**
	 * Find and load plugins from the plugins directory.
	 *
	 * @param manager Manager.
	 */
	void LoadPlugins( PwxFBManager manager );

	/**
	 * Create an instance of classname as a child of the parent.
	 *
	 * The function performs type checking to create the object:
	 * 
	 * - Check if the type is a valid child-type of "parent". 
	 *    Also check that the number of children of the same type does not exceed the maximum.
	 * 
	 * - If the type is not an allowded child-type for the "parent" it will be created as child
	 *    of a child item with the item flag "1".
	 * 
	 * @note You may want to create the object method without linking it to the tree,
	 * 		to facilitate the undo-redo.
	 * 
	 * @param class_name 	Class name.
	 * @param parent 		Parent object.
	 */
	PObjectBase CreateObject( std::string class_name, PObjectBase parent = PObjectBase() );

	/**
	 * Creates an object from an XML object; this method is used to load a saved project.
	 *
	 * @param obj 		XML object.
	 * @param parent 	Parent object.
	 */
	PObjectBase CreateObject( ticpp::Element* obj, PObjectBase parent = PObjectBase() );

	/**
	 * Creates an object as copy from another.
	 *
	 * @param obj Object to copy.
	 */
	PObjectBase CopyObject( PObjectBase obj );

	/**
	 * Gets an object's package.
	 *
	 * @param idx Package index.
	 */
	PObjectPackage GetPackage( unsigned int idx );

	/** Returns registered packages count. */
	unsigned int GetPackageCount() { return ( unsigned int )m_pkgs.size(); }

	/**
	* Resets the counters associated to the object's name:
	* "name" is a special property, reserved for the name of the instanced object.
	* Each object class has an associated counter to avoid duplicate names during creation. 
	* (i.e. m_button1, m_button2 ...)
	*/
	void ResetObjectCounters();
};

#endif //__OBJ_DATABASE__
