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

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

// Main propertygrid header.
#include <wx/propgrid/propgrid.h>

// Extra property classes.
#include <wx/propgrid/advprops.h>

// This defines wxPropertyGridManager.
#include <wx/propgrid/manager.h>

#include "objinspect.h"
//#include "prop_custom.h"

#include "utils/typeconv.h"

#define WXFB_PROPERTY_GRID 1000
#define WXFB_EVENT_GRID    1001

DECLARE_EVENT_TYPE( RECREATE_GRID_EVENT, -1 )
DEFINE_EVENT_TYPE( RECREATE_GRID_EVENT )

BEGIN_EVENT_TABLE(ObjectInspector, wxPanel)
	EVT_PG_CHANGED(WXFB_PROPERTY_GRID, ObjectInspector::OnPropertyGridChange)
	EVT_PG_CHANGED(WXFB_EVENT_GRID, ObjectInspector::OnEventGridChange)
	EVT_PG_ITEM_COLLAPSED(WXFB_PROPERTY_GRID, ObjectInspector::OnPropertyGridExpand)
	EVT_PG_ITEM_EXPANDED (WXFB_PROPERTY_GRID, ObjectInspector::OnPropertyGridExpand)

	EVT_COMMAND( wxID_ANY, RECREATE_GRID_EVENT, ObjectInspector::OnReCreateGrid )

	EVT_FB_OBJECT_SELECTED( ObjectInspector::OnObjectSelected )
	EVT_FB_PROJECT_REFRESH( ObjectInspector::OnProjectRefresh )
	EVT_FB_PROPERTY_MODIFIED( ObjectInspector::OnPropertyModified )
	EVT_FB_EVENT_HANDLER_MODIFIED( ObjectInspector::OnEventHandlerModified )

END_EVENT_TABLE()

/******************
 * wxSizeProperty *
 ******************/

class wxSizeProperty : public wxPGProperty
{
	WX_PG_DECLARE_PROPERTY_CLASS( wxSizeProperty )
public:

	wxSizeProperty( const wxString& label = wxPG_LABEL,
	                const wxString& name  = wxPG_LABEL,
	                const wxSize&   value = wxSize() );
	virtual ~wxSizeProperty();

	virtual wxVariant ChildChanged( wxVariant& thisValue,
	                                int childIndex,
	                                wxVariant& childValue ) const;
	virtual void RefreshChildren();

protected:

	// I stands for internal
	void SetValueI( const wxSize& value ) {
		m_value = WXVARIANT( value );
	}
};

WX_PG_IMPLEMENT_PROPERTY_CLASS( wxSizeProperty, wxPGProperty, wxSize, const wxSize&, TextCtrl )

wxSizeProperty::wxSizeProperty( const wxString& label,
                                const wxString& name,
                                const wxSize&   value ) : wxPGProperty( label, name )
{
	SetValueI( value );
	AddPrivateChild( new wxIntProperty( wxT("Width"),   wxPG_LABEL, value.x ) );
	AddPrivateChild( new wxIntProperty( wxT("Height"),  wxPG_LABEL, value.y ) );
}

wxSizeProperty::~wxSizeProperty() {}

void wxSizeProperty::RefreshChildren()
{
	if ( !GetChildCount() ) return;
	const wxSize& size = wxSizeRefFromVariant( m_value );
	Item(0)->SetValue( (long)size.x );
	Item(1)->SetValue( (long)size.y );
}

wxVariant wxSizeProperty::ChildChanged( wxVariant& thisValue,
                                        int childIndex,
                                        wxVariant& childValue ) const
{
	wxSize& size = wxSizeRefFromVariant(thisValue);
	int val = childValue.GetLong();
	switch ( childIndex ) {
	case 0:
		size.x = val;
		break;
	case 1:
		size.y = val;
		break;
	}
	wxVariant newVariant;
	newVariant << size;
	return newVariant;
}

/*******************
 * wxPointProperty *
 *******************/

class wxPointProperty : public wxPGProperty
{
	WX_PG_DECLARE_PROPERTY_CLASS( wxPointProperty )
public:

	wxPointProperty(const wxString& label = wxPG_LABEL,
	                const wxString& name  = wxPG_LABEL,
	                const wxPoint&  value = wxPoint() );
	virtual ~wxPointProperty();

	virtual wxVariant ChildChanged( wxVariant& thisValue,
	                                int childIndex,
	                                wxVariant& childValue ) const;
	virtual void RefreshChildren();

protected:

	void SetValueI( const wxPoint& value ) {
		m_value = WXVARIANT( value );
	}
};

WX_PG_IMPLEMENT_PROPERTY_CLASS( wxPointProperty, wxPGProperty,
                                wxPoint, const wxPoint&, TextCtrl )

