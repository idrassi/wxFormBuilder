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

#include "xrcconv.h"
#include <wx/wx.h>
#include <wx/tokenzr.h>

#include <string>
#include <set>

#include <ticpp.h>

static wxString StringToXrcText( const wxString &str )
{
	wxString result;

	for ( unsigned int i = 0 ; i < str.Length() ; i++ )
	{
		wxChar c = str[i];
		switch ( c )
		{
			case wxChar( '\n' ): result = result + "\\n"; 	break;
			case wxChar( '\t' ): result = result + "\\t"; 	break;
			case wxChar( '\r' ): result = result + "\\r"; 	break;
			case wxChar( '\\' ): result = result + "\\\\"; 	break;
			case wxChar( '_' ):  result = result + "__"; 	break;
			case wxChar( '&' ):  result = result + "_"; 	break;
			default:
			{
				result = result + c;
				break;
			}
		}
	}
	return result;
}

static wxString XrcTextToString( const wxString &str )
{
	wxString result;
	for ( unsigned int i = 0 ; i < str.Length() ; i++ )
	{
		wxChar c = str[i];
		if ( c == wxChar( '\\' ) && i < str.length() - 1 )
		{
			wxChar next = str[i+1];
			switch ( next )
			{
				case wxChar( 'n' ): result = result + wxChar( '\n' ); i++; 	break;
				case wxChar( 't' ): result = result + wxChar( '\t' ); i++; 	break;
				case wxChar( 'r' ): result = result + wxChar( '\r' ); i++; 	break;
				case wxChar( '\\' ): result = result + wxChar( '\\' ); i++; break;
			}
		}
		else if ( c == wxChar( '_' ) )
		{
			if ( i < str.Length() - 1 && str[i+1] == wxChar( '_' ) )
			{
				result = result + wxChar( '_' );
				i++;
			}
			else
			{
				result = result + wxChar( '&' );
			}
		}
		else
		{
			result = result + c;
		}
	}
	return result;
}

static wxString ReplaceSynonymous( const wxString &bitlist )
{
	IComponentLibrary* lib = GetComponentLibrary( NULL );
	wxString result, translation;
	wxStringTokenizer tkz( bitlist, "|" );
	while ( tkz.HasMoreTokens() )
	{
		wxString token;
		token = tkz.GetNextToken();
		token.Trim( true );
		token.Trim( false );

		if ( result != "" )
		{
			result = result + wxChar( '|' );
		}
		if ( lib->FindSynonymous( token, translation ) )
		{
			result += translation;
		}
		else
		{
			result += token;
		}
	}
	delete lib;
	return result;
}

ObjectToXrcFilter::ObjectToXrcFilter(IObject *obj,
									const wxString &classname,
									const wxString &objname,
									const wxString &base )
{
	m_obj = obj;
	m_xrcObj = new ticpp::Element( "object" );
	m_xrcObj->SetAttribute( "class", classname.mb_str( wxConvUTF8 ) );

	if ( objname != "" )
	{
		m_xrcObj->SetAttribute( "name", objname.mb_str( wxConvUTF8 ) );
	}
	if ( base != "" )
	{
		m_xrcObj->SetAttribute( "base", base.mb_str( wxConvUTF8 ) );
	}
}

ObjectToXrcFilter::~ObjectToXrcFilter()
{
	delete m_xrcObj;
}

