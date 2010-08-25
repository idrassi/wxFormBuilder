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

// TODO: check comments translation

#include "objectbase.h"
#include "database.h"
#include "rad/appdata.h"
#include "rad/bitmaps.h"
#include "utils/debug.h"
#include "utils/stringutils.h"
#include "utils/typeconv.h"
#include "utils/wxfbexception.h"

#include <ticpp.h>

#include <wx/app.h>
#include <wx/config.h>
#include <wx/dir.h>
#include <wx/filename.h>
#include <wx/image.h>
#include <wx/stdpaths.h>
#include <wx/tokenzr.h>

//#define DEBUG_PRINT(x) cout << x

#define OBJINFO_TAG "objectinfo"
#define CODEGEN_TAG "codegen"
#define TEMPLATE_TAG "template"
#define NAME_TAG "name"
#define DESCRIPTION_TAG "help"
#define CUSTOM_EDITOR_TAG "editor"
#define PROPERTY_TAG "property"
#define CHILD_TAG "child"
#define EVENT_TAG "event"
#define EVENT_CLASS_TAG "class"
#define CATEGORY_TAG "category"
#define OBJECT_TAG "object"
#define CLASS_TAG "class"
#define PACKAGE_TAG "package"
#define PKGDESC_TAG "desc"
#define PRGLANG_TAG "language"
#define ICON_TAG "icon"
#define SMALL_ICON_TAG "smallIcon"
#define EXPANDED_TAG "expanded"

#ifdef __WXMAC__
	#include <dlfcn.h>
#endif

ObjectPackage::ObjectPackage( wxString name, wxString desc, wxBitmap icon )
{
	m_name = name;
	m_desc = desc;
	m_icon = icon;
}

PObjectInfo ObjectPackage::GetObjectInfo( unsigned int idx )
{
	assert ( idx < m_objs.size() );
	return m_objs[idx];
}

void ObjectPackage::AppendPackage( PObjectPackage package )
{
	m_objs.insert( m_objs.end(), package->m_objs.begin(), package->m_objs.end() );
}
///////////////////////////////////////////////////////////////////////////////

ObjectDatabase::ObjectDatabase()
{
//	InitObjectTypes();
//  InitWidgetTypes();
	InitPropertyTypes();
}

ObjectDatabase::~ObjectDatabase()
{
    for ( ComponentLibraryMap::iterator lib = m_componentLibs.begin(); lib != m_componentLibs.end(); ++lib )
    {
        ( *( lib->first ) )( lib->second );
    }

    for ( LibraryVector::iterator lib = m_libs.begin(); lib != m_libs.end(); ++lib )
    {
        #ifdef __WXFB_DEBUG__
			// Only unload in release - can't get a good stack trace if the library is unloaded
			#ifdef __WXMAC__
				dlclose( *lib );
			#else
				(*lib)->Detach();
			#endif
        #endif

		#ifndef __WXMAC__
			delete *lib;
		#endif
    }
}

PObjectInfo ObjectDatabase::GetObjectInfo(wxString class_name)
{
	PObjectInfo info;
	ObjectInfoMap::iterator it = m_objs.find( class_name );

	if ( it != m_objs.end() )
	{
		info = it->second;
	}
	return info;
}

PObjectPackage ObjectDatabase::GetPackage(unsigned int idx)
{
	assert ( idx < m_pkgs.size() );

	return m_pkgs[idx];
}

/**
* @todo The inheritance of property must be recursive.
*/

PObjectBase ObjectDatabase::NewObject(PObjectInfo obj_info)
{
	PObjectBase object;

	// Llagados aquí el objeto se crea seguro...
	// At this point the object will be created (safe?)
	object = PObjectBase( new ObjectBase( obj_info->GetClassName() ) );
	object->SetObjectTypeName( obj_info->GetObjectTypeName() ); // *FIXME*

	object->SetObjectInfo( obj_info );

	PPropertyInfo prop_info;
	PEventInfo    event_info;
	PObjectInfo   class_info = obj_info;

	unsigned int base = 0;

	while ( class_info )
	{
		unsigned int i;
		for ( i = 0; i < class_info->GetPropertyCount(); i++ )
		{
			prop_info = class_info->GetPropertyInfo(i);

			PProperty property( new Property( prop_info, object ) );

			// Set the default value, either from the property info, or an override from this class
			wxString defaultValue = prop_info->GetDefaultValue();
			if ( base > 0 )
			{
				wxString defaultValueTemp = obj_info->GetBaseClassDefaultPropertyValue( base - 1, prop_info->GetName() );
				if ( !defaultValueTemp.empty() )
				{
					defaultValue = defaultValueTemp;
				}
			}
			property->SetValue( defaultValue );
			// Las propiedades están implementadas con una estructura "map",
			// ello implica que no habrá propiedades duplicadas.
			// En otro caso habrá que asegurarse de que dicha propiedad
			// no existe.
			// Otra cosa importante, es que el orden en que se insertan
			// las propiedades, de abajo-arriba, esto permite que se pueda redefir
			// alguna propiedad.

			// Properties are implemented with a "map" structure,
			// this means no duplicate properties.
			// In another case we must ensure that such property
			// doesn't exists.
			// Another important thing is the order in which those are inserted,
			// from bottom to top (?), this means that we can redefine
			// some property.
			object->AddProperty( property );
		}
		for ( i=0; i < class_info->GetEventCount(); i++ )
		{
			event_info = class_info->GetEventInfo( i );
			PEvent event( new Event( event_info, object ) );
			// Notice that for event there isn't a default value on its creation
			// because there is not handler at the moment
			object->AddEvent( event );
		}
		class_info = ( base < obj_info->GetBaseClassCount() ?
			obj_info->GetBaseClass( base++ ) : PObjectInfo() );
	}
	// If the object has the name property (reserved for the object name)
	// add a counter to prevent repeated names.

	obj_info->IncrementInstanceCount();

	unsigned int ins = obj_info->GetInstanceCount();
	PProperty pname = object->GetProperty( NAME_TAG );
	if ( pname )
		pname->SetValue( pname->GetValue() + StringUtils::IntToStr( ins ) );

	return object;
}