wxPointProperty::wxPointProperty( const wxString& label,
                                  const wxString& name,
                                  const wxPoint&  value ) : wxPGProperty( label, name )
{
	SetValueI( value );
	AddPrivateChild( new wxIntProperty( wxT("X"), wxPG_LABEL, value.x ) );
	AddPrivateChild( new wxIntProperty( wxT("Y"), wxPG_LABEL, value.y ) );
}

wxPointProperty::~wxPointProperty() { }

void wxPointProperty::RefreshChildren()
{
	if ( !GetChildCount() ) return;
	const wxPoint& point = wxPointRefFromVariant( m_value );
	Item(0)->SetValue( (long)point.x );
	Item(1)->SetValue( (long)point.y );
}

wxVariant wxPointProperty::ChildChanged( wxVariant& thisValue,
        int childIndex,
        wxVariant& childValue ) const
{
	wxPoint& point = wxPointRefFromVariant(thisValue);
	int val = childValue.GetLong();
	switch ( childIndex ) {
	case 0:
		point.x = val;
		break;
	case 1:
		point.y = val;
		break;
	}
	wxVariant newVariant;
	newVariant << point;
	return newVariant;
}

/*******************
 * ObjectInspector *
 *******************/

ObjectInspector::ObjectInspector( wxWindow* parent, int id, int style )
		: wxPanel(parent,id), m_style(style)
{
	AppData()->AddHandler( this->GetEventHandler() );
	m_currentSel = PObjectBase();

	long nbStyle = 0;
	wxConfigBase* config = wxConfigBase::Get();
	config->Read( wxT("/mainframe/objectInspector/notebook_style"), &nbStyle);

	m_nb = new wxAuiNotebook( this, -1, wxDefaultPosition, wxDefaultSize, nbStyle );

	/** Register the slider editor TODO : Reimplement class / enable this
		#if wxUSE_SLIDER
		wxPGRegisterEditorClass( Slider );
		#endif
	*/
	m_pg = CreatePropertyGridManager(m_nb, WXFB_PROPERTY_GRID);
	m_eg = CreatePropertyGridManager(m_nb, WXFB_EVENT_GRID);

	m_nb->AddPage(m_pg,wxT("Properties"),false);
	m_nb->AddPage(m_eg,wxT("Events"),false);

	wxBoxSizer* topSizer = new wxBoxSizer( wxVERTICAL );
	topSizer->Add( m_nb, 1, wxALL | wxEXPAND, 0 );
	SetSizer( topSizer );
}

ObjectInspector::~ObjectInspector()
{
	AppData()->RemoveHandler( this->GetEventHandler() );
}

void ObjectInspector::SavePosition()
{
	/** Save Layout */
	wxConfigBase* config = wxConfigBase::Get();
	config->Write( wxT("/mainframe/objectInspector/DescBoxHeight" ), m_pg->GetDescBoxHeight() );
	config->Write( wxT("/mainframe/objectInspector/notebook_style"), m_nb->GetWindowStyleFlag() );
}