void ObjectToXrcFilter::AddProperty( const wxString &objPropName,
                                     const wxString &xrcPropName,
                                     const int &propType )
{
	std::string name( xrcPropName.mb_str( wxConvUTF8 ) );
	ticpp::Element propElement( name );

	switch ( propType )
	{
		case XRC_TYPE_SIZE:
		case XRC_TYPE_POINT:
		case XRC_TYPE_BITLIST:
			LinkText( m_obj->GetPropertyAsString( objPropName ), &propElement );
			break;

		case XRC_TYPE_TEXT:
			// The text must be converted to XRC format
			{
				wxString text = m_obj->GetPropertyAsString( objPropName );
				LinkText( text, &propElement, true );
			}
			break;

		case XRC_TYPE_BOOL:
		case XRC_TYPE_INTEGER:
		{
			LinkInteger( m_obj->GetPropertyAsInteger( objPropName ), &propElement );
			break;
		}
		case XRC_TYPE_FLOAT:
		{
			LinkFloat( m_obj->GetPropertyAsFloat( objPropName ), &propElement );
			break;
		}
		case XRC_TYPE_COLOUR:
		{
			LinkColour( m_obj->GetPropertyAsColour( objPropName ), &propElement );
			break;
		}
		case XRC_TYPE_FONT:
		{
			LinkFont( m_obj->GetPropertyAsFont( objPropName ), &propElement );
			break;
		}
		case XRC_TYPE_STRINGLIST:
		{
			LinkStringList( m_obj->GetPropertyAsArrayString( objPropName ), &propElement );
			break;
		}
		case XRC_TYPE_BITMAP:
		{
			wxString bitmapProp = m_obj->GetPropertyAsString( objPropName );
			if ( bitmapProp.empty() )
			{
				break;
			}

			wxString filename = bitmapProp.BeforeFirst( ';' );
			if ( filename.empty() )
			{
				break;
			}

			if ( bitmapProp.size() < ( filename.size() + 2 ) )
			{
				break;
			}

			wxString source = bitmapProp.substr( filename.size() + 2 );
			if ( source.StartsWith( "Load From File" ) )
			{
				LinkText( filename, &propElement );
			}
		}
		break;
	}
	m_xrcObj->LinkEndChild( &propElement );
}

void ObjectToXrcFilter::AddPropertyValue (	const wxString &xrcPropName,
											const wxString &xrcPropValue,
											bool xrcFormat )
{
	ticpp::Element propElement( xrcPropName.mb_str( wxConvUTF8 ) );
	LinkText( xrcPropValue, &propElement, xrcFormat );
	m_xrcObj->LinkEndChild( &propElement );
}

void ObjectToXrcFilter::AddPropertyPair ( const wxString& objPropName1, const wxString& objPropName2, const wxString& xrcPropName )
{
	AddPropertyValue(	xrcPropName,
						wxString::Format("%d,%d",
										m_obj->GetPropertyAsInteger( objPropName1 ),
										m_obj->GetPropertyAsInteger( objPropName2 ) ) );
}

ticpp::Element* ObjectToXrcFilter::GetXrcObject()
{
	return new ticpp::Element( *m_xrcObj );
}

void ObjectToXrcFilter::LinkText( const wxString &text, ticpp::Element *propElement, bool xrcFormat )
{
	wxString value = ( xrcFormat ? StringToXrcText( text ) : text );
	propElement->SetText( value.mb_str( wxConvUTF8 ) );
}

void ObjectToXrcFilter::LinkInteger( const int &integer, ticpp::Element *propElement )
{
	propElement->SetText( integer );
}

void ObjectToXrcFilter::LinkFloat( const double& value, ticpp::Element* propElement )
{
	propElement->SetText( value );
}

void ObjectToXrcFilter::LinkColour( const wxColour &colour, ticpp::Element *propElement )
{
	wxString value = wxString::Format( "#%02x%02x%02x", colour.Red(), colour.Green(), colour.Blue() );
	propElement->SetText( value.mb_str( wxConvUTF8 ) );
}

