////////////////////////////////////////////////////////////////////////////////
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
// Python code generation writen by
//   Michal Bližňak - michal.bliznak@gmail.com
//
///////////////////////////////////////////////////////////////////////////////

#include "pythoncg.h"
#include "codewriter.h"
#include "model/database.h"
#include "model/objectbase.h"
#include "rad/appdata.h"
#include "utils/debug.h"
#include "utils/typeconv.h"
#include "utils/wxfbexception.h"

#include <algorithm>

#include <wx/filename.h>
#include <wx/tokenzr.h>
#include <wx/defs.h>

PythonTemplateParser::PythonTemplateParser( PObjectBase obj, wxString _template, bool useI18N, bool useRelativePath, wxString basePath )
	:
	TemplateParser(obj,_template),
	m_i18n( useI18N ),
	m_useRelativePath( useRelativePath ),
	m_basePath( basePath )
{
	if ( !wxFileName::DirExists( m_basePath ) )
	{
		m_basePath.clear();
	}
	SetupModulePrefixes();
}

PythonTemplateParser::PythonTemplateParser( const PythonTemplateParser & that, wxString _template )
	:
	TemplateParser( that, _template ),
	m_i18n( that.m_i18n ),
	m_useRelativePath( that.m_useRelativePath ),
	m_basePath( that.m_basePath )
{
	SetupModulePrefixes();
}

wxString PythonTemplateParser::RootWxParentToCode()
{
	return "self";
}

PTemplateParser PythonTemplateParser::CreateParser( const TemplateParser* oldparser, wxString _template )
{
	const PythonTemplateParser* pythonOldParser = dynamic_cast< const PythonTemplateParser* >( oldparser );
	if ( pythonOldParser != NULL )
	{
		PTemplateParser newparser( new PythonTemplateParser( *pythonOldParser, _template ) );
		return newparser;
	}
	return PTemplateParser();
}

/**
* Convert the value of the property to Python code
*/
wxString PythonTemplateParser::ValueToCode( PropertyType type, wxString value )
{
	wxString result;

	switch ( type )
	{
	case PT_WXPARENT:
		{
			result = "self." + value;
			break;
		}
	case PT_WXSTRING:
	case PT_FILE:
	case PT_PATH:
		{
			if ( value.empty() )
			{
				result << "wx.EmptyString";
			}
			else
			{
				result << "u\"" << PythonCodeGenerator::ConvertPythonString( value ) << "\"";
			}
			break;
		}
	case PT_WXSTRING_I18N:
		{
			if ( value.empty() )
			{
				result << "wx.EmptyString";
			}
			else
			{
				if ( m_i18n )
				{
					result << "u\"" << PythonCodeGenerator::ConvertPythonString(value) << "\"";
				}
				else
				{
					result << "u\"" << PythonCodeGenerator::ConvertPythonString(value) << "\"";
				}
			}
			break;
		}
	case PT_CLASS:
	case PT_MACRO:
	case PT_OPTION:
		{
			result = value;
			wxString pred = m_predModulePrefix[value];

			if( !pred.empty() )	result.Replace( "wx", pred );
			else
				result.Replace( "wx", "wx." );

			break;
		}
	case PT_TEXT:
	case PT_FLOAT:
	case PT_INT:
	case PT_UINT:
		{
			result = value;
			break;
		}
	case PT_BITLIST:
		{
			result = ( value.empty() ? "0" : value );

			wxString pred, bit;
			wxStringTokenizer bits( result, "|", wxTOKEN_STRTOK );

			while( bits.HasMoreTokens() )
			{
				bit = bits.GetNextToken();
				pred = m_predModulePrefix[bit];

				if( bit.Contains("wx") )
				{
					if( !pred.empty() )	result.Replace( bit, pred + bit.AfterFirst('x') );
					else
						result.Replace( bit, "wx." + bit.AfterFirst('x') );
				}
			}
			break;
		}
	case PT_WXPOINT:
		{
			if ( value.empty() )
			{
				result = "wx.DefaultPosition";
			}
			else
			{
				result << "wx.Point( " << value << " )";
			}
			break;
		}
	case PT_WXSIZE:
		{
			if ( value.empty() )
			{
				result = "wx.DefaultSize";
			}
			else
			{
				result << "wx.Size( " << value << " )";
			}
			break;
		}
	case PT_BOOL:
		{
			result = ( value == "0" ? "False" : "True" );
			break;
		}
	case PT_WXFONT:
		{
			if ( !value.empty() )
			{
				wxFontContainer font = TypeConv::StringToFont( value );
// TODO: Check thses changes
				int pointSize = font.GetPointSize();
				wxString size = pointSize <= 0 ? "wx.NORMAL_FONT.GetPointSize()" : wxString::Format("%i", pointSize );
				
				wxString ffname = ( font.m_faceName.empty() ? "wx.EmptyString" : "\"" + font.m_faceName + "\"" );
				result	= wxString::Format( "wx.Font( %s, %i, %i, %i, %s, %s )",
											size.c_str(),
											font.GetFamily(),
											font.GetStyle(),
											font.GetWeight(),
											( font.GetUnderlined() ? "True" : "False" ),
											( ffname.c_str() ) );
			}
			else
			{
				result = "wx.NORMAL_FONT";
			}
			break;
		}
	case PT_WXCOLOUR:
		{
			if ( !value.empty() )
			{
				if ( value.find_first_of( "wx" ) == 0 )
				{
					// System Colour
					result << "wx.SystemSettings.GetColour( " << ValueToCode( PT_OPTION, value ) << " )";
				}
				else
				{
					wxColour colour = TypeConv::StringToColour( value );
					result = wxString::Format( "wx.Colour( %i, %i, %i )", colour.Red(), colour.Green(), colour.Blue() );
				}
			}
			else
			{
				result = "wx.Colour()";
			}
			break;
		}
	case PT_BITMAP:
		{
			wxString path;
			wxString source;
			wxSize icoSize;
			TypeConv::ParseBitmapWithResource( value, &path, &source, &icoSize );

			if ( path.empty() )
			{
				// Empty path, generate Null Bitmap
				result = "wx.NullBitmap";
				break;
			}

            if ( path.StartsWith( "file:" ) )
            {
                wxLogWarning( _("Python code generation does not support using URLs for bitmap properties:\n%s"), path.c_str() );
                result = "wx.NullBitmap";
                break;
            }

            if ( source == "Load From File" )
			{
			    wxString absPath;
			    try
				{
				    absPath = TypeConv::MakeAbsolutePath( path, AppData()->GetProjectPath() );
				}
				catch( wxFBException& ex )
				{
				    wxLogError( ex.what() );
				    result = "wx.NullBitmap";
				    break;
				}

				wxString file = ( m_useRelativePath ? TypeConv::MakeRelativePath( absPath, m_basePath ) : absPath );

				result << "wx.Bitmap( u\"" << PythonCodeGenerator::ConvertPythonString( file ) << "\", wx.BITMAP_TYPE_ANY )";
			}
			else if ( source == "Load From Resource" )
			{
				result << "wx.Bitmap( u\"" << path << "\", wx.BITMAP_TYPE_RESOURCE )";
			}
			else if ( source == "Load From Icon Resource" )
			{
                if ( wxDefaultSize == icoSize )
                {
                    result << "wx.ICON( " << path << " )";
                }
                else
                {
                    result.Printf( "wx.Icon( u\"%s\", wx.BITMAP_TYPE_ICO_RESOURCE, %i, %i )", path.c_str(), icoSize.GetWidth(), icoSize.GetHeight() );
                }
			}

			break;
		}
	case PT_STRINGLIST:
		{
			// Stringlists are generated like a sequence of wxString separated by ', '.
			wxArrayString array = TypeConv::StringToArrayString( value );
			if ( array.Count() > 0 )
			{
				result = ValueToCode( PT_WXSTRING_I18N, array[0] );
			}

			for ( size_t i = 1; i < array.Count(); i++ )
			{
				result << ", " << ValueToCode( PT_WXSTRING_I18N, array[i] );
			}
			break;
		}
	default:
		break;
	}

	return result;
}