void ObjectInspector::Create( bool force )
{
	PObjectBase sel_obj = AppData()->GetSelectedObject();
	if ( sel_obj && ( sel_obj != m_currentSel || force ) ) {
		Freeze();

		m_currentSel = sel_obj;

		int pageNumber = m_pg->GetSelectedPage();
		wxString pageName;
		if ( pageNumber != wxNOT_FOUND ) {
			pageName = m_pg->GetPageName( pageNumber );
		}

		/** Clear Property Grid Manager */
		int pageCount = (int)m_pg->GetPageCount();
		if ( pageCount > 0 ) {
			for ( int pageIndex = pageCount - 1; pageIndex >= 0; --pageIndex ) {
				m_pg->RemovePage( pageIndex );
			}
		}

		/** Now we do the same thing for event grid... */
		pageCount = (int)m_eg->GetPageCount();
		if ( pageCount > 0) {
			for ( int pageIndex = pageCount - 1; pageIndex >= 0; --pageIndex) {
				m_eg->RemovePage( pageIndex );
			}
		}

		m_propMap.clear();
		m_eventMap.clear();

		PObjectInfo obj_desc = sel_obj->GetObjectInfo();
		if (obj_desc) {

			PropertyMap propMap, dummyPropMap;
			EventMap eventMap, dummyEventMap;

			/** We create the categories with the properties of the object organized by "classes" */
			CreateCategory( obj_desc->GetClassName(), sel_obj, obj_desc, propMap, false );
			CreateCategory( obj_desc->GetClassName(), sel_obj, obj_desc, eventMap, true );

			for (unsigned int i=0; i<obj_desc->GetBaseClassCount() ; i++) {
				PObjectInfo info_base = obj_desc->GetBaseClass(i);
				CreateCategory( info_base->GetClassName(), sel_obj, info_base, propMap, false );
				CreateCategory( info_base->GetClassName(), sel_obj, info_base, eventMap, true );
			}

			PObjectBase parent = sel_obj->GetParent();
			if ( parent ) {
				PObjectInfo parent_desc = parent->GetObjectInfo();
				if ( parent_desc->GetObjectType()->IsItem()) {
					CreateCategory( parent_desc->GetClassName(), parent, parent_desc, dummyPropMap, false );
					CreateCategory( parent_desc->GetClassName(), parent, parent_desc, dummyEventMap, true );

					for (unsigned int i=0; i<parent_desc->GetBaseClassCount() ; i++) {
						PObjectInfo info_base = parent_desc->GetBaseClass(i);
						CreateCategory( info_base->GetClassName(), parent, info_base, dummyPropMap, false );
						CreateCategory( info_base->GetClassName(), parent, info_base, dummyEventMap, true );
					}
				}
			}

			/** Select previously selected page, or first page */
			if ( m_pg->GetPageCount() > 0 ) {
				int pageIndex = m_pg->GetPageByName( pageName );
				if ( wxNOT_FOUND != pageIndex ) {
					m_pg->SelectPage( pageIndex );
				} else {
					m_pg->SelectPage( 0 );
				}
			}
		}

		m_pg->Refresh();
		m_pg->Update();
		m_eg->Refresh();
		m_eg->Update();
		Thaw();
	}
}

int ObjectInspector::StringToBits(const wxString& strVal, wxPGChoices& constants)
{
	wxStringTokenizer strTok(strVal, wxT(" |"));
	int val = 0;
	while (strTok.HasMoreTokens()) {
		wxString token = strTok.GetNextToken();
		unsigned int i = 0;
		bool done = false;
		while (i < constants.GetCount() && !done) {
			if (constants.GetLabel(i) == token) {
				val |= constants.GetValue(i);
				done = true;
			}
			i++;
		}
	}
	return val;
}