void ObjectToXrcFilter::LinkFont( const wxFontContainer &font, ticpp::Element *propElement )
{
	if ( font.GetPointSize() > 0 )
	{
		wxString aux;
		aux.Printf( "%d", font.GetPointSize() );

		ticpp::Element size( "size" );
		size.SetText( aux.mb_str( wxConvUTF8 ) );
		propElement->LinkEndChild( &size );
	}

	ticpp::Element family( "family" );
	switch ( font.GetFamily() )
	{
		case wxFONTFAMILY_DECORATIVE:
		{
			family.SetText( "decorative" );
			break;
		}
		case wxFONTFAMILY_ROMAN:
		{
			family.SetText( "roman" );
			break;
		}
		case wxFONTFAMILY_SWISS:
		{
			family.SetText( "swiss" );
			break;
		}
		case wxFONTFAMILY_SCRIPT:
		{
			family.SetText( "script" );
			break;
		}
		case wxFONTFAMILY_MODERN:
		{
			family.SetText( "modern" );
			break;
		}
		case wxFONTFAMILY_TELETYPE:
		{
			family.SetText( "teletype" );
			break;
		}
		default:
		{
			family.SetText( "default" );
			break;
		}
	}
	propElement->LinkEndChild( &family );

	ticpp::Element style( "style" );
	switch ( font.GetStyle() )
	{
		case wxFONTSTYLE_SLANT:
		{
			style.SetText( "slant" );
			break;
		}
		case wxFONTSTYLE_ITALIC:
		{
			style.SetText( "italic" );
			break;
		}
		default:
		{
			style.SetText( "normal" );
			break;
		}
	}
	propElement->LinkEndChild( &style );

	ticpp::Element weight( "weight" );
	switch ( font.GetWeight() )
	{
		case wxFONTWEIGHT_LIGHT:
		{
			weight.SetText( "light" );
			break;
		}
		case wxFONTWEIGHT_BOLD:
		{
			weight.SetText( "bold" );
			break;
		}
		default:
		{
			weight.SetText( "normal" );
			break;
		}
	}
	propElement->LinkEndChild( &weight );

	ticpp::Element underlined( "underlined" );
	underlined.SetText( font.GetUnderlined() ? "1" : "0" );
	propElement->LinkEndChild( &underlined );

	if ( !font.GetFaceName().empty() )
	{
		ticpp::Element face( "face" );
		face.SetText( font.GetFaceName().mb_str( wxConvUTF8 ) );
		propElement->LinkEndChild( &face );
	}
}

void ObjectToXrcFilter::LinkStringList( const wxArrayString &array, ticpp::Element *propElement, bool xrcFormat )
{
	for ( size_t i = 0; i < array.GetCount(); i++ )
	{
		wxString value = ( xrcFormat ? StringToXrcText( array[i] ) : array[i] );
		ticpp::Element item( "item" );
		item.SetText( value.mb_str( wxConvUTF8 ) );
		propElement->LinkEndChild( &item );
	}
}

void ObjectToXrcFilter::AddWindowProperties()
{
	wxString style;
	if ( !m_obj->IsNull("style") )
	{
		style = m_obj->GetPropertyAsString("style");
	}
	if ( !m_obj->IsNull("window_style" ) )
	{
		if ( !style.IsEmpty() )
		{
			style += '|';
		}
		style += m_obj->GetPropertyAsString("window_style");
	}
	if ( !style.IsEmpty() )
	{
		AddPropertyValue( "style", style );
	}
	wxString extraStyle;
	if ( !m_obj->IsNull("extra_style") )
	{
		extraStyle = m_obj->GetPropertyAsString("extra_style");
	}
	if ( !m_obj->IsNull("window_extra_style") )
	{
		if ( !extraStyle.IsEmpty() )
		{
			extraStyle += '|';
		}
		extraStyle += m_obj->GetPropertyAsString("window_extra_style");
	}
	if ( !extraStyle.IsEmpty() )
	{
		AddPropertyValue( "exstyle", extraStyle );
	}
	if ( !m_obj->IsNull("pos") ) 	{ AddProperty( "pos", "pos", XRC_TYPE_SIZE ); }
	if ( !m_obj->IsNull("size") ) 	{ AddProperty( "size", "size", XRC_TYPE_SIZE ); }
	if ( !m_obj->IsNull("bg") ) 	{ AddProperty( "bg", "bg", XRC_TYPE_COLOUR ); }
	if ( !m_obj->IsNull("fg") ) 	{ AddProperty( "fg", "fg", XRC_TYPE_COLOUR ); }

	if ( !m_obj->IsNull("enabled") && !m_obj->GetPropertyAsInteger("enabled") )
	{
		AddProperty( "enabled", "enabled", XRC_TYPE_BOOL );
	}
	if ( !m_obj->IsNull("focused" ) )
	{
		AddPropertyValue( "focused", "0" );
	}
	if ( !m_obj->IsNull("hidden") && m_obj->GetPropertyAsInteger("hidden") )
	{
		AddProperty( "hidden", "hidden", XRC_TYPE_BOOL );
	}
	if ( !m_obj->IsNull("font") )
	{
		AddProperty( "font", "font", XRC_TYPE_FONT );
	}
	if ( !m_obj->IsNull("tooltip") )
	{
		AddProperty( "tooltip", "tooltip", XRC_TYPE_TEXT );
	}
	if ( !m_obj->IsNull("subclass") )
	{
		wxString subclass = m_obj->GetChildFromParentProperty( "subclass", "name" );
		if ( !subclass.empty() )
		{
			m_xrcObj->SetAttribute( "subclass", subclass.mb_str( wxConvUTF8 ) );
		}
	}
};