///////////////////////////////////////////////////////////////////////////////

PythonCodeGenerator::PythonCodeGenerator()
{
	SetupPredefinedMacros();
	m_useRelativePath = false;
	m_i18n = false;
	m_firstID = 1000;
}

wxString PythonCodeGenerator::ConvertPythonString( wxString text )
{
	wxString result;

	for ( size_t i = 0; i < text.length(); i++ )
	{
		wxChar c = text[i];

		switch ( c )
		{
		case '"':
			result += "\\\"";
			break;

		case '\\':
			result += "\\\\";
			break;

		case '\t':
			result += "\\t";
			break;

		case '\n':
			result += "\\n";
			break;

		case '\r':
			result += "\\r";
			break;

		default:
			result += c;
			break;
		}
	}
	return result;
}

void PythonCodeGenerator::GenerateInheritedClass( PObjectBase userClasses, PObjectBase form )
{
	if (!userClasses)
	{
		wxLogError( _("There is no object to generate inherited class") );
		return;
	}

	if ( "UserClasses" != userClasses->GetClassName() )
	{
		wxLogError( _("This not a UserClasses object") );
		return;
	}

	wxString type = userClasses->GetPropertyAsString( "type" );

	// Start file
	wxString code = GetCode( userClasses, "file_comment" );
	m_source->WriteLn( code );
	m_source->WriteLn( wxEmptyString );

	code = GetCode( userClasses, "source_include" );
	m_source->WriteLn( code );
	m_source->WriteLn( wxEmptyString );

	code = GetCode( userClasses, "class_decl" );
	m_source->WriteLn( code );
	m_source->Indent();

	code = GetCode( userClasses, type + "_cons_def" );
	m_source->WriteLn( code );

	// Do events
	EventVector events;
	FindEventHandlers( form, events );

	if ( events.size() > 0 )
	{
		code = GetCode( userClasses, "event_handler_comment" );
		m_source->WriteLn( code );

		std::set<wxString> generatedHandlers;
		for ( size_t i = 0; i < events.size(); i++ )
		{
			PEvent event = events[i];
			if ( generatedHandlers.find( event->GetValue() ) == generatedHandlers.end() )
			{
				m_source->WriteLn( wxString::Format( "def %s( self, event ):",  event->GetValue().c_str() ) );
				m_source->Indent();
				m_source->WriteLn( wxString::Format( "# TODO: Implement %s", event->GetValue().c_str() ) );
				m_source->WriteLn("pass");
				m_source->Unindent();
				m_source->WriteLn( wxEmptyString );
				generatedHandlers.insert(event->GetValue());
			}
		}
		m_source->WriteLn( wxEmptyString );
	}

	m_source->Unindent();
}

bool PythonCodeGenerator::GenerateCode( PObjectBase project )
{
	if (!project)
	{
		wxLogError( _("There is no project to generate code") );
		return false;
	}

	m_i18n = false;
	PProperty i18nProperty = project->GetProperty("internationalize");
	if (i18nProperty && i18nProperty->GetValueAsInteger())
		m_i18n = true;

	m_disconnectEvents = ( project->GetPropertyAsInteger("disconnect_python_events") != 0 );

	m_source->Clear();

	// Insert python preamble

	wxString code = GetCode( project, "python_preamble" );
	if ( !code.empty() )
	{
		m_source->WriteLn( code );
		m_source->WriteLn( wxEmptyString );
	}

	code = (
			"###########################################################################\n"
			"## Python code generated with wxFormBuilder (version " __DATE__ "\n"
			"## http://www.wxformbuilder.org/\n"
			"##\n"
			"## PLEASE DO \"NOT\" EDIT THIS FILE!\n"
			"###########################################################################\n" );

	m_source->WriteLn( code );

	PProperty propFile = project->GetProperty( "file" );
	if (!propFile)
	{
		wxLogError( _("Missing \"file\" property on Project Object") );
		return false;
	}
	wxString file = propFile->GetValue();
	if ( file.empty() )
	{
		file = "noname";
	}
	// Generate the subclass sets
	std::set< wxString > subclasses;
	std::vector< wxString > headerIncludes;

	GenSubclassSets( project, &subclasses, &headerIncludes );

	// Generating in the .h header file those include from components dependencies.
	std::set< wxString > templates;
	GenIncludes( project, &headerIncludes, &templates );

	// Write the include lines
	std::vector<wxString>::iterator include_it;
	for ( include_it = headerIncludes.begin(); include_it != headerIncludes.end(); ++include_it )
	{
		m_source->WriteLn( *include_it );
	}
	if ( !headerIncludes.empty() )
	{
		m_source->WriteLn("");
	}

	// Generating "defines" for macros
	GenDefines( project );

	wxString eventHandlerPostfix;
	PProperty eventKindProp = project->GetProperty("skip_python_events");
	if( eventKindProp->GetValueAsInteger() )
	{
		 eventHandlerPostfix = "event.Skip()";
	}
	else
		eventHandlerPostfix = "pass";

	PProperty disconnectMode = project->GetProperty("disconnect_mode");
	m_disconnecMode = disconnectMode->GetValueAsString();

	for ( unsigned int i = 0; i < project->GetChildCount(); i++ )
	{
		PObjectBase child = project->GetChild( i );

		EventVector events;
		FindEventHandlers( child, events );
		//GenClassDeclaration( child, useEnum, classDecoration, events, eventHandlerPrefix, eventHandlerPostfix );
		GenClassDeclaration( child, false, "", events, eventHandlerPostfix );
	}

	code = GetCode( project, "python_epilogue" );
	if( !code.empty() ) m_source->WriteLn( code );

	return true;
}