wxPGProperty* ObjectInspector::GetProperty(PProperty prop)
{
	wxPGProperty* result = NULL;
	PropertyType type = prop->GetType();
	wxString name = prop->GetName();
	wxVariant vTrue = wxVariant( true, wxT("true") );

	switch ( type ) {
	case PT_MACRO: {
		result = new wxStringProperty(name, wxPG_LABEL, prop->GetValueAsString());
		break;
	}
	case PT_INT: {
		result = new wxIntProperty(name, wxPG_LABEL, prop->GetValueAsInteger());
		break;
	}
	case PT_UINT: {
		result = new wxUIntProperty(name, wxPG_LABEL, (unsigned)prop->GetValueAsInteger());
		break;
	}
	case PT_WXSTRING:
	case PT_WXSTRING_I18N: {
		result = new wxLongStringProperty(name, wxPG_LABEL, prop->GetValueAsText());
		break;
	}
	case PT_TEXT: {
		result = new wxLongStringProperty(name, wxPG_LABEL, prop->GetValueAsString());
		result->SetFlag( wxPG_PROP_NO_ESCAPE );
		break;
	}
	case PT_BOOL: {
		result = new wxBoolProperty(name, wxPG_LABEL, prop->GetValue() == wxT("1"));
		break;
	}
	case PT_BITLIST: {
		PPropertyInfo prop_desc = prop->GetPropertyInfo();
		POptionList opt_list = prop_desc->GetOptionList();

		assert(opt_list && opt_list->GetOptionCount() > 0);

		wxPGChoices constants;
		const std::map< wxString, wxString > options = opt_list->GetOptions();
		std::map< wxString, wxString >::const_iterator it;
		unsigned int i = 0;
		for ( it = options.begin(); it != options.end(); ++it ) {
			constants.Add( it->first, 1 << i++ );
		}

		int val = StringToBits(prop->GetValueAsString(), constants);
		result = new wxFlagsProperty(name, wxPG_LABEL, constants, val);

		/** Workaround to set the help strings for individual members of a wxFlagsProperty */
		wxFlagsProperty* flagsProp = dynamic_cast<wxFlagsProperty*>(result);
		if ( NULL != flagsProp ) {
			for ( size_t i = 0; i < flagsProp->GetItemCount(); i++ ) {
				wxPGProperty* prop = flagsProp->Item( i );
				std::map< wxString, wxString >::const_iterator option = options.find( prop->GetLabel() );
				if ( option != options.end() )

					m_pg->SetPropertyHelpString( prop, option->second );
			}
		}
		break;
	}
	case PT_INTLIST:
	case PT_UINTLIST: {
		result = new wxStringProperty(name, wxPG_LABEL, IntList( prop->GetValueAsString(), type == PT_UINTLIST ).ToString());
		break;
	}
	case PT_OPTION: {
		PPropertyInfo prop_desc = prop->GetPropertyInfo();
		POptionList opt_list = prop_desc->GetOptionList();

		assert(opt_list && opt_list->GetOptionCount() > 0);

		wxString value = prop->GetValueAsString();
		wxString help;

		wxPGChoices constants;
		const std::map< wxString, wxString > options = opt_list->GetOptions();
		std::map< wxString, wxString >::const_iterator it;
		unsigned int i = 0;
		for ( it = options.begin(); it != options.end(); ++it ) {
			constants.Add( it->first, i++ );
			if ( it->first == value ) {
				/** Save help */
				help = it->second;
			}
		}
		result = new wxEnumProperty(name, wxPG_LABEL, constants);
		result->SetValueFromString(value, 0);
		wxString desc = prop_desc->GetDescription();
		if ( desc.empty() ) {
			desc = value + wxT(":\n") + help;
		} else {
			desc += wxT("\n\n") + value + wxT(":\n") + help;
		}
		result->SetHelpString( desc );
		break;
	}
	case PT_WXPOINT: {
		result = new wxPointProperty(name, wxPG_LABEL, prop->GetValueAsPoint());
		break;
	}
	case PT_WXSIZE: {
		result = new wxSizeProperty(name, wxPG_LABEL, prop->GetValueAsSize());
		break;
	}
	case PT_WXFONT: {
		wxFontContainer container = TypeConv::StringToFont( prop->GetValueAsString() );
		result = new wxFontProperty(name, wxPG_LABEL, container.GetFont() );
		break;
	}
	case PT_WXCOLOUR: {
		wxString value = prop->GetValueAsString();
		if ( value.empty() ) { // Default Colour
			wxColourPropertyValue def;
			def.m_type = wxSYS_COLOUR_WINDOW;
			result = new wxSystemColourProperty( name, wxPG_LABEL, def );
		} else {
			if ( value.find_first_of( wxT("wx") ) == 0 ) {
				wxColourPropertyValue def;
				def.m_type = TypeConv::StringToSystemColour( value );
				result = new wxSystemColourProperty( name, wxPG_LABEL, def );
			} else {
				result = new wxSystemColourProperty( name, wxPG_LABEL, prop->GetValueAsColour() );
			}
		}
		break;
	}
	case PT_PATH: {
		result = new wxDirProperty(name, wxPG_LABEL, prop->GetValueAsString());
		break;
	}
	case PT_FILE: {
		result = new wxFileProperty(name, wxPG_LABEL, prop->GetValueAsString());
		break;
	}
	case PT_BITMAP: {
		result = new wxImageFileProperty( name, wxPG_LABEL, prop->GetValue() );
		break;
	}
	case PT_STRINGLIST: {
		result = new wxArrayStringProperty(name, wxPG_LABEL,prop->GetValueAsArrayString());
		break;
	}
	case PT_FLOAT: {
		result = new wxFloatProperty(name, wxPG_LABEL,prop->GetValueAsFloat());
		break;
	}
	case PT_PARENT: {
		wxPropertyCategory* parent = new wxPropertyCategory( name, wxPG_LABEL );

		PPropertyInfo prop_desc = prop->GetPropertyInfo();
		std::list< PropertyChild >* children = prop_desc->GetChildren();
		std::list< PropertyChild >::iterator it;
		for ( it = children->begin(); it != children->end(); ++it ) {
			wxPGProperty* child = new wxStringProperty( it->m_name, wxPG_LABEL, wxEmptyString );
			m_pg->Append( child );
			m_pg->SetPropertyHelpString( child, it->m_description );
		}

		parent->SetValueFromString( prop->GetValueAsString(), wxPG_FULL_VALUE );
		result = parent;
		break;
	}
	default: {
		result = new wxStringProperty(name, wxPG_LABEL, prop->GetValueAsString());
		result->SetAttribute(wxPG_BOOL_USE_DOUBLE_CLICK_CYCLING, vTrue);
		wxLogError( _("Property type Unknown") );
		break;
	}
	}
	return result;
}