///////////////////////////////////////////////////////////////////////////////

XrcToXfbFilter::XrcToXfbFilter( ticpp::Element *obj,
								const wxString &/*classname*/,
                                const wxString &objname )
{
	m_xrcObj = obj;
	m_xfbObj = new ticpp::Element( "object" );

	try
	{
		std::string name;
		obj->GetAttribute( "class", &name );
		m_xfbObj->SetAttribute( "class", name );
	}
	catch( ticpp::Exception& ex )
	{
		wxLogDebug( wxString( ex.m_details.c_str(), wxConvUTF8 ) );
	}
	if ( !objname.empty() )
	{
		AddProperty( "name", objname, XRC_TYPE_TEXT );
	}
}

XrcToXfbFilter::XrcToXfbFilter( ticpp::Element *obj, const wxString &classname )
{
	m_xrcObj = obj;
	m_xfbObj = new ticpp::Element( "object" );

	m_xfbObj->SetAttribute( "class", classname.mb_str( wxConvUTF8 ) );

	try
	{
		std::string name;
		obj->GetAttribute( "name", &name );
		wxString objname( name.c_str(), wxConvUTF8 );
		AddPropertyValue( "name", objname );
	}
	catch( ticpp::Exception& ex )
	{
		wxLogDebug( wxString( ex.m_details.c_str(), wxConvUTF8 ) );
	}
}

XrcToXfbFilter::~XrcToXfbFilter()
{
	delete m_xfbObj;
}


ticpp::Element* XrcToXfbFilter::GetXrcProperty( const wxString &name )
{
	return m_xrcObj->FirstChildElement( name.mb_str( wxConvUTF8 ) );
}

void XrcToXfbFilter::AddProperty( const wxString &xrcPropName,
                                  const wxString &xfbPropName,
                                  const int &propType )
{
	ticpp::Element propElement( "property" );
	propElement.SetAttribute( "name", xfbPropName.mb_str( wxConvUTF8 ) );

	switch ( propType )
	{
		case XRC_TYPE_SIZE:
		case XRC_TYPE_POINT:
		case XRC_TYPE_BOOL:
		{
			ImportTextProperty( xrcPropName, &propElement );
			break;
		}
		case XRC_TYPE_TEXT:
		{
			ImportTextProperty( xrcPropName, &propElement, true );
			break;
		}
		case XRC_TYPE_INTEGER:
		{
			ImportIntegerProperty( xrcPropName, &propElement );
			break;
		}
		case XRC_TYPE_FLOAT:
		{
			ImportFloatProperty( xrcPropName, &propElement );
			break;
		}
		case XRC_TYPE_BITLIST:
		{
			ImportBitlistProperty( xrcPropName, &propElement );
			break;
		}
		case XRC_TYPE_COLOUR:
		{
			ImportColourProperty( xrcPropName, &propElement );
			break;
		}
		case XRC_TYPE_FONT:
		{
			ImportFontProperty( xrcPropName, &propElement );
			break;
		}
		case XRC_TYPE_STRINGLIST:
		{
			ImportStringListProperty( xrcPropName, &propElement, true );
			break;
		}
		case XRC_TYPE_BITMAP:
		{
			ImportBitmapProperty( xrcPropName, &propElement );
			break;
		}
	}
	m_xfbObj->LinkEndChild( &propElement );
}