int ObjectDatabase::CountChildrenWithSameType( PObjectBase parent, PObjectType type )
{
	unsigned int count = 0;
	unsigned int numChildren = parent->GetChildCount();
	for ( unsigned int i=0; i < numChildren ; i++ )
	{
		if ( type == parent->GetChild( i )->GetObjectInfo()->GetObjectType() )
			count++;
	}
	return count;
}

/**
* Create an instance of classname as a child of the parent.
*
* The function performs type checking to create the object:
* - Check if the type is a valid child-type of "parent". 
*    Also check that the number of children of the same type does not exceed the maximum.
* - If the type is not an allowded child-type for the "parent" it will be created as child
*    of a child item with the item flag "1".
* 
* Note: you may want to create the object method without linking it to the tree,
*       to facilitate the undo-redo.
*/

PObjectBase ObjectDatabase::CreateObject( std::string classname, PObjectBase parent )
{
	PObjectBase object;
	PObjectInfo objInfo = GetObjectInfo( _WXSTR( classname ) );

	if ( !objInfo )
	{
		THROW_WXFBEX( _("Unknown Object Type: ") << _WXSTR( classname )
			<< _("\nThe most likely causes are that this copy of wxFormBuilder is out of date, or that there is a plugin missing.\n")
			<< _("Please check at http://www.wxformbuilder.org\n") );
	}

	PObjectType objType = objInfo->GetObjectType();

	if ( parent )
	{
		// Type check
		PObjectType parentType = parent->GetObjectInfo()->GetObjectType();
		int max = parentType->FindChildType(objType);

		//AUI
		if( parentType->GetName() == "form" )
		{
			// Widgets and containers can be used without sizer only in AUI managed parents
			if( (!parent->GetPropertyAsInteger("aui_managed") && parent->GetObjectTypeName() != "toolbar" ) && ( objType->GetName() == "widget" || objType->GetName() == "container" ) ) max = 0;
			// Sizer cannot be used with AUI managed parent
			if( parent->GetPropertyAsInteger("aui_managed") && ( objType->GetName() == "sizer" ) ) max = 0;
		}

		// FIXME! Esto es un parche para evitar crear los tipos menubar,statusbar y
		// toolbar en un form que no sea wxFrame.
		// Hay que modificar el conjunto de tipos para permitir tener varios tipos
		// de forms (como childType de project), pero hay mucho código no válido
		// para forms que no sean de tipo "form". Dicho de otra manera, hay
		// código que dependen del nombre del tipo, cosa que hay que evitar.

		// FIXME! This is a workaround to avoid creating menubar, statusbar and
		// toolbar types in a form other than Frame (pseudo wxFrame).
		// Should be modified to allow all types have several form types
		// (like project childType), but there is invalid code
		// to forms not of type "form." In other words, there
		// code depends on type name, which must be avoided.
		if (parentType->GetName() 	== "form" 		&&
			parent->GetClassName() 	!= "Frame" 		&&
			(objType->GetName() 	== "statusbar" 	||
			objType->GetName() 		== "menubar" 	||
			objType->GetName() 		== "toolbar" 	))
			return PObjectBase(); // Invalid type

		if ( max != 0 ) // Valid type
		{
			bool create = true;

			// Check the number of instances
			if ( max > 0 && CountChildrenWithSameType( parent, objType ) >= max )
				create = false;

			if ( create )
				object = NewObject( objInfo );
		}
		else // max == 0
		{
			// Type is not valid, let's see if we can insert it as child of an "item"
			bool created = false;
			for ( unsigned int i=0; !created && i < parentType->GetChildTypeCount(); i++ )
			{
				PObjectType childType = parentType->GetChildType( i );
				int max = childType->FindChildType( objType );

				if ( childType->IsItem() && max != 0 )
				{
					max = parentType->FindChildType( childType );

					// If the type is an item and the type of object to create can
					// be the child of the type of item we will try to create the 
					// instance of the item to create the object as a child of this
					if ( max < 0 || CountChildrenWithSameType( parent, childType ) < max )
					{
						// Create the item with this parent
						PObjectBase item = NewObject( GetObjectInfo( childType->GetName() ) );

						//PObjectBase obj = CreateObject(classname,item);
						PObjectBase obj = NewObject( objInfo );

						// The following condition must be met as long as it should always
						// contain one item to another object
						if ( obj )
						{
							// Link item and obj
							item->AddChild( obj );
							obj->SetParent( item );

							// Sizeritem is a reserved object type,
							// Is more practical to assign default values based
							// on the type of object created
							if ( item->GetObjectInfo()->IsSubclassOf("sizeritembase") )
								SetDefaultLayoutProperties( item );

							object = item;
							created = true;
						}
						else
							wxLogError( _("Review your definitions file (objtypes.xml)") );
					}
				}
			}
		}
		///////////////////////////////////////////////////////////////////////
		// Note: provisionally linking the object to the parent. 
		//       This should be done outside in order to implement the Undo-Redo.
		///////////////////////////////////////////////////////////////////////
		//if ( object )
		//{
		//  parent->AddChild( object );
		//  object->SetParent( parent );
		//}
	}
	else // parent == NULL;
	{
		object = NewObject( objInfo );
	}
	return object;
}

PObjectBase ObjectDatabase::CopyObject( PObjectBase obj )
{
	assert( obj );

	PObjectInfo objInfo = obj->GetObjectInfo();

	PObjectBase copyObj = NewObject( objInfo ); // Create copy
	assert( copyObj );

	// Copy properties
	unsigned int i;
	unsigned int count = obj->GetPropertyCount();
	for ( i = 0; i < count; i++ )
	{
		PProperty objProp = obj->GetProperty( i );
		assert( objProp );

		PProperty copyProp = copyObj->GetProperty( objProp->GetName() );
		assert( copyProp );

		wxString propValue = objProp->GetValue();
		copyProp->SetValue( propValue );
	}

	// ...and the event handlers
	count = obj->GetEventCount();
	for ( i = 0; i < count; i++ )
	{
		PEvent event = obj->GetEvent( i );
		PEvent copyEvent = copyObj->GetEvent( event->GetName() );
		copyEvent->SetValue( event->GetValue() );
	}

	// Recursively create children
	count = obj->GetChildCount();
	for ( i = 0; i<count; i++ )
	{
		PObjectBase childCopy = CopyObject( obj->GetChild( i ) );
		copyObj->AddChild( childCopy );
		childCopy->SetParent( copyObj );
	}

	return copyObj;
}