void PythonCodeGenerator::GenEvents( PObjectBase class_obj, const EventVector &events, bool disconnect )
{
	if ( events.empty() )
	{
		return;
	}

	if( disconnect )
	{
		m_source->WriteLn("# Disconnect Events");
	}
	else
	{
		m_source->WriteLn();
		m_source->WriteLn("# Connect Events");
	}

	PProperty propName = class_obj->GetProperty("name");
	if ( !propName )
	{
		wxLogError( _("Missing \"name\" property on \"%s\" class. Review your XML object description"),
					class_obj->GetClassName().c_str());
		return;
	}

	wxString class_name = propName->GetValue();
	if ( class_name.empty() )
	{
		wxLogError( _("Object name can not be null") );
		return;
	}

	wxString base_class;
	wxString handlerName;

	PProperty propSubclass = class_obj->GetProperty("subclass");
	if ( propSubclass )
	{
		wxString subclass = propSubclass->GetChildFromParent("name");
		if ( !subclass.empty() )
		{
			base_class = subclass;
		}
	}

	if ( base_class.empty() )
		base_class = "wx." + class_obj->GetClassName();

	if ( events.size() > 0 )
	{
		for ( size_t i = 0; i < events.size(); i++ )
		{
			PEvent event = events[i];

			handlerName = event->GetValue();

			wxString templateName = wxString::Format( "connect_%s", event->GetName().c_str() );

			PObjectBase obj = event->GetObject();
			if ( !GenEventEntry( obj, obj->GetObjectInfo(), templateName, handlerName, disconnect ) )
			{
				wxLogError( _("Missing \"evt_%s\" template for \"%s\" class. Review your XML object description"),
							templateName.c_str(), class_name.c_str() );
			}
		}
	}
}

bool PythonCodeGenerator::GenEventEntry( PObjectBase obj, PObjectInfo obj_info, const wxString& templateName, const wxString& handlerName, bool disconnect )
{
	wxString _template;
	PCodeInfo code_info = obj_info->GetCodeInfo("Python");
	if ( code_info )
	{
		_template = code_info->GetTemplate( wxString::Format( "evt_%s%s", disconnect ? "dis" : "", templateName.c_str() ) );
		if ( disconnect && _template.empty() )
		{
			_template = code_info->GetTemplate( "evt_" + templateName );
			_template.Replace( "Bind", "Unbind", true );
		}
		if ( !_template.empty() )
		{
			if( disconnect )
			{
				if( m_disconnecMode == "handler_name") _template.Replace( "#handler", "handler = self." + handlerName );
				else if(m_disconnecMode == "source_name") _template.Replace( "#handler", "None" ); //"self." + obj->GetProperty("name")->GetValueAsString() );
			}
			else
				_template.Replace( "#handler", "self." + handlerName );

			PythonTemplateParser parser( obj, _template, m_i18n, m_useRelativePath, m_basePath );
			m_source->WriteLn( parser.ParseTemplate() );
			return true;
		}
	}
	for ( unsigned int i = 0; i < obj_info->GetBaseClassCount(); i++ )
	{
		PObjectInfo base_info = obj_info->GetBaseClass( i );
		if ( GenEventEntry( obj, base_info, templateName, handlerName, disconnect ) )
		{
			return true;
		}
	}
	return false;
}

void PythonCodeGenerator::GenVirtualEventHandlers( const EventVector& events, const wxString& eventHandlerPostfix )
{
	if ( events.size() > 0 )
	{
		// There are problems if we create "pure" virtual handlers, because some
		// events could be triggered in the constructor in which virtual methods are
		// execute properly.
		// So we create a default handler which will skip the event.
		m_source->WriteLn( wxEmptyString );
		m_source->WriteLn( _("# Virtual event handlers, override them in your derived class") );

		std::set<wxString> generatedHandlers;
		for ( size_t i = 0; i < events.size(); i++ )
		{
			PEvent event = events[i];
			wxString aux = "def " + event->GetValue() + "( self, event ):";

			if (generatedHandlers.find(aux) == generatedHandlers.end())
			{
				m_source->WriteLn(aux);
				m_source->Indent();
				m_source->WriteLn(eventHandlerPostfix);
				m_source->Unindent();

				generatedHandlers.insert(aux);
			}
			if( i < (events.size()-1) )  m_source->WriteLn();
		}
		m_source->WriteLn( wxEmptyString );
	}
}

void PythonCodeGenerator::GetGenEventHandlers( PObjectBase obj )
{
	GenDefinedEventHandlers( obj->GetObjectInfo(), obj );

	for (unsigned int i = 0; i < obj->GetChildCount() ; i++)
	{
		PObjectBase child = obj->GetChild(i);
		GetGenEventHandlers(child);
	}
}

void PythonCodeGenerator::GenDefinedEventHandlers( PObjectInfo info, PObjectBase obj )
{
	PCodeInfo code_info = info->GetCodeInfo("Python");
	if ( code_info )
	{
		wxString _template = code_info->GetTemplate("generated_event_handlers");
		if ( !_template.empty() )
		{
			PythonTemplateParser parser( obj, _template, m_i18n, m_useRelativePath, m_basePath );
			wxString code = parser.ParseTemplate();

			if ( !code.empty() )
			{
				m_source->WriteLn(code);
			}
		}
	}
	// Proceeding recursively with the base classes
	for ( unsigned int i = 0; i < info->GetBaseClassCount(); i++ )
	{
		PObjectInfo base_info = info->GetBaseClass( i );
		GenDefinedEventHandlers( base_info, obj );
	}
}


wxString PythonCodeGenerator::GetCode(PObjectBase obj, wxString name, bool silent)
{
	wxString _template;
	PCodeInfo code_info = obj->GetObjectInfo()->GetCodeInfo( "Python" );

	if (!code_info)
	{
		if( !silent )
		{
			wxString msg( wxString::Format( _("Missing \"%s\" template for \"%s\" class. Review your XML object description"),
							name.c_str(), obj->GetClassName().c_str() ) );
			wxLogError(msg);
		}
		return "";
	}

	_template = code_info->GetTemplate( name );

	PythonTemplateParser parser( obj, _template, m_i18n, m_useRelativePath, m_basePath );
	wxString code = parser.ParseTemplate();

	return code;
}