void XrcToXfbFilter::AddPropertyValue ( const wxString &xfbPropName,
                                        const wxString &xfbPropValue,
                                        bool parseXrcText )
{
	ticpp::Element propElement( "property" );
	propElement.SetAttribute( "name", xfbPropName.mb_str( wxConvUTF8 ) );
	wxString value = ( parseXrcText ? XrcTextToString( xfbPropValue ) : xfbPropValue );
	propElement.SetText( value.mb_str( wxConvUTF8 ) );
	m_xfbObj->LinkEndChild( &propElement );
}

void XrcToXfbFilter::AddStyleProperty()
{
	try
	{
		ticpp::Element *xrcProperty = m_xrcObj->FirstChildElement( "style" );

		wxString bitlist = wxString( xrcProperty->GetText().c_str(), wxConvUTF8 );
		bitlist = ReplaceSynonymous( bitlist );

		// FIXME: We should avoid hardcoding these things
		std::set< wxString > windowStyles;
		windowStyles.insert( "wxSIMPLE_BORDER" );
		windowStyles.insert( "wxDOUBLE_BORDER" );
		windowStyles.insert( "wxSUNKEN_BORDER" );
		windowStyles.insert( "wxRAISED_BORDER" );
		windowStyles.insert( "wxSTATIC_BORDER" );
		windowStyles.insert( "wxNO_BORDER" );
		windowStyles.insert( "wxTRANSPARENT_WINDOW" );
		windowStyles.insert( "wxTAB_TRAVERSAL" );
		windowStyles.insert( "wxWANTS_CHARS" );
		windowStyles.insert( "wxVSCROLL" );
		windowStyles.insert( "wxHSCROLL" );
		windowStyles.insert( "wxALWAYS_SHOW_SB" );
		windowStyles.insert( "wxCLIP_CHILDREN" );
		windowStyles.insert( "wxFULL_REPAINT_ON_RESIZE" );

		wxString style, windowStyle;
		wxStringTokenizer tkz( bitlist, " |" );
		while ( tkz.HasMoreTokens() )
		{
			wxString token;
			token = tkz.GetNextToken();
			token.Trim( true );
			token.Trim( false );

			if ( windowStyles.find( token ) == windowStyles.end() )
			{
				if ( !style.IsEmpty() ) style += _T( "|" );
				style += token;
			}
			else
			{
				if ( !windowStyle.IsEmpty() ) windowStyle += _T( "|" );
				windowStyle += token;
			}
		}
		if ( !style.empty() )
		{
			AddPropertyValue( "style", style );
		}
		AddPropertyValue( "window_style", windowStyle );
	}
	catch( ticpp::Exception& ex )
	{
		wxLogDebug( wxString( ex.m_details.c_str(), wxConvUTF8 ) );
	}
}

void XrcToXfbFilter::AddExtraStyleProperty()
{
	try
	{
		ticpp::Element *xrcProperty = m_xrcObj->FirstChildElement( "exstyle" );

		wxString bitlist = wxString( xrcProperty->GetText().c_str(), wxConvUTF8 );
		bitlist = ReplaceSynonymous( bitlist );

		// FIXME: We should avoid hardcoding these things
		std::set< wxString > windowStyles;
		windowStyles.insert( "wxWS_EX_VALIDATE_RECURSIVELY" );
		windowStyles.insert( "wxWS_EX_BLOCK_EVENTS" );
		windowStyles.insert( "wxWS_EX_TRANSIENT" );
		windowStyles.insert( "wxWS_EX_PROCESS_IDLE" );
		windowStyles.insert( "wxWS_EX_PROCESS_UI_UPDATES" );

		wxString style, windowStyle;
		wxStringTokenizer tkz( bitlist, " |" );
		while ( tkz.HasMoreTokens() )
		{
			wxString token;
			token = tkz.GetNextToken();
			token.Trim( true );
			token.Trim( false );

			if ( windowStyles.find( token ) == windowStyles.end() )
			{
				if ( !style.IsEmpty() ) style += _T( "|" );
				style += token;
			}
			else
			{
				if ( !windowStyle.IsEmpty() ) windowStyle += _T( "|" );
				windowStyle += token;
			}
		}
		if ( !style.empty() )
		{
			AddPropertyValue( "extra_style", style );
		}
		AddPropertyValue( "window_extra_style", windowStyle );
	}
	catch( ticpp::Exception& ex )
	{
		wxLogDebug( wxString( ex.m_details.c_str(), wxConvUTF8 ) );
	}
}