void ObjectDatabase::SetDefaultLayoutProperties(PObjectBase sizeritem)
{
	if ( !sizeritem->GetObjectInfo()->IsSubclassOf("sizeritembase") )
	{
		Debug::Print( _("SetDefaultLayoutProperties expects a subclass of sizeritembase") );
		return;
	}

	PObjectBase child = sizeritem->GetChild(0);
	PObjectInfo childInfo = child->GetObjectInfo();
	wxString obj_type = child->GetObjectTypeName();

	PProperty proportion = sizeritem->GetProperty("proportion");

	if ( childInfo->IsSubclassOf("sizer") || obj_type == "splitter" || childInfo->GetClassName() == "spacer" )
	{
		if ( proportion )
			proportion->SetValue( wxString("1") );

		sizeritem->GetProperty("flag")->SetValue( wxString("wxEXPAND") );
	}
	else if ( childInfo->GetClassName() == "wxStaticLine" )
	{
		sizeritem->GetProperty("flag")->SetValue( wxString("wxEXPAND | wxALL") );
	}
	else if ( childInfo->GetClassName() == "wxToolBar" )
	{
		sizeritem->GetProperty("flag")->SetValue( wxString("wxEXPAND") );
	}
	else if ( obj_type == "widget" || obj_type == "statusbar" )
	{
		if ( proportion )
			proportion->SetValue( wxString("0") );

		sizeritem->GetProperty("flag")->SetValue( wxString("wxALL") );
	}
	else if (	obj_type == "expanded_widget" 	||
                obj_type == "dataview" 			||
                obj_type == "notebook"			||
				obj_type == "listbook"			||
				obj_type == "choicebook"		||
				obj_type == "treebook"			||
				obj_type == "toolbook"		    ||
				obj_type == "auinotebook"		||
				obj_type == "flatnotebook"		||
				obj_type == "treelistctrl"		||
				obj_type == "collapsiblepane" 	||
				obj_type == "container" )
	{
		if ( proportion )
			proportion->SetValue( wxString("1") );

		sizeritem->GetProperty("flag")->SetValue( wxString("wxEXPAND | wxALL") );
	}
}

void ObjectDatabase::ResetObjectCounters()
{
	ObjectInfoMap::iterator it;
	for ( it = m_objs.begin() ; it != m_objs.end() ; it++ )
		it->second->ResetInstanceCount();
}
///////////////////////////////////////////////////////////////////////

PObjectBase ObjectDatabase::CreateObject( ticpp::Element* xml_obj, PObjectBase parent )
{
	try
	{
		std::string class_name;
		xml_obj->GetAttribute( CLASS_TAG, &class_name, false );

		PObjectBase newobject = CreateObject( class_name, parent );

		// It is possible the CreateObject returns an "item" containing the object, e.g. SizerItem or SplitterItem
		// If that is the case, reassign "object" to the actual object
		PObjectBase object = newobject;
		if ( object && object->GetChildCount() > 0 )
			object = object->GetChild( 0 );

		if ( object )
		{
			// Get the state of expansion in the object tree
			bool expanded;
			xml_obj->GetAttributeOrDefault( EXPANDED_TAG, &expanded, true );
			object->SetExpanded( expanded );

			// Load the properties
			ticpp::Element* xml_prop = xml_obj->FirstChildElement( PROPERTY_TAG, false );
			while ( xml_prop )
			{
				std::string prop_name;
				xml_prop->GetAttribute( NAME_TAG, &prop_name, false );
				PProperty prop = object->GetProperty( _WXSTR( prop_name ) );

				if ( prop ) // Does the property exist
				{
					// Load the value
					prop->SetValue( _WXSTR( xml_prop->GetText( false ) ) );
				}
				else
				{
					std::string value = xml_prop->GetText( false );
					if ( !value.empty() )
					{
						wxLogError( _("The property named \"%s\" of class \"%s\" is not supported by this version of wxFormBuilder.\nIf your project file was just converted from an older version, then the conversion was not complete.\nOtherwise, this project is from a newer version of wxFormBuilder.\n\nThe property's value is: %s\nIf you save this project, YOU WILL LOSE DATA"),
									_WXSTR(prop_name).c_str(), _WXSTR(class_name).c_str(), _WXSTR(value).c_str() );
					}
				}
				xml_prop = xml_prop->NextSiblingElement( PROPERTY_TAG, false );
			}
			// Load the event handlers
			ticpp::Element* xml_event = xml_obj->FirstChildElement( EVENT_TAG, false );
			while ( xml_event )
			{
				std::string event_name;
				xml_event->GetAttribute( NAME_TAG, &event_name, false );
				PEvent event = object->GetEvent( _WXSTR( event_name ) );
				if ( event )
				{
					event->SetValue( _WXSTR( xml_event->GetText( false ) ) );
				}
				xml_event = xml_event->NextSiblingElement( EVENT_TAG, false );
			}
			if ( parent )
			{
				// Set up parent/child relationship
				parent->AddChild( newobject );
				newobject->SetParent( parent );
			}
			// Create the children
			ticpp::Element* child = xml_obj->FirstChildElement( OBJECT_TAG, false );
			while ( child )
			{
				CreateObject( child, object );
				child = child->NextSiblingElement( OBJECT_TAG, false );
			}
		}
		return newobject;
	}
	catch( ticpp::Exception& )
	{
		return PObjectBase();
	}
}
//////////////////////////////

bool IncludeInPalette( wxString type )
{
	return true;
}