void PythonCodeGenerator::GenClassDeclaration( PObjectBase class_obj, bool use_enum,
												const wxString& classDecoration, const EventVector &events,
												const wxString& eventHandlerPostfix)
{
	PProperty propName = class_obj->GetProperty("name");
	if ( !propName )
	{
		wxLogError( _("Missing \"name\" property on \"%s\" class. Review your XML object description"),
					class_obj->GetClassName().c_str() );
		return;
	}
	wxString class_name = propName->GetValue();
	if ( class_name.empty() )
	{
		wxLogError( _("Object name can not be null") );
		return;
	}
	m_source->WriteLn( "###########################################################################" );
	m_source->WriteLn( "## Class " + class_name);
	m_source->WriteLn( "###########################################################################" );
	m_source->WriteLn( );

	m_source->WriteLn( "class " + classDecoration + class_name + " ( " + GetCode( class_obj, "base" ).Trim() + " ):" );
	m_source->Indent();

	// The constructor is also included within public
	GenConstructor( class_obj, events );
	GenDestructor( class_obj, events );

	m_source->WriteLn("");

	// event handlers
	GenVirtualEventHandlers(events, eventHandlerPostfix);
	GetGenEventHandlers( class_obj );

	m_source->Unindent();
	m_source->WriteLn("");
}

void PythonCodeGenerator::GenSubclassSets( PObjectBase obj,
											std::set< wxString >* subclasses,
											std::vector< wxString >* headerIncludes )
{
	// Call GenSubclassForwardDeclarations on all children as well
	for ( unsigned int i = 0; i < obj->GetChildCount(); i++ )
	{
		GenSubclassSets( obj->GetChild( i ), subclasses, headerIncludes );
	}
	// Fill the set
	PProperty subclass = obj->GetProperty("subclass");
	if ( subclass )
	{
		std::map< wxString, wxString > children;
		subclass->SplitParentProperty( &children );

		std::map< wxString, wxString >::iterator name;
		name = children.find("name");
		if ( children.end() == name )
		{
			// No name, so do nothing
			return;
		}
		wxString nameVal = name->second;
		if ( nameVal.empty() )
		{
			// No name, so do nothing
			return;
		}
		// Now get the header
		std::map< wxString, wxString >::iterator header;
		header = children.find("header");
		if ( children.end() == header )
		{
			// No header, so do nothing
			return;
		}
		wxString headerVal = header->second;
		if ( headerVal.empty() )
		{
			// No header, so do nothing
			return;
		}
		// Got a header
		PObjectInfo info = obj->GetObjectInfo();
		if ( !info )
		{
			return;
		}
		PObjectPackage pkg = info->GetPackage();
		if ( !pkg )
		{
			return;
		}
		wxString include = "from " + headerVal + " import " + nameVal;
		std::vector< wxString >::iterator it = std::find( headerIncludes->begin(), headerIncludes->end(), include );
		if ( headerIncludes->end() == it )
		{
			headerIncludes->push_back( include );
		}
	}
}

void PythonCodeGenerator::GenIncludes( PObjectBase project,
										std::vector<wxString>* includes, std::set< wxString >* templates )
{
	GenObjectIncludes( project, includes, templates );
}

void PythonCodeGenerator::GenObjectIncludes( PObjectBase project,
										std::vector< wxString >* includes, std::set< wxString >* templates )
{
	// Fill the set
	PCodeInfo code_info = project->GetObjectInfo()->GetCodeInfo("Python");
	if (code_info)
	{
		PythonTemplateParser parser( project, code_info->GetTemplate("include"), m_i18n, m_useRelativePath, m_basePath );
		wxString include = parser.ParseTemplate();
		if ( !include.empty() )
		{
			if ( templates->insert( include ).second )
			{
				AddUniqueIncludes( include, includes );
			}
		}
	}
	// Call GenIncludes on all children as well
	for ( unsigned int i = 0; i < project->GetChildCount(); i++ )
	{
		GenObjectIncludes( project->GetChild(i), includes, templates );
	}
	// Generate includes for base classes
	GenBaseIncludes( project->GetObjectInfo(), project, includes, templates );
}

void PythonCodeGenerator::GenBaseIncludes( PObjectInfo info, PObjectBase obj, std::vector< wxString >* includes, std::set< wxString >* templates )
{
	if ( !info )
	{
		return;
	}
	// Process all the base classes recursively
	for ( unsigned int i = 0; i < info->GetBaseClassCount(); i++ )
	{
		PObjectInfo base_info = info->GetBaseClass( i );
		GenBaseIncludes( base_info, obj, includes, templates );
	}
	PCodeInfo code_info = info->GetCodeInfo("Python");
	if ( code_info )
	{
		PythonTemplateParser parser( obj, code_info->GetTemplate("include"), m_i18n, m_useRelativePath, m_basePath );
		wxString include = parser.ParseTemplate();
		if ( !include.empty() )
		{
			if ( templates->insert( include ).second )
			{
				AddUniqueIncludes( include, includes );
			}
		}
	}
}

void PythonCodeGenerator::AddUniqueIncludes( const wxString& include, std::vector< wxString >* includes )
{
	// Split on newlines to only generate unique include lines
	// This strips blank lines and trims
	wxStringTokenizer tkz( include, "\n", wxTOKEN_STRTOK );

	while ( tkz.HasMoreTokens() )
	{
		wxString line = tkz.GetNextToken();
		line.Trim( false );
		line.Trim( true );

		// If it is not an include line, it will be written
		if ( !line.StartsWith("import") )
		{
			includes->push_back( line );
			continue;
		}
		// If it is an include, it must be unique to be written
		std::vector< wxString >::iterator it = std::find( includes->begin(), includes->end(), line );
		if ( includes->end() == it )
		{
			includes->push_back( line );
		}
	}
}

void PythonCodeGenerator::FindDependencies( PObjectBase obj, std::set< PObjectInfo >& info_set )
{
	unsigned int ch_count = obj->GetChildCount();
	if (ch_count > 0)
	{
		unsigned int i;
		for (i = 0; i<ch_count; i++)
		{
			PObjectBase child = obj->GetChild(i);
			info_set.insert(child->GetObjectInfo());
			FindDependencies(child, info_set);
		}
	}
}