void ObjectInspector::AddItems( const wxString& name, PObjectBase obj,
                                PObjectInfo obj_info, PPropertyCategory category, PropertyMap &properties )
{
	size_t propCount = category->GetPropertyCount();
	for ( size_t i = 0; i < propCount; i++ ) {
		wxString propName = category->GetPropertyName( i );
		PProperty prop = obj->GetProperty( propName );

		if ( !prop )
			continue;

		PPropertyInfo propInfo = prop->GetPropertyInfo();

		/** We do not want to duplicate inherited properties */
		if ( properties.find( propName ) == properties.end() ) {
			Debug::Print(propName);
			wxPGProperty* prope = GetProperty( prop );
			wxPGProperty* id = m_pg->Append( prope );
			if ( prop->GetType() != PT_OPTION ) {
				m_pg->SetPropertyHelpString( id, propInfo->GetDescription() );
			}
			wxString customEditor = propInfo->GetCustomEditor();
			if ( !customEditor.empty() ) {
				wxPGEditor* editor = m_pg->GetEditorByName( customEditor );
				if ( editor ) {
					m_pg->SetPropertyEditor( id, editor );
				}
			}

			if (m_style != wxFB_OI_MULTIPAGE_STYLE) {
				/** Most common classes will be showed with a slightly different colour. */
				if (name == wxT("wxWindow"))
					m_pg->SetPropertyBackgroundColour(id,wxColour(255,255,205)); /** Yellow */
				else if (name == wxT("sizeritem") || name == wxT("gbsizeritem") || name == wxT("sizeritembase") )
					m_pg->SetPropertyBackgroundColour(id,wxColour(220,255,255)); /** Cyan */
			}

			ExpandMap::iterator it = m_isExpanded.find( propName );
			if ( it != m_isExpanded.end() ) {
				if ( it->second ) {
					m_pg->Expand( id );
				} else {
					m_pg->Collapse( id );
				}
			}

			properties.insert( PropertyMap::value_type( propName, prop ) );
			m_propMap.insert( ObjInspectorPropertyMap::value_type( id, prop ) );
		}
	}

	size_t catCount = category->GetCategoryCount();
	for ( size_t i = 0; i < catCount; i++ ) {
		PPropertyCategory nextCat = category->GetCategory( i );
		if ( 0 == nextCat->GetCategoryCount() && 0 == nextCat->GetPropertyCount() ) {
			continue;
		}
		wxPGProperty* catId = m_pg->Append( new wxPropertyCategory( nextCat->GetName() ) );
		ExpandMap::iterator it = m_isExpanded.find( nextCat->GetName() );
		if ( it != m_isExpanded.end() ) {
			if ( it->second ) {
				m_pg->Expand( catId );
			} else {
				m_pg->Collapse( catId );
			}
		}
		AddItems( name, obj, obj_info, nextCat, properties );
	}
}

void ObjectInspector::AddItems( const wxString& name, PObjectBase obj,
                                PObjectInfo obj_info, PPropertyCategory category, EventMap &events )
{
	size_t eventCount = category->GetEventCount();
	for ( size_t i = 0; i < eventCount; i++ ) {
		wxString eventName = category->GetEventName( i );
		PEvent event = obj->GetEvent( eventName );

		if ( !event )
			continue;

		PEventInfo eventInfo = event->GetEventInfo();

		/** We do not want to duplicate inherited events */
		if ( events.find( eventName ) == events.end() ) {
			wxPGProperty* pgProp = new wxStringProperty( eventInfo->GetName(), wxPG_LABEL, event->GetValue() );
			wxPGProperty* id = m_eg->Append( pgProp );
			m_eg->SetPropertyHelpString( id, eventInfo->GetDescription() );

			if (m_style != wxFB_OI_MULTIPAGE_STYLE) {
				/** Most common classes will be showed with a slightly different colour. */
				if (name == wxT("wxWindow"))
					m_eg->SetPropertyBackgroundColour(id,wxColour(255,255,205)); // yellow
				else if (name == wxT("sizeritem") || name == wxT("gbsizeritem") || name == wxT("sizeritembase") )
					m_eg->SetPropertyBackgroundColour(id,wxColour(220,255,255)); // cyan
			}

			events.insert( EventMap::value_type( eventName, event ) );
			m_eventMap.insert( ObjInspectorEventMap::value_type( id, event) );
		}
	}

	size_t catCount = category->GetCategoryCount();
	for ( size_t i = 0; i < catCount; i++ ) {
		PPropertyCategory nextCat = category->GetCategory( i );
		if ( 0 == nextCat->GetCategoryCount() && 0 == nextCat->GetEventCount() ) {
			continue;
		}
		m_eg->AppendIn( category->GetName(), new wxPropertyCategory( nextCat->GetName() ) );
		AddItems( name, obj, obj_info, nextCat, events );
	}
}