void XrcToXfbFilter::AddPropertyPair( const char* xrcPropName, const wxString& xfbPropName1, const wxString& xfbPropName2 )
{
	try
	{
		ticpp::Element* pairProp = m_xrcObj->FirstChildElement( xrcPropName );

		wxString width = wxEmptyString;
		wxString height = wxEmptyString;
		wxStringTokenizer tkz( wxString( pairProp->GetText().c_str(), wxConvUTF8 ), "," );
		if ( tkz.HasMoreTokens() )
		{
			width = tkz.GetNextToken();
			if ( tkz.HasMoreTokens() )
			{
				height = tkz.GetNextToken();
			}
		}
		AddPropertyValue( xfbPropName1, width );
		AddPropertyValue( xfbPropName2, height );
	}
	catch( ticpp::Exception& ex )
	{
		wxLogDebug( wxString( ex.m_details.c_str(), wxConvUTF8 ) );
	}
}

ticpp::Element* XrcToXfbFilter::GetXfbObject()
{
	return m_xfbObj->Clone().release()->ToElement();
}

//-----------------------------

void XrcToXfbFilter::ImportTextProperty(const wxString &xrcPropName,
										ticpp::Element *property,
										bool parseXrcText )
{
	try
	{
		ticpp::Element *xrcProperty = m_xrcObj->FirstChildElement( xrcPropName.mb_str( wxConvUTF8 ) );

		// Convert XRC text to normal text
		wxString value( wxString( xrcProperty->GetText().c_str(), wxConvUTF8 ) );

		if ( parseXrcText ) { value = XrcTextToString( value ); }

		property->SetText( value.mb_str( wxConvUTF8 ) );
	}
	catch( ticpp::Exception& ex )
	{
		wxLogDebug( wxString( ex.m_details.c_str(), wxConvUTF8 ) );
	}
}

void XrcToXfbFilter::ImportIntegerProperty( const wxString &xrcPropName, ticpp::Element *property )
{
	try
	{
		ticpp::Element *xrcProperty = m_xrcObj->FirstChildElement( xrcPropName.mb_str( wxConvUTF8 ) );
		property->SetText( xrcProperty->GetText() );
	}
	catch( ticpp::Exception& )
	{
		property->SetText( "0" );
	}
}

void XrcToXfbFilter::ImportFloatProperty( const wxString &xrcPropName, ticpp::Element *property )
{
	try
	{
		ticpp::Element *xrcProperty = m_xrcObj->FirstChildElement( xrcPropName.mb_str( wxConvUTF8 ) );
		property->SetText( xrcProperty->GetText() );
	}
	catch( ticpp::Exception& )
	{
		property->SetText( "0.0" );
	}
}

void XrcToXfbFilter::ImportBitlistProperty( const wxString &xrcPropName, ticpp::Element *property )
{
	try
	{
		ticpp::Element *xrcProperty = m_xrcObj->FirstChildElement( xrcPropName.mb_str( wxConvUTF8 ) );

		wxString bitlist = wxString( xrcProperty->GetText().c_str(), wxConvUTF8 );
		bitlist = ReplaceSynonymous( bitlist );
		property->SetText( bitlist.mb_str( wxConvUTF8 ) );
	}
	catch( ticpp::Exception& ex )
	{
		wxLogDebug( wxString( ex.m_details.c_str(), wxConvUTF8 ) );
	}
}