void PythonCodeGenerator::GenConstructor( PObjectBase class_obj, const EventVector &events )
{
	m_source->WriteLn();
	// Generate function definition
	m_source->WriteLn( GetCode( class_obj, "cons_def" ) );
	m_source->Indent();

	m_source->WriteLn( GetCode( class_obj, "cons_call" ) );
	m_source->WriteLn();

	wxString settings = GetCode( class_obj, "settings" );
	if ( !settings.IsEmpty() )
	{
		m_source->WriteLn( settings );
	}
	for ( unsigned int i = 0; i < class_obj->GetChildCount(); i++ )
	{
		GenConstruction( class_obj->GetChild( i ), true );
	}
	wxString afterAddChild = GetCode( class_obj, "after_addchild" );
    if ( !afterAddChild.IsEmpty() )
    {
        m_source->WriteLn( afterAddChild );
    }
	GenEvents( class_obj, events );

	m_source->Unindent();
}

void PythonCodeGenerator::GenDestructor( PObjectBase class_obj, const EventVector &events )
{
	m_source->WriteLn();
	// generate function definition
	m_source->WriteLn("def __del__( self ):");
	m_source->Indent();

	if ( m_disconnectEvents && !events.empty() )
	{
		GenEvents( class_obj, events, true );
	}
	else
		m_source->WriteLn("pass");

	m_source->Unindent();
}

void PythonCodeGenerator::GenConstruction(PObjectBase obj, bool is_widget )
{
	wxString type = obj->GetObjectTypeName();
	PObjectInfo info = obj->GetObjectInfo();

	if ( ObjectDatabase::HasCppProperties( type ) )
	{
		m_source->WriteLn( GetCode( obj, "construction" ) );

		GenSettings( obj->GetObjectInfo(), obj );

		bool isWidget = !info->IsSubclassOf("sizer");

		for ( unsigned int i = 0; i < obj->GetChildCount(); i++ )
		{
			PObjectBase child = obj->GetChild( i );
			GenConstruction( child, isWidget );

			if ( type == "toolbar" )
			{
				GenAddToolbar(child->GetObjectInfo(), child);
			}
		}

		if ( !isWidget ) // sizers
		{
			if (is_widget)
			{
				// the parent object is not a sizer. There is no template for
				// this so we'll make it manually.
				// It's not a good practice to embed templates into the source code,
				// because you will need to recompile...

				wxString _template = 	"#wxparent $name.SetSizer( $name ) #nl"
										"#wxparent $name.Layout()"
										"#ifnull #parent $size"
										"@{ #nl $name.Fit( #wxparent $name ) @}";

				PythonTemplateParser parser( obj, _template, m_i18n, m_useRelativePath, m_basePath );
				m_source->WriteLn(parser.ParseTemplate());
			}
		}
		else if ( type == "splitter" )
		{
			// Generating the split
			switch ( obj->GetChildCount() )
			{
				case 1:
				{
					PObjectBase sub1 = obj->GetChild(0)->GetChild(0);
					wxString _template = "self.$name.Initialize( ";
					_template = _template + "self." + sub1->GetProperty("name")->GetValue() + " )";

					PythonTemplateParser parser( obj, _template, m_i18n, m_useRelativePath, m_basePath );
					m_source->WriteLn(parser.ParseTemplate());
					break;
				}
				case 2:
				{
					PObjectBase sub1,sub2;
					sub1 = obj->GetChild(0)->GetChild(0);
					sub2 = obj->GetChild(1)->GetChild(0);

					wxString _template;
					if ( obj->GetProperty("splitmode")->GetValue() == "wxSPLIT_VERTICAL" )
					{
						_template = "self.$name.SplitVertically( ";
					}
					else
					{
						_template = "self.$name.SplitHorizontally( ";
					}

					_template = _template + "self." + sub1->GetProperty( "name" )->GetValue() +
						", self." + sub2->GetProperty( "name" )->GetValue() + ", $sashpos )";

					PythonTemplateParser parser( obj, _template, m_i18n, m_useRelativePath, m_basePath );
					m_source->WriteLn(parser.ParseTemplate());
					break;
				}
				default:
					wxLogError( _("Missing subwindows for wxSplitterWindow widget.") );
					break;
			}
		}
		else if ( 	type == "menubar"		||
					type == "menu"			||
					type == "submenu"		||
					type == "toolbar"		||
					type == "listbook"		||
					type == "notebook"		||
					type == "auinotebook"	||
					type == "treelistctrl"	||
					type == "flatnotebook"
			)
		{
			wxString afterAddChild = GetCode( obj, "after_addchild" );
			if ( !afterAddChild.empty() )
			{
				m_source->WriteLn( afterAddChild );
			}
			m_source->WriteLn();
		}
	}
	else if ( info->IsSubclassOf("sizeritembase") )
	{
		// The child must be added to the sizer having in mind the
		// child object type (there are 3 different routines)
		GenConstruction( obj->GetChild(0), false );

		PObjectInfo childInfo = obj->GetChild(0)->GetObjectInfo();
		wxString temp_name;
		if ( childInfo->IsSubclassOf("wxWindow") || "CustomControl" == childInfo->GetClassName() )
		{
			temp_name = "window_add";
		}
		else if ( childInfo->IsSubclassOf( "sizer" ) )
		{
			temp_name = "sizer_add";
		}
		else if ( childInfo->GetClassName() == "spacer" )
		{
			temp_name = "spacer_add";
		}
		else
		{
			Debug::Print( _("SizerItem child is not a Spacer and is not a subclass of wxWindow or of sizer.") );
			return;
		}

		m_source->WriteLn( GetCode( obj, temp_name ) );
	}
	else if (   type == "notebookpage"		||
				type == "listbookpage"		||
				type == "choicebookpage"	||
				type == "auinotebookpage"	||
                type == "flatnotebookpage"
			)
	{
		GenConstruction( obj->GetChild( 0 ), false );
		m_source->WriteLn( GetCode( obj, "page_add" ) );
		GenSettings( obj->GetObjectInfo(), obj );
	}
	else if ( type == "toolbookpage" )
	{
		GenConstruction( obj->GetChild( 0 ), false );
		GenSettings( obj->GetObjectInfo(), obj );
		m_source->WriteLn( GetCode( obj, "page_add" ) );
	}
	else if ( type == "treebookpage" )
	{
		GenConstruction( obj->GetChild( 0 ), false );
		if ( obj->GetPropertyAsInteger("depth") == 0 )
		{
		    m_source->WriteLn( GetCode( obj, "page_add" ) );
		}
        else if ( obj->GetPropertyAsInteger("depth") > 0 )
        {
            m_source->WriteLn( GetCode( obj, "subpage_add" ) );
        }
		GenSettings( obj->GetObjectInfo(), obj );
	}
	else if ( type == "treelistctrlcolumn" )
	{
		m_source->WriteLn( GetCode( obj, "column_add" ) );
		GenSettings( obj->GetObjectInfo(), obj );
	}
	else if ( type == "tool" )
	{
		// If loading bitmap from ICON resource, and size is not set, set size to toolbars bitmapsize
		// So hacky, yet so useful ...
		wxSize toolbarsize = obj->GetParent()->GetPropertyAsSize("bitmapsize");
		if ( wxDefaultSize != toolbarsize )
		{
			PProperty prop = obj->GetProperty("bitmap");
			if ( prop )
			{
				wxString oldVal = prop->GetValueAsString();
				wxString path, source;
				wxSize toolsize;
				TypeConv::ParseBitmapWithResource( oldVal, &path, &source, &toolsize );
				if ( "Load From Icon Resource" == source && wxDefaultSize == toolsize )
				{
					prop->SetValue( wxString::Format( 	"%s; %s [%i; %i]", path.c_str(), source.c_str(),
														toolbarsize.GetWidth(), toolbarsize.GetHeight() ) );
					m_source->WriteLn( GetCode( obj, "construction" ) );
					prop->SetValue( oldVal );
					return;
				}
			}
		}
		m_source->WriteLn( GetCode( obj, "construction" ) );
	}
	else
	{
		// Generate the children
		for ( unsigned int i = 0; i < obj->GetChildCount(); i++ )
		{
			GenConstruction( obj->GetChild( i ), false );
		}
	}
}