void ObjectInspector::OnPropertyGridChange( wxPropertyGridEvent& event )
{
	wxPGProperty* propPtr = event.GetProperty();
	ObjInspectorPropertyMap::iterator it = m_propMap.find( propPtr );

	if ( m_propMap.end() == it ) {
		// Could be a child property
		propPtr = propPtr->GetParent();
		it = m_propMap.find( propPtr );
	}
	
	Debug::Print(wxT("Property Changed"));
	
	if ( it != m_propMap.end() ) {
		PProperty prop = it->second;
		switch ( prop->GetType() ) {
		case PT_FLOAT: {
			/** Use typeconv to properly handle locale */
			Debug::Print(wxT("Property Changed [PT_FLOAT]"));
			double val = m_pg->GetPropertyValueAsDouble(propPtr);
			AppData()->ModifyProperty( prop, TypeConv::FloatToString( val ) );
			break;
		}
		case PT_TEXT:
		case PT_MACRO:
		case PT_INT:
		case PT_UINT: {
			AppData()->ModifyProperty( prop, m_pg->GetPropertyValueAsString(propPtr) );
			Debug::Print(wxT("Property Changed [PT_UINT]"));
			break;
		}
		case PT_OPTION: {
			Debug::Print(wxT("Property Changed [PT_OPTION]"));
			wxString value = m_pg->GetPropertyValueAsString(propPtr);
			AppData()->ModifyProperty( prop, value );

			/** Update displayed description for the new selection */
			PPropertyInfo prop_desc = prop->GetPropertyInfo();
			POptionList opt_list = prop_desc->GetOptionList();

			wxString helpString = prop_desc->GetDescription();
			if ( opt_list && opt_list->GetOptionCount() > 0 ) {
				const std::map< wxString, wxString > options = opt_list->GetOptions();
				std::map< wxString, wxString >::const_iterator option = options.find( value );
				if ( option != options.end() ) {
					if ( helpString.empty() ) {
						helpString = value + wxT(":\n") + option->second;
					} else {
						helpString += wxT("\n\n") + value + wxT(":\n") + option->second;
					}
				}
			}
			m_pg->SetPropertyHelpString( propPtr, helpString );
			m_pg->SetDescription( propPtr->GetLabel(), helpString );
			break;
		}
		case PT_PARENT: {
			Debug::Print(wxT("Property Changed [PT_PARENT]"));
			AppData()->ModifyProperty( prop, propPtr->GetValueAsString( wxPG_FULL_VALUE ) );
			break;
		}
		case PT_WXSTRING:
		case PT_WXSTRING_I18N: {
			/** Las cadenas de texto del inspector son formateadas */
			Debug::Print(wxT("Property Changed [PT_WXSTRING]"));
			wxString value = m_pg->GetPropertyValueAsString(propPtr);
			AppData()->ModifyProperty( prop, value );
			break;
		}
		case PT_BOOL: {
			Debug::Print(wxT("Property Changed [PT_BOOL]"));
			AppData()->ModifyProperty( prop, m_pg->GetPropertyValueAsBool(propPtr) ? wxT("1") : wxT("0") );
			break;
		}
		case PT_BITLIST: {
			Debug::Print(wxT("Property Changed [PT_BITLIST]"));
			wxString aux = m_pg->GetPropertyValueAsString(propPtr);
			Debug::Print(aux);
			aux.Replace( wxT(" "), wxT("") );
			aux.Replace( wxT(","), wxT("|") );
			AppData()->ModifyProperty( prop, aux );
			break;
		}
		case PT_WXPOINT: {
			Debug::Print(wxT("Property Changed [PT_WXPOINT]"));
			wxPoint point = wxPointRefFromVariant(event.GetPropertyValue ());
			AppData()->ModifyProperty( prop, wxString::Format( wxT("%i,%i"), point.x, point.y ) );
			break;
		}
		case PT_WXSIZE: {
			Debug::Print(wxT("Property Changed [PT_WXSIZE]"));
			wxSize size = wxSizeRefFromVariant (event.GetPropertyValue());
			AppData()->ModifyProperty( prop, wxString::Format( wxT("%i,%i"), size.GetWidth(), size.GetHeight() ) );
			break;
		}
		case PT_WXFONT: {
			Debug::Print(wxT("Property Changed [PT_WXFONT]"));
			wxFont font;
			font << event.GetPropertyValue() ;
			wxFontContainer container(font.GetPointSize(),
			                          font.GetFamily(),
			                          font.GetStyle(),
			                          font.GetWeight(),
			                          font.GetUnderlined(),
			                          font.GetFaceName() );
			AppData()->ModifyProperty( prop, TypeConv::FontToString( container ) );
			break;
		}
		case PT_WXCOLOUR: {
			Debug::Print(wxT("Property Changed [PT_WXCOLOUR]"));
			wxColourPropertyValue colour;
			colour << event.GetPropertyValue();
			switch ( colour.m_type ) {
			case wxSYS_COLOUR_MAX:
				AppData()->ModifyProperty( prop, _T("") );
				break;
			case wxPG_COLOUR_CUSTOM:
				AppData()->ModifyProperty( prop, TypeConv::ColourToString( colour.m_colour ) );
				break;
			default:
				AppData()->ModifyProperty( prop, TypeConv::SystemColourToString( colour.m_type ) );
			}
			break;
		}
		case PT_INTLIST:
		case PT_UINTLIST: {
			Debug::Print(wxT("Property Changed [PT_UINTLIST]"));
			IntList il( event.GetPropertyValue(), PT_UINTLIST == prop->GetType() );
			AppData()->ModifyProperty( prop, il.ToString() );
			break;
		}
		case PT_BITMAP: {
			Debug::Print(wxT("Property Changed [PT_BITMAP]"));
			/** Get property value */
			wxString path = m_pg->GetPropertyValueAsString(propPtr);
			size_t semicolon_index = path.find_first_of( wxT(";") );
			if ( semicolon_index != path.npos ) {
				path = TypeConv::MakeRelativeURL( path.substr( 0, semicolon_index ), AppData()->GetProjectPath() ) + path.substr( semicolon_index  );
			}

			/* Save state from old property to use after grid is recreated */
			wxPGProperty* pwc = dynamic_cast< wxPGProperty* >( event.GetProperty() );
			bool expanded = false;
			if ( pwc ) {
				expanded = pwc->IsExpanded();
			}
			wxString name = event.GetPropertyName();

			/* Respond to property modification */
			AppData()->ModifyProperty( prop, path );

			/* It is bad to delete the property while handling an event from it! */
			wxCommandEvent e( RECREATE_GRID_EVENT );
			e.SetString( name );
			e.SetInt( expanded ? 1 : 0 );
			AddPendingEvent( e );
			break;
		}
		default:
			AppData()->ModifyProperty( prop, event.GetPropertyValue() );
		}
	}
}