void ObjectDatabase::LoadPlugins( PwxFBManager manager )
{
	// Load some default templates
	LoadCodeGen( m_xmlPath + "properties.cppcode" );
	LoadCodeGen( m_xmlPath + "properties.pythoncode" );
	LoadPackage( m_xmlPath + "default.xml", m_iconPath );
	LoadCodeGen( m_xmlPath + "default.cppcode" );
	LoadCodeGen( m_xmlPath + "default.pythoncode" );

	// Map to temporarily hold plugins.
	// Used to both set page order and to prevent two plugins with the same name.
	typedef std::map< wxString, PObjectPackage > PackageMap;
	PackageMap packages;

	// Open plugins directory for iteration
	if ( !wxDir::Exists( m_pluginPath ) )
		return;

	wxDir pluginsDir( m_pluginPath );
	if ( !pluginsDir.IsOpened() )
		return;

	// Iterate through plugin directories and load the package from the xml subdirectory
	wxString pluginDirName;
	bool moreDirectories = pluginsDir.GetFirst( &pluginDirName, wxEmptyString, wxDIR_DIRS | wxDIR_HIDDEN );
    while ( moreDirectories )
    {
    	// Iterate through .xml files in the xml directory
    	wxString nextPluginPath = m_pluginPath + pluginDirName;
    	wxString nextPluginXmlPath = nextPluginPath + wxFILE_SEP_PATH + "xml";
    	wxString nextPluginIconPath = nextPluginPath + wxFILE_SEP_PATH + "icons";
    	if ( wxDir::Exists( nextPluginPath ) )
    	{
    		if ( wxDir::Exists( nextPluginXmlPath ) )
    		{
				wxDir pluginXmlDir( nextPluginXmlPath );
				if ( pluginXmlDir.IsOpened() )
				{
					std::map< wxString, PObjectPackage > packagesToSetup;
					wxString packageXmlFile;
					bool moreXmlFiles = pluginXmlDir.GetFirst( &packageXmlFile, "*.xml", wxDIR_FILES | wxDIR_HIDDEN );
					while ( moreXmlFiles )
					{
						try
						{
							wxFileName nextXmlFile( nextPluginXmlPath + wxFILE_SEP_PATH + packageXmlFile );
							if ( !nextXmlFile.IsAbsolute() )
								nextXmlFile.MakeAbsolute();

							PObjectPackage package = LoadPackage( nextXmlFile.GetFullPath(), nextPluginIconPath );
							if ( package )
							{
								// Load all packages, then setup all packages
								// this allows multiple packages sharing one library
								packagesToSetup[ nextXmlFile.GetFullPath() ] = package;
							}
						}
						catch ( wxFBException& ex )
						{
							wxLogError( ex.what() );
						}
						moreXmlFiles = pluginXmlDir.GetNext( &packageXmlFile );
					}
					std::map< wxString, PObjectPackage >::iterator packageIt;
					for ( packageIt = packagesToSetup.begin(); packageIt != packagesToSetup.end(); ++packageIt )
					{
						// Setup the inheritance for base classes
						wxFileName fullNextPluginPath( nextPluginPath );
						if ( !fullNextPluginPath.IsAbsolute() )
							fullNextPluginPath.MakeAbsolute();

						wxFileName xmlFileName( packageIt->first );
						try
						{
							SetupPackage( xmlFileName.GetFullPath(), fullNextPluginPath.GetFullPath(), manager );

							// Load the C++ code tempates
							xmlFileName.SetExt("cppcode");
							LoadCodeGen( xmlFileName.GetFullPath() );

							// Load the Python code tempates
							xmlFileName.SetExt("pythoncode");
							LoadCodeGen( xmlFileName.GetFullPath() );

							std::pair< PackageMap::iterator, bool > addedPackage =
									packages.insert( PackageMap::value_type( packageIt->second->GetPackageName(),
									packageIt->second ) );
							if ( !addedPackage.second )
							{
								addedPackage.first->second->AppendPackage( packageIt->second );
								wxString msg = _( "Merged plugins named \"") + packageIt->second->GetPackageName() + "\"";
								Debug::Print( msg );
							}
						}
						catch ( wxFBException& ex )
						{
							wxLogError( ex.what() );
						}
					}
				}
    		}
    	}
        moreDirectories = pluginsDir.GetNext( &pluginDirName );
    }
    // Get previous plugin order
	wxConfigBase* config = wxConfigBase::Get();
	wxString pages = config->Read( "/palette/pageOrder", "Forms,Layout,Menu/Toolbar,Containers,Common,Additional," );

	// Add packages to the vector in the correct order
	wxStringTokenizer packageList( pages, "," );
	while ( packageList.HasMoreTokens() )
	{
		wxString packageName = packageList.GetNextToken();
		PackageMap::iterator packageIt = packages.find( packageName );
		if ( packages.end() == packageIt )
		{
			// Plugin missing - move on
			continue;
		}
		m_pkgs.push_back( packageIt->second );
		packages.erase( packageIt );
	}
    // If any packages remain in the map, they are new plugins and must still be added
    for ( PackageMap::iterator packageIt = packages.begin(); packageIt != packages.end(); ++packageIt )
    	m_pkgs.push_back( packageIt->second );
}