void PythonCodeGenerator::FindMacros( PObjectBase obj, std::vector<wxString>* macros )
{
	// Iterate through all of the properties of all objects, add the macros
	// to the vector
	unsigned int i;
	for ( i = 0; i < obj->GetPropertyCount(); i++ )
	{
		PProperty prop = obj->GetProperty( i );
		if ( prop->GetType() == PT_MACRO )
		{
			wxString value = prop->GetValue();
			if( value.IsEmpty() ) continue;

			//if ( value.Contains("wx") && !value.Contains("wx.") ) value.Replace( "wx", "wx." );
			value.Replace( "wx", "wx." );

			// Skip wx IDs
            if ( m_predMacros.end() == m_predMacros.find( value ) )
            {
                if ( macros->end() == std::find( macros->begin(), macros->end(), value ) )
                {
                    macros->push_back( value );
                }
            }
		}
	}
	for ( i = 0; i < obj->GetChildCount(); i++ )
	{
		FindMacros( obj->GetChild( i ), macros );
	}
}

void PythonCodeGenerator::FindEventHandlers(PObjectBase obj, EventVector &events)
{
  unsigned int i;
  for (i=0; i < obj->GetEventCount(); i++)
  {
    PEvent event = obj->GetEvent(i);
    if (!event->GetValue().IsEmpty())
      events.push_back(event);
  }
  for (i=0; i < obj->GetChildCount(); i++)
  {
    PObjectBase child = obj->GetChild(i);
    FindEventHandlers(child,events);
  }
}

void PythonCodeGenerator::GenDefines( PObjectBase project)
{
	std::vector< wxString > macros;
	FindMacros( project, &macros );

	// Remove the default macro from the set, for backward compatiblity
	std::vector< wxString >::iterator it;
	it = std::find( macros.begin(), macros.end(), "ID_DEFAULT" );
	if ( it != macros.end() )
	{
		// The default macro is defined to wxID_ANY
		m_source->WriteLn( "ID_DEFAULT = wx.ID_ANY # Default" );
		macros.erase(it);
	}
	unsigned int id = m_firstID;
	if ( id < 1000 )
	{
		wxLogWarning( _("First ID is Less than 1000") );
	}
	for (it = macros.begin() ; it != macros.end(); it++)
	{
	    // Don't redefine wx IDs
        m_source->WriteLn( wxString::Format( "%s = %i", it->c_str(), id ) );
        id++;
	}
	if ( !macros.empty() ) m_source->WriteLn("");
}

void PythonCodeGenerator::GenSettings(PObjectInfo info, PObjectBase obj)
{
	wxString _template;
	PCodeInfo code_info = info->GetCodeInfo("Python");

	if ( !code_info )
	{
		return;
	}
	_template = code_info->GetTemplate("settings");

	if ( !_template.empty() )
	{
		PythonTemplateParser parser( obj, _template, m_i18n, m_useRelativePath, m_basePath );
		wxString code = parser.ParseTemplate();
		if ( !code.empty() )
		{
			m_source->WriteLn(code);
		}
	}
	// Proceeding recursively with the base classes
	for (unsigned int i=0; i< info->GetBaseClassCount(); i++)
	{
		PObjectInfo base_info = info->GetBaseClass(i);
		GenSettings(base_info,obj);
	}
}

void PythonCodeGenerator::GenAddToolbar( PObjectInfo info, PObjectBase obj )
{
	wxArrayString arrCode;
	
	GetAddToolbarCode( info, obj, arrCode );
	
	for( size_t i = 0; i < arrCode.GetCount(); i++ ) m_source->WriteLn( arrCode[i] );
}

void PythonCodeGenerator::GetAddToolbarCode( PObjectInfo info, PObjectBase obj, wxArrayString& codelines )
{
	wxString _template;
	PCodeInfo code_info = info->GetCodeInfo( wxT( "Python" ) );

	if ( !code_info )
		return;

	_template = code_info->GetTemplate( wxT( "toolbar_add" ) );

	if ( !_template.empty() )
	{
		PythonTemplateParser parser( obj, _template, m_i18n, m_useRelativePath, m_basePath );
		wxString code = parser.ParseTemplate();
		if ( !code.empty() )
		{
			if( codelines.Index( code ) == wxNOT_FOUND ) codelines.Add( code );
		}
	}
	
	// Proceeding recursively with the base classes
	for ( unsigned int i = 0; i < info->GetBaseClassCount(); i++ )
	{
		PObjectInfo base_info = info->GetBaseClass( i );
		GetAddToolbarCode( base_info, obj, codelines );
	}
}
///////////////////////////////////////////////////////////////////////

void PythonCodeGenerator::UseRelativePath(bool relative, wxString basePath)
{
	bool result;
	m_useRelativePath = relative;

	if (m_useRelativePath)
	{
		result = wxFileName::DirExists( basePath );
		m_basePath = ( result ? basePath : "" );
	}
}
/*
wxString CppCodeGenerator::ConvertToRelativePath(wxString path, wxString basePath)
{
	wxString auxPath = path;
	if ( basePath != "" )
	{
		wxFileName filename( _WXSTR( auxPath ) );
		if ( filename.MakeRelativeTo( _WXSTR( basePath ) ) )
		auxPath = _STDSTR( filename.GetFullPath() );
	}
	return auxPath;
}*/
// TODO: Check these ones
#define ADD_PREDEFINED_MACRO(x) m_predMacros.insert(#x)
#define ADD_PREDEFINED_PREFIX(k, v) m_predModulePrefix[ #k ] = #v