void ObjectInspector::OnReCreateGrid( wxCommandEvent& event )
{
	/** Recreate grid, the bitmap property may need to change */
	Create( true );

	/** Re-expand the bitmap property, if it was expanded */
	wxPGProperty* bitmapProp = m_pg->GetPropertyByName( event.GetString() );
	m_pg->SelectProperty( bitmapProp );
	if ( event.GetInt() != 0 ) {
		m_pg->Expand( bitmapProp );
		m_pg->Expand( dynamic_cast< wxPGProperty* >( bitmapProp )->Last() );
	}
}

void ObjectInspector::OnEventGridChange(wxPropertyGridEvent& event)
{
	ObjInspectorEventMap::iterator it = m_eventMap.find( event.GetProperty() );

	if ( it != m_eventMap.end() ) {
		PEvent evt = it->second;
		wxString handler = event.GetPropertyValue();
		handler.Trim();
		handler.Trim( false );
		AppData()->ModifyEventHandler( evt, handler );
	}
}

void ObjectInspector::OnPropertyGridExpand(wxPropertyGridEvent& event)
{
	m_isExpanded[event.GetPropertyName()] = m_pg->IsPropertyExpanded( event.GetProperty() );
}

///////////////////////////////////////////////////////////////////////////////
void ObjectInspector::OnObjectSelected( wxFBObjectEvent& )
{
	Create();
}

void ObjectInspector::OnProjectRefresh( wxFBEvent& )
{
	Create(true);
}

void ObjectInspector::OnEventHandlerModified( wxFBEventHandlerEvent& event )
{
	PEvent e = event.GetFBEventHandler();
	m_eg->SetPropertyValue( e->GetName(), e->GetValue() );
	m_eg->Refresh();
}