void ObjectDatabase::SetupPackage( const wxString& file, const wxString& path, PwxFBManager manager )
{
	#ifdef __WXMSW__
		wxString libPath = path;
	#else
		wxStandardPathsBase& stdpaths = wxStandardPaths::Get();
		wxString libPath = stdpaths.GetPluginsDir();
		libPath.Replace( wxTheApp->GetAppName().c_str(), "wxformbuilder" );
	#endif

	try
	{
		ticpp::Document doc;
		XMLUtils::LoadXMLFile( doc, true, file );

		ticpp::Element* root = doc.FirstChildElement( PACKAGE_TAG );

		// Get the library to import
		std::string lib;
		root->GetAttributeOrDefault( "lib", &lib, "" );
		if ( !lib.empty() )
		{
			// Allows plugin dependency dlls to be next to plugin dll in windows
			wxString workingDir = ::wxGetCwd();
			wxFileName::SetCwd( libPath );
			try
			{
				wxString fullLibPath = libPath + wxFILE_SEP_PATH + _WXSTR( lib );
				if ( m_importedLibraries.insert( fullLibPath ).second )
				{
					ImportComponentLibrary( fullLibPath, manager );
				}
			}
			catch ( ... )
			{
				// Put Cwd back
				wxFileName::SetCwd( workingDir );
				throw;
			}
			// Put Cwd back
			wxFileName::SetCwd( workingDir );
		}
		ticpp::Element* elem_obj = root->FirstChildElement( OBJINFO_TAG, false );
		while ( elem_obj )
		{
			std::string class_name;
			elem_obj->GetAttribute( CLASS_TAG, &class_name );

			PObjectInfo class_info = GetObjectInfo( _WXSTR( class_name ) );

			ticpp::Element* elem_base = elem_obj->FirstChildElement( "inherits", false );
			while ( elem_base )
			{
				std::string base_name;
				elem_base->GetAttribute( CLASS_TAG, &base_name );

				// Add a reference to its base class
				PObjectInfo base_info  = GetObjectInfo( _WXSTR( base_name ) );
				if ( class_info && base_info )
				{
					size_t baseIndex = class_info->AddBaseClass( base_info );

					std::string prop_name, value;
					ticpp::Element* inheritedProperty = elem_base->FirstChildElement( "property", false );
					while( inheritedProperty )
					{
						inheritedProperty->GetAttribute( NAME_TAG, &prop_name );
						value = inheritedProperty->GetText();
						class_info->AddBaseClassDefaultPropertyValue( baseIndex, _WXSTR( prop_name ), _WXSTR( value ) );
						inheritedProperty = inheritedProperty->NextSiblingElement( "property", false );
					}
				}
				elem_base = elem_base->NextSiblingElement( "inherits", false );
			}
			// Add the "C++" base class, predefined for the components and widgets
			wxString typeName = class_info->GetObjectTypeName();
			if ( HasCppProperties( typeName ) )
			{
				PObjectInfo cpp_interface = GetObjectInfo("C++");
				if ( cpp_interface )
				{
					size_t baseIndex = class_info->AddBaseClass( cpp_interface );
					if (    typeName == "sizer"    ||
                            typeName == "gbsizer"  ||
                            typeName == "menuitem"  )
					{
						class_info->AddBaseClassDefaultPropertyValue( baseIndex, "permission", "none" );
					}
				}
			}
			elem_obj = elem_obj->NextSiblingElement( OBJINFO_TAG, false );
		}
	}
	catch ( ticpp::Exception& ex )
	{
		THROW_WXFBEX( _WXSTR(ex.m_details) );
	}
}

bool ObjectDatabase::HasCppProperties(wxString type)
{
	return (type == "widget" 			||
			type == "expanded_widget" 	||
			type == "statusbar"			||
			type == "component"			||
			type == "container"			||
			type == "menubar"			||
			type == "menu"				||
			type == "menuitem"			||
			type == "submenu"			||
			type == "toolbar"			||
			type == "gbsizer"          	||
			type == "splitter"			||
            type == "dataview"			||
            type == "notebook"			||
			type == "listbook"			||
			type == "choicebook"		||
            type == "treebook"			||
			type == "toolbook"		    ||
			type == "auinotebook"		||
			type == "flatnotebook"		||
			type == "collapsiblepane" 	||
			type == "treelistctrl" );
}

void ObjectDatabase::LoadCodeGen( const wxString& file )
{
	try
	{
		ticpp::Document doc;
		XMLUtils::LoadXMLFile( doc, true, file );

		// Read the codegen element
		ticpp::Element* elem_codegen = doc.FirstChildElement("codegen");
		std::string language;
		elem_codegen->GetAttribute( "language", &language );
		wxString lang = _WXSTR( language );

		// Read the templates
		ticpp::Element* elem_templates = elem_codegen->FirstChildElement( "templates", false );
		while ( elem_templates  )
		{
			std::string prop_name;
			elem_templates->GetAttribute( "property", &prop_name, false );
			bool hasProp = !prop_name.empty();

			std::string class_name;
			elem_templates->GetAttribute( "class", &class_name, !hasProp );

			PCodeInfo code_info( new CodeInfo() );

			ticpp::Element* elem_template = elem_templates->FirstChildElement( "template", false );
			while ( elem_template )
			{
				std::string template_name;
				elem_template->GetAttribute( "name", &template_name );

				std::string template_code = elem_template->GetText( false );

				code_info->AddTemplate( _WXSTR(template_name), _WXSTR(template_code) );

				elem_template = elem_template->NextSiblingElement( "template", false );
			}
			if ( hasProp )
			{
				// Store code info for properties
				if ( !m_propertyTypeTemplates[ ParsePropertyType( _WXSTR(prop_name) ) ].insert( LangTemplateMap::value_type( lang, code_info ) ).second )
				{
					wxLogError( _("Found second template definition for property \"%s\" for language \"%s\""),
								_WXSTR(prop_name).c_str(), lang.c_str() );
				}
			}
			else
			{
				// Store code info for objects
				PObjectInfo obj_info = GetObjectInfo( _WXSTR( class_name ) );
				if ( obj_info )
				{
					obj_info->AddCodeInfo( lang, code_info );
				}
			}
			elem_templates = elem_templates->NextSiblingElement( "templates", false );
		}
	}
	catch( ticpp::Exception& ex )
	{
		wxLogError( _WXSTR( ex.m_details ) );
	}
	catch( wxFBException& ex )
	{
		wxLogError( ex.what() );
	}
}