void PythonCodeGenerator::SetupPredefinedMacros()
{
    /* no id matches this one when compared to it */
    ADD_PREDEFINED_MACRO(wx.ID_NONE);

    /*  id for a separator line in the menu (invalid for normal item) */
    ADD_PREDEFINED_MACRO(wx.ID_SEPARATOR);

    ADD_PREDEFINED_MACRO(wx.ID_ANY);

	ADD_PREDEFINED_MACRO(wx.ID_LOWEST);

	ADD_PREDEFINED_MACRO(wx.ID_OPEN);
	ADD_PREDEFINED_MACRO(wx.ID_CLOSE);
	ADD_PREDEFINED_MACRO(wx.ID_NEW);
	ADD_PREDEFINED_MACRO(wx.ID_SAVE);
	ADD_PREDEFINED_MACRO(wx.ID_SAVEAS);
	ADD_PREDEFINED_MACRO(wx.ID_REVERT);
	ADD_PREDEFINED_MACRO(wx.ID_EXIT);
	ADD_PREDEFINED_MACRO(wx.ID_UNDO);
	ADD_PREDEFINED_MACRO(wx.ID_REDO);
	ADD_PREDEFINED_MACRO(wx.ID_HELP);
	ADD_PREDEFINED_MACRO(wx.ID_PRINT);
	ADD_PREDEFINED_MACRO(wx.ID_PRINT_SETUP);
	ADD_PREDEFINED_MACRO(wx.ID_PREVIEW);
	ADD_PREDEFINED_MACRO(wx.ID_ABOUT);
	ADD_PREDEFINED_MACRO(wx.ID_HELP_CONTENTS);
	ADD_PREDEFINED_MACRO(wx.ID_HELP_COMMANDS);
	ADD_PREDEFINED_MACRO(wx.ID_HELP_PROCEDURES);
	ADD_PREDEFINED_MACRO(wx.ID_HELP_CONTEXT);
	ADD_PREDEFINED_MACRO(wx.ID_CLOSE_ALL);
    ADD_PREDEFINED_MACRO(wx.ID_PAGE_SETUP);
    ADD_PREDEFINED_MACRO(wx.ID_HELP_INDEX);
    ADD_PREDEFINED_MACRO(wx.ID_HELP_SEARCH);
    ADD_PREDEFINED_MACRO(wx.ID_PREFERENCES);

    ADD_PREDEFINED_MACRO(wx.ID_EDIT);
	ADD_PREDEFINED_MACRO(wx.ID_CUT);
	ADD_PREDEFINED_MACRO(wx.ID_COPY);
	ADD_PREDEFINED_MACRO(wx.ID_PASTE);
	ADD_PREDEFINED_MACRO(wx.ID_CLEAR);
	ADD_PREDEFINED_MACRO(wx.ID_FIND);

	ADD_PREDEFINED_MACRO(wx.ID_DUPLICATE);
	ADD_PREDEFINED_MACRO(wx.ID_SELECTALL);
	ADD_PREDEFINED_MACRO(wx.ID_DELETE);
	ADD_PREDEFINED_MACRO(wx.ID_REPLACE);
	ADD_PREDEFINED_MACRO(wx.ID_REPLACE_ALL);
	ADD_PREDEFINED_MACRO(wx.ID_PROPERTIES);

	ADD_PREDEFINED_MACRO(wx.ID_VIEW_DETAILS);
	ADD_PREDEFINED_MACRO(wx.ID_VIEW_LARGEICONS);
	ADD_PREDEFINED_MACRO(wx.ID_VIEW_SMALLICONS);
	ADD_PREDEFINED_MACRO(wx.ID_VIEW_LIST);
	ADD_PREDEFINED_MACRO(wx.ID_VIEW_SORTDATE);
	ADD_PREDEFINED_MACRO(wx.ID_VIEW_SORTNAME);
	ADD_PREDEFINED_MACRO(wx.ID_VIEW_SORTSIZE);
	ADD_PREDEFINED_MACRO(wx.ID_VIEW_SORTTYPE);

    ADD_PREDEFINED_MACRO(wx.ID_FILE);
	ADD_PREDEFINED_MACRO(wx.ID_FILE1);
	ADD_PREDEFINED_MACRO(wx.ID_FILE2);
	ADD_PREDEFINED_MACRO(wx.ID_FILE3);
	ADD_PREDEFINED_MACRO(wx.ID_FILE4);
	ADD_PREDEFINED_MACRO(wx.ID_FILE5);
	ADD_PREDEFINED_MACRO(wx.ID_FILE6);
	ADD_PREDEFINED_MACRO(wx.ID_FILE7);
	ADD_PREDEFINED_MACRO(wx.ID_FILE8);
	ADD_PREDEFINED_MACRO(wx.ID_FILE9);

	/*  Standard button and menu IDs */

	ADD_PREDEFINED_MACRO(wx.ID_OK);
	ADD_PREDEFINED_MACRO(wx.ID_CANCEL);

	ADD_PREDEFINED_MACRO(wx.ID_APPLY);
	ADD_PREDEFINED_MACRO(wx.ID_YES);
	ADD_PREDEFINED_MACRO(wx.ID_NO);
	ADD_PREDEFINED_MACRO(wx.ID_STATIC);
	ADD_PREDEFINED_MACRO(wx.ID_FORWARD);
	ADD_PREDEFINED_MACRO(wx.ID_BACKWARD);
	ADD_PREDEFINED_MACRO(wx.ID_DEFAULT);
	ADD_PREDEFINED_MACRO(wx.ID_MORE);
	ADD_PREDEFINED_MACRO(wx.ID_SETUP);
	ADD_PREDEFINED_MACRO(wx.ID_RESET);
	ADD_PREDEFINED_MACRO(wx.ID_CONTEXT_HELP);
	ADD_PREDEFINED_MACRO(wx.ID_YESTOALL);
	ADD_PREDEFINED_MACRO(wx.ID_NOTOALL);
	ADD_PREDEFINED_MACRO(wx.ID_ABORT);
	ADD_PREDEFINED_MACRO(wx.ID_RETRY);
	ADD_PREDEFINED_MACRO(wx.ID_IGNORE);
    ADD_PREDEFINED_MACRO(wx.ID_ADD);
    ADD_PREDEFINED_MACRO(wx.ID_REMOVE);

	ADD_PREDEFINED_MACRO(wx.ID_UP);
	ADD_PREDEFINED_MACRO(wx.ID_DOWN);
	ADD_PREDEFINED_MACRO(wx.ID_HOME);
	ADD_PREDEFINED_MACRO(wx.ID_REFRESH);
	ADD_PREDEFINED_MACRO(wx.ID_STOP);
	ADD_PREDEFINED_MACRO(wx.ID_INDEX);

	ADD_PREDEFINED_MACRO(wx.ID_BOLD);
	ADD_PREDEFINED_MACRO(wx.ID_ITALIC);
	ADD_PREDEFINED_MACRO(wx.ID_JUSTIFY_CENTER);
	ADD_PREDEFINED_MACRO(wx.ID_JUSTIFY_FILL);
	ADD_PREDEFINED_MACRO(wx.ID_JUSTIFY_RIGHT);

	ADD_PREDEFINED_MACRO(wx.ID_JUSTIFY_LEFT);
	ADD_PREDEFINED_MACRO(wx.ID_UNDERLINE);
	ADD_PREDEFINED_MACRO(wx.ID_INDENT);
	ADD_PREDEFINED_MACRO(wx.ID_UNINDENT);
	ADD_PREDEFINED_MACRO(wx.ID_ZOOM_100);
	ADD_PREDEFINED_MACRO(wx.ID_ZOOM_FIT);
	ADD_PREDEFINED_MACRO(wx.ID_ZOOM_IN);
	ADD_PREDEFINED_MACRO(wx.ID_ZOOM_OUT);
	ADD_PREDEFINED_MACRO(wx.ID_UNDELETE);
	ADD_PREDEFINED_MACRO(wx.ID_REVERT_TO_SAVED);

	/*  System menu IDs (used by wxUniv): */
    ADD_PREDEFINED_MACRO(wx.ID_SYSTEM_MENU);
	ADD_PREDEFINED_MACRO(wx.ID_CLOSE_FRAME);
	ADD_PREDEFINED_MACRO(wx.ID_MOVE_FRAME);
	ADD_PREDEFINED_MACRO(wx.ID_RESIZE_FRAME);
	ADD_PREDEFINED_MACRO(wx.ID_MAXIMIZE_FRAME);
	ADD_PREDEFINED_MACRO(wx.ID_ICONIZE_FRAME);
	ADD_PREDEFINED_MACRO(wx.ID_RESTORE_FRAME);

	/*  IDs used by generic file dialog (13 consecutive starting from this value) */
	ADD_PREDEFINED_MACRO(wx.ID_FILEDLGG);

	ADD_PREDEFINED_MACRO(wx.ID_HIGHEST);
}