void ObjectInspector::OnPropertyModified( wxFBPropertyEvent& event )
{
	PProperty prop = event.GetFBProperty();

	PObjectBase propobj = prop->GetObject();
	PObjectBase appobj = AppData()->GetSelectedObject();

	bool shouldContinue = ( prop->GetObject() == AppData()->GetSelectedObject() );
	if ( !shouldContinue ) {
		/** Item objects cannot be selected - their children are selected instead */
		if ( propobj->GetObjectInfo()->GetObjectType()->IsItem() ) {
			if ( propobj->GetChildCount() > 0 ) {
				shouldContinue = ( appobj == propobj->GetChild( 0 ) );
			}
		}
	}
	if ( !shouldContinue ) {
		return;
	}

	wxPGProperty* pgid = m_pg->GetPropertyByLabel(prop->GetName());
	if (pgid == NULL ) return; /** Puede que no se esté mostrando ahora esa página */

	switch (prop->GetType()) {
	case PT_FLOAT: {
		/** Use float instead of string -> typeconv handles locale */
		pgid->SetValue( wxVariant( prop->GetValueAsFloat() ) );
		break;
	}
	case PT_INT:
	case PT_UINT: {
		pgid->SetValueFromString(prop->GetValueAsString(), 0);
		break;
	}
	case PT_TEXT: {
		pgid->SetValueFromString(prop->GetValueAsString(), 0);
		break;
	}
	case PT_MACRO:
	case PT_OPTION:
	case PT_PARENT:
	case PT_WXSTRING: {
		pgid->SetValueFromString(prop->GetValueAsText(), 0);
		break;
	}
	case PT_WXSTRING_I18N: {
		pgid->SetValueFromString(prop->GetValueAsText(), 0);
		break;
	}
	case PT_BOOL: {
		pgid->SetValueFromInt(prop->GetValueAsString() == wxT("0") ? 0 : 1, 0);
		break;
	}
	case PT_BITLIST: {
		wxString aux = prop->GetValueAsString();
		aux.Replace(wxT("|"), wxT(", "));
		if (aux == wxT("0")) aux = wxT("");
		pgid->SetValueFromString(aux, 0);
		break;
	}
	case PT_WXPOINT: {
		m_pg->SetPropertyValue(pgid, prop->GetValue());
		break;
	}
	case PT_WXSIZE: {
		m_pg->SetPropertyValue(pgid, prop->GetValue());
		break;
	}
	case PT_WXFONT: {
		wxFontContainer container = TypeConv::StringToFont( prop->GetValueAsString() );
		wxVariant value;
		value << container.GetFont();
		pgid->SetValue( value );
		break;
	}
	case PT_WXCOLOUR: {
		wxString value = prop->GetValueAsString();
		if ( value.empty() ) {
			wxColourPropertyValue def;
			def.m_type = wxSYS_COLOUR_WINDOW;
			m_pg->SetPropertyValue( pgid, def );
		} else {
			if ( value.find_first_of( wxT("wx") ) == 0 ) {
				wxColourPropertyValue def;
				def.m_type = TypeConv::StringToSystemColour( value );
				def.m_colour = prop->GetValueAsColour();
				m_pg->SetPropertyValue( pgid, def );
			} else {
				wxColourPropertyValue def( wxPG_COLOUR_CUSTOM, prop->GetValueAsColour() );
				m_pg->SetPropertyValue( pgid, def );
			}
		}
		break;
	}
	case PT_BITMAP: {
		break;
	}
	default: {
		pgid->SetValueFromString(prop->GetValueAsString(), wxPG_FULL_VALUE);
	}
	}
	m_pg->Refresh();
}

wxPropertyGridManager* ObjectInspector::CreatePropertyGridManager(wxWindow *parent, wxWindowID id)
{
	int pgStyle;
	int defaultDescBoxHeight;

	switch (m_style) {
	case wxFB_OI_MULTIPAGE_STYLE: {
		pgStyle = wxPG_BOLD_MODIFIED | wxPG_SPLITTER_AUTO_CENTER | wxPG_TOOLBAR |
		          wxPG_DESCRIPTION | wxPGMAN_DEFAULT_STYLE;
		defaultDescBoxHeight = 50;
		break;
	}
	case wxFB_OI_DEFAULT_STYLE:
	case wxFB_OI_SINGLE_PAGE_STYLE:
	default: {
		pgStyle = wxPG_BOLD_MODIFIED | wxPG_SPLITTER_AUTO_CENTER | wxPG_DESCRIPTION |
		          wxPGMAN_DEFAULT_STYLE;
		defaultDescBoxHeight = 150;
		break;
	}
	}

	int descBoxHeight;
	wxConfigBase* config = wxConfigBase::Get();
	config->Read( wxT( "/mainframe/objectInspector/DescBoxHeight" ), &descBoxHeight, defaultDescBoxHeight );
	if ( -1 == descBoxHeight ) {
		descBoxHeight = defaultDescBoxHeight;
	}

	wxPropertyGridManager* pg;
	pg = new wxPropertyGridManager( parent, id, wxDefaultPosition, wxDefaultSize, pgStyle );
	pg->SetDescBoxHeight( descBoxHeight );
	pg->SetExtraStyle( wxPG_EX_NATIVE_DOUBLE_BUFFERING );
//	pg->SetExtraStyle( wxPG_EX_PROCESS_EVENTS_IMMEDIATELY ); TODO: ???

	return pg;
}