void XrcToXfbFilter::ImportFontProperty( const wxString &xrcPropName, ticpp::Element *property )
{
	try
	{
		ticpp::Element *xrcProperty = m_xrcObj->FirstChildElement( xrcPropName.mb_str( wxConvUTF8 ) );
		ticpp::Element *element;
		wxFontContainer font;

		// the size
		try
		{
			element = xrcProperty->FirstChildElement( "size" );
			long size;
			element->GetText( &size );
			font.SetPointSize( size );
		}
		catch( ticpp::Exception& ex )
		{
			wxLogDebug( wxString( ex.m_details.c_str(), wxConvUTF8 ) );
		}

		// the family
		try
		{
			element = xrcProperty->FirstChildElement( "family" );
			wxString family_str( element->GetText().c_str(), wxConvUTF8 );

			if ( family_str == "decorative" )
			{
				font.SetFamily( wxDECORATIVE );
			}
			else if ( family_str == "roman" )
			{
				font.SetFamily( wxROMAN );
			}
			else if ( family_str == "swiss" )
			{
				font.SetFamily( wxSWISS );
			}
			else if ( family_str == "script" )
			{
				font.SetFamily( wxSCRIPT );
			}
			else if ( family_str == "modern" )
			{
				font.SetFamily( wxMODERN );
			}
			else if ( family_str == "teletype" )
			{
				font.SetFamily( wxTELETYPE );
			}
			else
			{
				font.SetFamily( wxDEFAULT );
			}
		}
		catch( ticpp::Exception& )
		{
			font.SetFamily( wxDEFAULT );
		}

		// the style
		try
		{
			element = xrcProperty->FirstChildElement( "style" );
			wxString style_str( element->GetText().c_str(), wxConvUTF8 );

			if ( style_str == "slant" )
			{
				font.SetStyle( wxSLANT );
			}
			else if ( style_str == "italic" )
			{
				font.SetStyle( wxITALIC );
			}
			else
			{
				font.SetStyle( wxNORMAL );
			}
		}
		catch( ticpp::Exception& )
		{
			font.SetStyle( wxNORMAL );
		}

		// weight
		try
		{
			element = xrcProperty->FirstChildElement( "weight" );
			wxString weight_str( element->GetText().c_str(), wxConvUTF8 );

			if ( weight_str == "light" )
			{
				font.SetWeight( wxLIGHT );
			}
			else if ( weight_str == "bold" )
			{
				font.SetWeight( wxBOLD );
			}
			else
			{
				font.SetWeight( wxNORMAL );
			}
		}
		catch( ticpp::Exception& )
		{
			font.SetWeight( wxNORMAL );
		}

		// underlined
		try
		{
			element = xrcProperty->FirstChildElement( "underlined" );
			wxString underlined_str( element->GetText().c_str(), wxConvUTF8 );

			if ( underlined_str == "1" )
			{
				font.SetUnderlined( true );
			}
			else
			{
				font.SetUnderlined( false );
			}
		}
		catch( ticpp::Exception& )
		{
			font.SetUnderlined( false );
		}

		// face
		try
		{
			element = xrcProperty->FirstChildElement( "face" );
			wxString face( element->GetText().c_str(), wxConvUTF8 );
			font.SetFaceName( face );
		}
		catch( ticpp::Exception& )
		{
			font.SetFaceName( wxEmptyString );
		}

		// We already have the font type. So we must now use the wxFB format
		wxString font_str = wxString::Format( 	"%s,%d,%d,%d,%d,%d",
												font.GetFaceName().c_str(), font.GetStyle(),
												font.GetWeight(), font.GetPointSize(),
												font.GetFamily(), font.GetUnderlined() );

		property->SetText( font_str.mb_str( wxConvUTF8 ) );
	}
	catch( ticpp::Exception& ex )
	{
		wxLogDebug( wxString( ex.m_details.c_str(), wxConvUTF8 ) );
	}
}