PObjectPackage ObjectDatabase::LoadPackage( const wxString& file, const wxString& iconPath )
{
	PObjectPackage package;
	try
	{
		ticpp::Document doc;
		XMLUtils::LoadXMLFile( doc, true, file );

		ticpp::Element* root = doc.FirstChildElement( PACKAGE_TAG );

		// Name Attribute
		std::string pkg_name;
		root->GetAttribute( NAME_TAG, &pkg_name );

		// Description Attribute
		std::string pkg_desc;
		root->GetAttributeOrDefault( PKGDESC_TAG, &pkg_desc, "" );

		// Icon Path Attribute
		std::string pkgIconName;
		root->GetAttributeOrDefault( ICON_TAG, &pkgIconName, "" );
		wxString pkgIconPath = iconPath + wxFILE_SEP_PATH + _WXSTR( pkgIconName );

		wxBitmap pkg_icon;
		if ( !pkgIconName.empty() && wxFileName::FileExists( pkgIconPath ) )
		{
			wxImage image( pkgIconPath, wxBITMAP_TYPE_ANY );
			pkg_icon = wxBitmap( image.Scale( 16, 16 ) );
		}
		else
		{
			pkg_icon = AppBitmaps::GetBitmap( "unknown", 16 );
		}
		package = PObjectPackage ( new ObjectPackage( _WXSTR( pkg_name ), _WXSTR( pkg_desc ), pkg_icon ) );

		ticpp::Element* elem_obj = root->FirstChildElement( OBJINFO_TAG, false );

		while ( elem_obj )
		{
			std::string class_name;
			elem_obj->GetAttribute( CLASS_TAG, &class_name );

			std::string type;
			elem_obj->GetAttribute( "type", &type );

			std::string icon;
			elem_obj->GetAttributeOrDefault( "icon", &icon, "" );
			wxString iconFullPath = iconPath + wxFILE_SEP_PATH + _WXSTR(icon);

			std::string smallIcon;
			elem_obj->GetAttributeOrDefault( "smallIcon", &smallIcon, "" );
			wxString smallIconFullPath = iconPath + wxFILE_SEP_PATH + _WXSTR(smallIcon);

			bool startGroup;
			elem_obj->GetAttributeOrDefault( "startgroup", &startGroup, false );

			PObjectInfo obj_info( new ObjectInfo( _WXSTR( class_name ), GetObjectType( _WXSTR( type ) ), package, startGroup ) );

			if ( !icon.empty() && wxFileName::FileExists( iconFullPath ) )
			{
				wxImage img( iconFullPath, wxBITMAP_TYPE_ANY );
				obj_info->SetIconFile( wxBitmap( img.Scale( ICON_SIZE, ICON_SIZE ) ) );
			}
			else
			{
				obj_info->SetIconFile( AppBitmaps::GetBitmap( "unknown", ICON_SIZE ) );
			}

			if ( !smallIcon.empty() && wxFileName::FileExists( smallIconFullPath ) )
			{
				wxImage img( smallIconFullPath, wxBITMAP_TYPE_ANY );
				obj_info->SetSmallIconFile( wxBitmap( img.Scale( SMALL_ICON_SIZE, SMALL_ICON_SIZE ) ) );
			}
			else
			{
				wxImage img = obj_info->GetIconFile().ConvertToImage();
				obj_info->SetSmallIconFile( wxBitmap( img.Scale( SMALL_ICON_SIZE, SMALL_ICON_SIZE ) ) );
			}
			// Parse the Properties
			std::set< PropertyType > types;
			ParseProperties( elem_obj, obj_info, obj_info->GetCategory(), &types );
			ParseEvents    ( elem_obj, obj_info, obj_info->GetCategory() );

			// Add the ObjectInfo to the map
			m_objs.insert(ObjectInfoMap::value_type( _WXSTR( class_name ), obj_info ) );

			// Add the object to the palette
			if ( ShowInPalette( obj_info->GetObjectTypeName() ) )
				package->Add( obj_info );

			elem_obj = elem_obj->NextSiblingElement( OBJINFO_TAG, false );
		}
	}
	catch ( ticpp::Exception& ex )
	{
		THROW_WXFBEX( _WXSTR( ex.m_details ) );
	}
	return package;
}

void ObjectDatabase::ParseProperties( ticpp::Element* elem_obj, PObjectInfo obj_info,
									PPropertyCategory category, std::set< PropertyType >* types )
{
	ticpp::Element* elem_category = elem_obj->FirstChildElement( CATEGORY_TAG, false );
	while ( elem_category )
	{
		// Category name attribute
		std::string cname;
		elem_category->GetAttribute( NAME_TAG, &cname );
		PPropertyCategory new_cat( new PropertyCategory( _WXSTR( cname ) ) );

		// Add category
		category->AddCategory( new_cat );

		// Recurse
		ParseProperties( elem_category, obj_info, new_cat, types );

		elem_category = elem_category->NextSiblingElement( CATEGORY_TAG, false );
	}

	ticpp::Element* elem_prop = elem_obj->FirstChildElement( PROPERTY_TAG, false );
	while ( elem_prop )
	{
		// Property Name Attribute
		std::string pname;
		elem_prop->GetAttribute( NAME_TAG, &pname );
		category->AddProperty( _WXSTR( pname ) );

		std::string description;
		elem_prop->GetAttributeOrDefault( DESCRIPTION_TAG, &description, "" );

		std::string customEditor;
		elem_prop->GetAttributeOrDefault( CUSTOM_EDITOR_TAG, &customEditor, "" );

		std::string prop_type;
		elem_prop->GetAttribute( "type", &prop_type );
		PropertyType ptype;
		try
		{
			ptype = ParsePropertyType( _WXSTR( prop_type ) );
		}
		catch( wxFBException& ex )
		{
			wxLogError( _("Error: %s\nWhile parsing property \"%s\" of class \"%s\""),
						ex.what(), _WXSTR( pname ).c_str(), obj_info->GetClassName().c_str() );

			elem_prop = elem_prop->NextSiblingElement( PROPERTY_TAG, false );
			continue;
		}
		// Get default value
		std::string def_value;
		try
		{
			ticpp::Node* lastChild = elem_prop->LastChild( false );
            if ( lastChild && lastChild->Type()== TiXmlNode::TEXT )
            {
				ticpp::Text* text = lastChild->ToText();
				def_value = text->Value();
			}
		}
		catch( ticpp::Exception& ) 
		{
			wxLogError( "Error: While getting default value \"%s\" of class \"%s\"", _WXSTR(pname).c_str(), obj_info->GetClassName().c_str() );
		}

		// If the property is a "bitlist" then parse all of the options
		POptionList opt_list;
		std::list< PropertyChild > children;
		if ( ptype == PT_BITLIST || ptype == PT_OPTION )
		{
			opt_list = POptionList( new OptionList() );
			ticpp::Element* elem_opt = elem_prop->FirstChildElement( "option", false );
			while( elem_opt )
			{
				std::string macro_name;
				elem_opt->GetAttribute( NAME_TAG, &macro_name );

				std::string macro_description;
				elem_opt->GetAttributeOrDefault( DESCRIPTION_TAG, &macro_description, "" );

				opt_list->AddOption( _WXSTR( macro_name ), _WXSTR(macro_description) );

				m_macroSet.insert( _WXSTR( macro_name ) );

				elem_opt = elem_opt->NextSiblingElement( "option", false );
			}
		}
		else if ( ptype == PT_PARENT )
		{
			// If the property is a parent, then get the children
			def_value.clear();
			ticpp::Element* elem_child = elem_prop->FirstChildElement( "child", false );
			while ( elem_child )
			{
				PropertyChild child;

				std::string child_name;
				elem_child->GetAttribute( NAME_TAG, &child_name );
				child.m_name = _WXSTR( child_name );

				std::string child_description;
				elem_child->GetAttributeOrDefault( DESCRIPTION_TAG, &child_description, "" );
				child.m_description = _WXSTR( child_description );

				// Get default value
				ticpp::Node* lastChild = elem_child->LastChild(false);
				if ( lastChild )
				{
					ticpp::Text* text = lastChild->ToText();
					child.m_defaultValue = _WXSTR( text->Value() );

					// Build parent default value
					if ( children.size() > 0 )
					{
						def_value += "; ";
					}
					def_value += text->Value();
				}
				children.push_back( child );

				elem_child = elem_child->NextSiblingElement( "child", false );
			}
		}
		// Create an instance of PropertyInfo
		PPropertyInfo prop_info( new PropertyInfo( _WXSTR( pname ), ptype, _WXSTR( def_value ),
													_WXSTR( description ), _WXSTR( customEditor ), opt_list, children ) );
		// Add the PropertyInfo to the property
		obj_info->AddPropertyInfo( prop_info );

		// Merge property code templates, once per property type
		if ( types->insert( ptype ).second )
		{
			LangTemplateMap& propLangTemplates = m_propertyTypeTemplates[ ptype ];
			LangTemplateMap::iterator lang;
			for ( lang = propLangTemplates.begin(); lang != propLangTemplates.end(); ++lang )
			{
				if ( lang->second )
				{
					obj_info->AddCodeInfo( lang->first, lang->second );
				}
			}
		}
		elem_prop = elem_prop->NextSiblingElement( PROPERTY_TAG, false );
	}
}