void PythonTemplateParser::SetupModulePrefixes()
{
	// altered class names
	ADD_PREDEFINED_PREFIX( wxCalendarCtrl, wx.calendar. );
	ADD_PREDEFINED_PREFIX( wxRichTextCtrl, wx.richtext. );
	ADD_PREDEFINED_PREFIX( wxHtmlWindow, wx.html. );
	ADD_PREDEFINED_PREFIX( wxAuiNotebook, wx.aui. );
	ADD_PREDEFINED_PREFIX( wxGrid, wx.grid. );
	ADD_PREDEFINED_PREFIX( wxAnimationCtrl, wx.animate. );

	// altered macros
	ADD_PREDEFINED_PREFIX( wxCAL_SHOW_HOLIDAYS, wx.calendar. );
	ADD_PREDEFINED_PREFIX( wxCAL_MONDAY_FIRST, wx.calendar. );
	ADD_PREDEFINED_PREFIX( wxCAL_NO_MONTH_CHANGE, wx.calendar. );
	ADD_PREDEFINED_PREFIX( wxCAL_NO_YEAR_CHANGE, wx.calendar. );
	ADD_PREDEFINED_PREFIX( wxCAL_SEQUENTIAL_MONTH_SELECTION, wx.calendar. );
	ADD_PREDEFINED_PREFIX( wxCAL_SHOW_SURROUNDING_WEEKS, wx.calendar. );
	ADD_PREDEFINED_PREFIX( wxCAL_SUNDAY_FIRST, wx.calendar. );

	ADD_PREDEFINED_PREFIX( wxHW_DEFAULT_STYLE, wx.html. );
	ADD_PREDEFINED_PREFIX( wxHW_NO_SELECTION, wx.html. );
	ADD_PREDEFINED_PREFIX( wxHW_SCROLLBAR_AUTO, wx.html. );
	ADD_PREDEFINED_PREFIX( wxHW_SCROLLBAR_NEVER, wx.html. );

	ADD_PREDEFINED_PREFIX( wxAUI_NB_BOTTOM, wx.aui. );
	ADD_PREDEFINED_PREFIX( wxAUI_NB_CLOSE_BUTTON, wx.aui. );
	ADD_PREDEFINED_PREFIX( wxAUI_NB_CLOSE_ON_ACTIVE_TAB, wx.aui. );
	ADD_PREDEFINED_PREFIX( wxAUI_NB_CLOSE_ON_ALL_TABS, wx.aui. );
	ADD_PREDEFINED_PREFIX( wxAUI_NB_DEFAULT_STYLE, wx.aui. );
	ADD_PREDEFINED_PREFIX( wxAUI_NB_LEFT, wx.aui. );
	ADD_PREDEFINED_PREFIX( wxAUI_NB_MIDDLE_CLICK_CLOSE, wx.aui. );
	ADD_PREDEFINED_PREFIX( wxAUI_NB_RIGHT, wx.aui. );
	ADD_PREDEFINED_PREFIX( wxAUI_NB_SCROLL_BUTTONS, wx.aui. );
	ADD_PREDEFINED_PREFIX( wxAUI_NB_TAB_EXTERNAL_MOVE, wx.aui. );
	ADD_PREDEFINED_PREFIX( wxAUI_NB_TAB_FIXED_WIDTH, wx.aui. );
	ADD_PREDEFINED_PREFIX( wxAUI_NB_TAB_MOVE, wx.aui. );
	ADD_PREDEFINED_PREFIX( wxAUI_NB_TAB_SPLIT, wx.aui. );
	ADD_PREDEFINED_PREFIX( wxAUI_NB_TOP, wx.aui. );
	ADD_PREDEFINED_PREFIX( wxAUI_NB_WINDOWLIST_BUTTON, wx.aui. );

	ADD_PREDEFINED_PREFIX( wxAC_DEFAULT_STYLE, wx.animate. );
	ADD_PREDEFINED_PREFIX( wxAC_NO_AUTORESIZE, wx.animate. );
}