void XrcToXfbFilter::ImportBitmapProperty( const wxString &xrcPropName, ticpp::Element *property )
{
	try
	{
		ticpp::Element *xrcProperty = m_xrcObj->FirstChildElement( xrcPropName.mb_str( wxConvUTF8 ) );
		wxString res( xrcProperty->GetText().c_str(), wxConvUTF8 );

		res.Trim();
		res += "; Load From File";
		property->SetText( res.mb_str( wxConvUTF8 ) );
	}
	catch( ticpp::Exception& ex )
	{
		wxLogDebug( wxString( ex.m_details.c_str(), wxConvUTF8 ) );
	}
}

void XrcToXfbFilter::ImportColourProperty( const wxString &xrcPropName, ticpp::Element *property )
{
	try
	{
		ticpp::Element *xrcProperty = m_xrcObj->FirstChildElement( xrcPropName.mb_str( wxConvUTF8 ) );
		std::string value = xrcProperty->GetText();

		// Changing "#rrggbb" format to "rrr,ggg,bbb"
		std::string hexColour = "0x" + value.substr( 1, 2 ) +
								" 0x" + value.substr( 3, 2 ) +
		                        " 0x" + value.substr( 5, 2 );

		std::istringstream strIn;
		std::ostringstream strOut;
		unsigned int red, green, blue;

		strIn.str( hexColour );
		strIn >> std::hex;

		strIn >> red;
		strIn >> green;
		strIn >> blue;

		strOut << red << "," << green << "," << blue;

		property->SetText( strOut.str() );
	}
	catch( ticpp::Exception& ex )
	{
		wxLogDebug( wxString( ex.m_details.c_str(), wxConvUTF8 ) );
	}
}

void XrcToXfbFilter::ImportStringListProperty( const wxString &xrcPropName, ticpp::Element *property , bool parseXrcText )
{
	try
	{
		ticpp::Element *xrcProperty = m_xrcObj->FirstChildElement( xrcPropName.mb_str( wxConvUTF8 ) );

		wxString res;

		ticpp::Element *element = xrcProperty->FirstChildElement( "item", false );
		while ( element )
		{
			try
			{
				wxString value( element->GetText().c_str(), wxConvUTF8 );
				if ( parseXrcText )
				{
					value = XrcTextToString( value );
				}
				res += wxChar( '\"' ) + value + "\" ";
			}
			catch( ticpp::Exception& ex )
			{
				wxLogDebug( "%s. line: %i", wxString( ex.m_details.c_str(), wxConvUTF8 ).c_str(), __LINE__ );
			}

			element = element->NextSiblingElement( "item", false );
		}
		res.Trim();
		property->SetText( res.mb_str( wxConvUTF8 ) );
	}
	catch( ticpp::Exception& ex )
	{
		wxLogDebug( "%s. line: %i", wxString( ex.m_details.c_str(), wxConvUTF8 ).c_str(), __LINE__ );
	}
}

void XrcToXfbFilter::AddWindowProperties()
{
	AddProperty( "pos", "pos", XRC_TYPE_POINT );
	AddProperty( "size", "size", XRC_TYPE_SIZE );
	AddProperty( "bg", "bg", XRC_TYPE_COLOUR );
	AddProperty( "fg", "fg", XRC_TYPE_COLOUR );
	AddProperty( "font", "font", XRC_TYPE_FONT );

	if ( m_xrcObj->FirstChildElement( "enabled", false ) )
	{
		AddProperty( "enabled", "enabled", XRC_TYPE_BOOL );
	}

	AddProperty( "hidden", "hidden", XRC_TYPE_BOOL );
	AddProperty( "tooltip", "tooltip", XRC_TYPE_TEXT );
	AddStyleProperty();
	AddExtraStyleProperty();

	// Subclass
	std::string subclass;
	m_xrcObj->GetAttribute( "subclass", &subclass, false );
	if ( !subclass.empty() )
	{
		ticpp::Element propElement( "property" );
		propElement.SetAttribute( "name", "subclass" );
		propElement.SetText( subclass );
		m_xfbObj->LinkEndChild( &propElement );
	}
};