void ObjectDatabase::ParseEvents( ticpp::Element* elem_obj, PObjectInfo obj_info, PPropertyCategory category )
{
	ticpp::Element* elem_category = elem_obj->FirstChildElement( CATEGORY_TAG, false );
	while ( elem_category )
	{
		// Category name attribute
		std::string cname;
		elem_category->GetAttribute( NAME_TAG, &cname );
		PPropertyCategory new_cat( new PropertyCategory( _WXSTR( cname ) ) );

		// Add category
		category->AddCategory( new_cat );

		// Recurse
		ParseEvents( elem_category, obj_info, new_cat );

		elem_category = elem_category->NextSiblingElement( CATEGORY_TAG, false );
	}

	ticpp::Element* elem_evt = elem_obj->FirstChildElement( EVENT_TAG, false );
	while ( elem_evt )
	{
		// Event Name Attribute
		std::string evt_name;
		elem_evt->GetAttribute( NAME_TAG, &evt_name );
		category->AddEvent( _WXSTR( evt_name ) );

		// Event class
		std::string evt_class;
		elem_evt->GetAttributeOrDefault( EVENT_CLASS_TAG, &evt_class, "wxEvent" );

		// Help string
		std::string description;
		elem_evt->GetAttributeOrDefault( DESCRIPTION_TAG, &description, "" );

		// Get default value
		std::string def_value;
		ticpp::Node* lastChild = elem_evt->LastChild(false);
		if ( lastChild )
		{
			ticpp::Text* text = lastChild->ToText();
			def_value = text->Value();
		}

		// Create an instance of EventInfo
		PEventInfo evt_info(
			new EventInfo( _WXSTR( evt_name ), _WXSTR( evt_class ), _WXSTR( def_value ), _WXSTR( description ) ) );

		// Add the EventInfo to the event
		obj_info->AddEventInfo( evt_info );

		elem_evt = elem_evt->NextSiblingElement( EVENT_TAG, false );
	}
}

bool ObjectDatabase::ShowInPalette( wxString type )
{
	return (type == "form"					||
			type == "wizard" 				||
			type == "wizardpage"       		||
			type == "menubar_form"			||
			type == "toolbar_form"			||
			type == "sizer"					||
			type == "gbsizer"				||
			type == "menubar"				||
			type == "menu"					||
			type == "menuitem"				||
			type == "submenu"				||
			type == "toolbar"				||
			type == "tool"					||
			type == "widget"				||
			type == "expanded_widget"		||
			type == "dataview"				||
			type == "dataviewcolumn"		||
			type == "notebook"				||
			type == "listbook"				||
			type == "choicebook"			||
			type == "treebook"			    ||
            type == "toolbook"				||
			type == "auinotebook"			||
			type == "flatnotebook"			||
			type == "statusbar"				||
			type == "component"				||
			type == "container"				||
			type == "treelistctrl"			||
			type == "treelistctrlcolumn" 	||
			type == "collapsiblepane" 		||
			type == "splitter" );
}

void ObjectDatabase::ImportComponentLibrary( wxString libfile, PwxFBManager manager )
{
	wxString path = libfile;

	// This will prevent loading debug libraries in release and vice versa
	// That used to cause crashes when trying to debug
	#ifdef __WXFB_DEBUG__
		path += "d";
	#endif

	// Find the GetComponentLibrary function - all plugins must implement this
	typedef IComponentLibrary* (*PFGetComponentLibrary)( IManager* manager );

	#ifdef __WXMAC__
		path += ".dylib";

		// Open the library
		void* handle = dlopen( path.mb_str(), RTLD_LAZY );

		if ( !handle )
		{
			wxString error = wxString( dlerror(), wxConvUTF8 );
			THROW_WXFBEX( _("Error loading library ") << path << " " << error )
		}
		dlerror(); // Reset errors

		// Load the symbol
		PFGetComponentLibrary GetComponentLibrary = (PFGetComponentLibrary) dlsym( handle, "GetComponentLibrary" );
		PFFreeComponentLibrary FreeComponentLibrary = (PFFreeComponentLibrary) dlsym( handle, "FreeComponentLibrary" );

		const char *dlsym_error = dlerror();
		if (dlsym_error)
		{
			wxString error = wxString( dlsym_error, wxConvUTF8 );
			THROW_WXFBEX( path << _(" is not a valid component library: ") << error )
			dlclose( handle );
		}
		else
		{
			m_libs.push_back( handle );
		}
	#else
		// Attempt to load the DLL
		wxDynamicLibrary* library = new wxDynamicLibrary( path );
		if ( !library->IsLoaded() )
			THROW_WXFBEX( _("Error loading library ") << path )

		m_libs.push_back( library );

		PFGetComponentLibrary GetComponentLibrary =		( PFGetComponentLibrary )library->GetSymbol("GetComponentLibrary");
		PFFreeComponentLibrary FreeComponentLibrary = 	( PFFreeComponentLibrary )library->GetSymbol("FreeComponentLibrary");

		if ( !(GetComponentLibrary && FreeComponentLibrary) )
			THROW_WXFBEX( path << _(" is not a valid component library") )
#endif
// TODO: Check these changes
		wxString msg = _("[Database::ImportComponentLibrary] Importing ") + path + _(" library");
		Debug::Print( msg );

	// Get the component library
	IComponentLibrary* comp_lib = GetComponentLibrary( (IManager*)manager.get() );

	// Store the function to free the library
	m_componentLibs[ FreeComponentLibrary ] = comp_lib;

	// Import all of the components
	for ( unsigned int i = 0; i < comp_lib->GetComponentCount(); i++ )
	{
		wxString class_name = comp_lib->GetComponentName( i );
		IComponent* comp = comp_lib->GetComponent( i );

		// Look for the class in the data read from the .xml files
		PObjectInfo class_info = GetObjectInfo( class_name );
		if ( class_info )
		{
			class_info->SetComponent( comp );
		}
		else
		{
			wxString msg = _( "ObjectInfo for <") + class_name + _("> not found while loading library <") + path + ">";
			Debug::Print( msg );
		}
	}
	// Add all of the macros in the library to the macro dictionary
	PMacroDictionary dic = MacroDictionary::GetInstance();
	for ( unsigned int i = 0; i < comp_lib->GetMacroCount(); i++ )
	{
		wxString name = comp_lib->GetMacroName( i );
		int value = comp_lib->GetMacroValue( i );
		dic->AddMacro( name, value );
		m_macroSet.erase( name );
	}
}

PropertyType ObjectDatabase::ParsePropertyType( wxString str )
{
	PropertyType result;
	PTMap::iterator it = m_propTypes.find( str );
	if (it != m_propTypes.end())
		result = it->second;
	else
	{
		result = PT_ERROR;
		THROW_WXFBEX( wxString::Format( _("Unknown property type \"%s\""), str.c_str() ) );
	}
	return result;
}

wxString  ObjectDatabase::ParseObjectType( wxString str )
{
	return str;
}

#define PT(x,y) m_propTypes.insert(PTMap::value_type(x,y))
void ObjectDatabase::InitPropertyTypes()
{
	PT( "bool",				PT_BOOL				);
	PT( "text",				PT_TEXT				);
	PT( "int",				PT_INT				);
	PT( "uint",				PT_UINT				);
	PT( "bitlist",			PT_BITLIST			);
	PT( "intlist",			PT_INTLIST			);
	PT( "uintlist",			PT_UINTLIST			);
	PT( "option",			PT_OPTION			);
	PT( "macro",			PT_MACRO			);
	PT( "path",				PT_PATH				);
	PT( "file",				PT_FILE				);
	PT( "wxString", 		PT_WXSTRING			);
	PT( "wxPoint",			PT_WXPOINT			);
	PT( "wxSize",			PT_WXSIZE			);
	PT( "wxFont",			PT_WXFONT			);
	PT( "wxColour",			PT_WXCOLOUR			);
	PT( "bitmap",			PT_BITMAP			);
	PT( "wxString_i18n", 	PT_WXSTRING_I18N 	);
	PT( "stringlist",		PT_STRINGLIST		);
	PT( "float",			PT_FLOAT			);
	PT( "parent",			PT_PARENT			);
}

bool ObjectDatabase::LoadObjectTypes()
{
	ticpp::Document doc;
	wxString xmlPath = m_xmlPath + "objtypes.xml";
	XMLUtils::LoadXMLFile( doc, true, xmlPath );

	// First load the object types, then the children
	try
	{
		ticpp::Element* root = doc.FirstChildElement("definitions");
		ticpp::Element* elem = root->FirstChildElement("objtype");
		while ( elem )
		{
			bool hidden;
			elem->GetAttributeOrDefault( "hidden", &hidden, false );

			bool item;
			elem->GetAttributeOrDefault( "item", &item, false );

			wxString name = _WXSTR( elem->GetAttribute("name") );

			PObjectType objType( new ObjectType( name, (int)m_types.size(), hidden, item ) );
			m_types.insert( ObjectTypeMap::value_type( name, objType ) );

			elem = elem->NextSiblingElement( "objtype", false );
		}
		// Now load the children
		elem = root->FirstChildElement("objtype");
		while (elem)
		{
			wxString name = _WXSTR( elem->GetAttribute("name") );

			// Get the objType
			PObjectType objType = GetObjectType( name );
			ticpp::Element* child = elem->FirstChildElement( "childtype", false );
			while ( child )
			{
				int nmax = -1; // No limit
				child->GetAttributeOrDefault( "nmax", &nmax, -1 );

				wxString childname = _WXSTR( child->GetAttribute("name") );

				PObjectType childType = GetObjectType( childname );
				if ( !childType )
				{
					wxLogError( _("No Object Type found for \"%s\""), childname.c_str() );
					continue;
				}
				objType->AddChildType( childType, nmax );

				child = child->NextSiblingElement( "childtype", false );
			}
			elem = elem->NextSiblingElement( "objtype", false );
		}
	}
	catch( ticpp::Exception& ex )
	{
		wxLogError( _WXSTR( ex.m_details ) );
		return false;
	}
	return true;
}

PObjectType ObjectDatabase::GetObjectType( wxString name )
{
	PObjectType type;
	ObjectTypeMap::iterator it = m_types.find( name );
	if (it != m_types.end())
		type = it->second;

	return type;
}
