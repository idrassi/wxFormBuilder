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

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/advprops.h>
#include <wx/propgrid/manager.h>

#include "objinspect29.h"
#include "model/objectbase.h"
#include "utils/debug.h"
#include "utils/typeconv.h"

#include "rad/bitmaps.h"
#include "rad/wxfbevent.h"
#include "rad/appdata.h"

#include <wx/tokenzr.h>
#include <wx/config.h>

#define WXFB_PROPERTY_GRID 1000
#define WXFB_EVENT_GRID    1001

// -----------------------------------------------------------------------
// wxSizeProperty
// -----------------------------------------------------------------------

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
	AddPrivateChild( new wxIntProperty( "Width", wxPG_LABEL, value.x ) );
	AddPrivateChild( new wxIntProperty( "Height", wxPG_LABEL, value.y ) );
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

// -----------------------------------------------------------------------
// wxPointProperty
// -----------------------------------------------------------------------

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
	AddPrivateChild( new wxIntProperty( "X", wxPG_LABEL, value.x ) );
	AddPrivateChild( new wxIntProperty( "Y", wxPG_LABEL, value.y ) );
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
	wxPoint& point = wxPointRefFromVariant( thisValue );
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

// -----------------------------------------------------------------------
// wxBitmapWithResourceProperty TODO
// -----------------------------------------------------------------------

static long g_imageFilterIndex = -1;
static wxString g_imageInitialPath = wxEmptyString;

class wxBitmapWithResourceProperty : public wxPGProperty
{
	WX_PG_DECLARE_PROPERTY_CLASS( wxBitmapWithResourceProperty )

public:
	wxBitmapWithResourceProperty( const wxString& label = wxPG_LABEL,
                                       const wxString& name  = wxPG_LABEL,
                                       const wxString& value = wxString() );

	virtual ~wxBitmapWithResourceProperty();

	virtual wxVariant DoGetValue() const;

	void DoSetValue( wxVariant value );

    virtual wxVariant ChildChanged( wxVariant& thisValue,
                                    int childIndex,
                                    wxVariant& childValue ) const;

    virtual void RefreshChildren();

protected:

	wxString m_image;
	wxString m_id;
	wxString m_client;
	wxString m_source;
	wxSize m_icoSize;
	wxArrayString m_strings;
	static wxArrayString m_ids;
	static wxArrayString m_clients;

private:
	enum
	{
		SOURCE_FILE = 0,
		SOURCE_RESOURCE,
		SOURCE_ICON_RESOURCE
	};

	enum
	{
		ITEM_FILE_OR_RESOURCE = 0,
		ITEM_SOURCE
	};
};

wxArrayString wxBitmapWithResourceProperty::m_ids;
wxArrayString wxBitmapWithResourceProperty::m_clients;

WX_PG_IMPLEMENT_PROPERTY_CLASS( wxBitmapWithResourceProperty, wxPGProperty,
                                wxString, const wxString&, TextCtrl )

wxBitmapWithResourceProperty::wxBitmapWithResourceProperty( const wxString& label,
                                                                      const wxString& name,
                                                                      const wxString& value )
: wxPGProperty( label, name )
{	
	// Add the options
	m_strings.Add(_("Load From File") );
    m_strings.Add(_("Load From Embedded File") );
    m_strings.Add(_("Load From Resource") );
    m_strings.Add(_("Load From Icon Resource") );
    m_strings.Add(_("Load From Art Provider") );

	// Parse default value, ( sets m_image and m_source based on 'value' )
	wxVariant variant = wxVariant( value );
	DoSetValue( variant );

	// Add the appropriate child
	if ( (m_source == _("Load From File")) || (m_source == _("Load From Embedded File")) )
	{
		wxPGProperty* child = new wxImageFileProperty( wxT("file_path"), wxPG_LABEL, m_image );
		AddPrivateChild( child );

		child->SetHelpString( _("Path to the image file.") );
		if ( g_imageFilterIndex >= 0 )
		{
			wxVariant filterIndex( g_imageFilterIndex );
			child->SetAttribute( wxPG_FILE_WILDCARD, filterIndex );
		}

		if ( !g_imageInitialPath.empty() )
		{
			wxVariant initialPath( g_imageInitialPath );
			child->SetAttribute( wxPG_FILE_INITIAL_PATH, initialPath );
		}
	}
	else if ( m_source == _("Load From Art Provider") )
	{
		if( m_ids.IsEmpty() )
		{
			m_ids.Add(wxT("wxART_ADD_BOOKMARK"));
			m_ids.Add(wxT("wxART_DEL_BOOKMARK "));
			m_ids.Add(wxT("wxART_HELP_SIDE_PANEL"));
			m_ids.Add(wxT("wxART_HELP_SETTINGS"));
			m_ids.Add(wxT("wxART_HELP_BOOK"));
			m_ids.Add(wxT("wxART_HELP_FOLDER"));
			m_ids.Add(wxT("wxART_HELP_PAGE"));
			m_ids.Add(wxT("wxART_GO_BACK"));
			m_ids.Add(wxT("wxART_GO_FORWARD"));
			m_ids.Add(wxT("wxART_GO_UP"));
			m_ids.Add(wxT("wxART_GO_DOWN"));
			m_ids.Add(wxT("wxART_GO_TO_PARENT"));
			m_ids.Add(wxT("wxART_GO_HOME"));
			m_ids.Add(wxT("wxART_FILE_OPEN"));
			m_ids.Add(wxT("wxART_PRINT"));
			m_ids.Add(wxT("wxART_HELP"));
			m_ids.Add(wxT("wxART_TIP"));
			m_ids.Add(wxT("wxART_REPORT_VIEW"));
			m_ids.Add(wxT("wxART_LIST_VIEW"));
			m_ids.Add(wxT("wxART_NEW_DIR"));
			m_ids.Add(wxT("wxART_FOLDER"));
			m_ids.Add(wxT("wxART_GO_DIR_UP"));
			m_ids.Add(wxT("wxART_EXECUTABLE_FILE"));
			m_ids.Add(wxT("wxART_NORMAL_FILE"));
			m_ids.Add(wxT("wxART_TICK_MARK"));
			m_ids.Add(wxT("wxART_CROSS_MARK"));
			m_ids.Add(wxT("wxART_ERROR"));
			m_ids.Add(wxT("wxART_QUESTION"));
			m_ids.Add(wxT("wxART_WARNING"));
			m_ids.Add(wxT("wxART_INFORMATION"));
			m_ids.Add(wxT("wxART_MISSING_IMAGE"));

			m_ids.Add(wxT("gtk-about"));
			m_ids.Add(wxT("gtk-add"));
			m_ids.Add(wxT("gtk-apply"));
			m_ids.Add(wxT("gtk-bold"));
			m_ids.Add(wxT("gtk-cancel"));
			m_ids.Add(wxT("gtk-caps-lock-warning"));
			m_ids.Add(wxT("gtk-cdrom"));
			m_ids.Add(wxT("gtk-clear"));
			m_ids.Add(wxT("gtk-close"));
			m_ids.Add(wxT("gtk-color-picker"));
			m_ids.Add(wxT("gtk-convert"));
			m_ids.Add(wxT("gtk-copy"));
			m_ids.Add(wxT("gtk-cut"));
			m_ids.Add(wxT("gtk-delete"));
			m_ids.Add(wxT("gtk-dialog-authentication"));
			m_ids.Add(wxT("gtk-dialog-error"));
			m_ids.Add(wxT("gtk-dialog-info"));
			m_ids.Add(wxT("gtk-dialog-question"));
			m_ids.Add(wxT("gtk-dialog-warning"));
			m_ids.Add(wxT("gtk-warning"));
			m_ids.Add(wxT("gtk-discard"));
			m_ids.Add(wxT("gtk-disconnect"));
			m_ids.Add(wxT("gtk-dnd"));
			m_ids.Add(wxT("gtk-dnd-multiple"));
			m_ids.Add(wxT("gtk-edit"));
			m_ids.Add(wxT("gtk-execute"));
			m_ids.Add(wxT("gtk-file"));
			m_ids.Add(wxT("gtk-find"));
			m_ids.Add(wxT("gtk-find-and-replace"));
			m_ids.Add(wxT("gtk-fullscreen"));
			m_ids.Add(wxT("gtk-goto-bottom"));
			m_ids.Add(wxT("gtk-goto-first"));
			m_ids.Add(wxT("gtk-goto-last"));
			m_ids.Add(wxT("gtk-goto-top"));
			m_ids.Add(wxT("gtk-go-back"));
			m_ids.Add(wxT("gtk-go-down"));
			m_ids.Add(wxT("gtk-go-forward"));
			m_ids.Add(wxT("gtk-go-up"));
			m_ids.Add(wxT("gtk-harddisk"));
			m_ids.Add(wxT("gtk-indent"));
			m_ids.Add(wxT("gtk-index"));
			m_ids.Add(wxT("gtk-info"));
			m_ids.Add(wxT("gtk-italic"));
			m_ids.Add(wxT("gtk-jump-to"));
			m_ids.Add(wxT("gtk-justify-center"));
			m_ids.Add(wxT("gtk-justify-fill"));
			m_ids.Add(wxT("gtk-justify-left"));
			m_ids.Add(wxT("gtk-justify-right"));
			m_ids.Add(wxT("gtk-leave-fullscreen"));
			m_ids.Add(wxT("gtk-media-forward"));
			m_ids.Add(wxT("gtk-media-next"));
			m_ids.Add(wxT("gtk-media-forward"));
			m_ids.Add(wxT("gtk-media-pause"));
			m_ids.Add(wxT("gtk-media-play"));
			m_ids.Add(wxT("gtk-media-previous"));
			m_ids.Add(wxT("gtk-media-record"));
			m_ids.Add(wxT("gtk-media-rewind"));
			m_ids.Add(wxT("gtk-media-stop"));
			m_ids.Add(wxT("gtk-missing-image"));
			m_ids.Add(wxT("gtk-network"));
			m_ids.Add(wxT("gtk-new"));
			m_ids.Add(wxT("gtk-no"));
			m_ids.Add(wxT("gtk-ok"));
			m_ids.Add(wxT("gtk-open"));
			m_ids.Add(wxT("gtk-orientation-landscape"));
			m_ids.Add(wxT("gtk-orientation-portrait"));
			m_ids.Add(wxT("gtk-orientation-reverse-landscape"));
			m_ids.Add(wxT("gtk-orientation-reverse-portrait"));
			m_ids.Add(wxT("gtk-page-setup"));
			m_ids.Add(wxT("gtk-paste"));
			m_ids.Add(wxT("gtk-preferences"));
			m_ids.Add(wxT("gtk-print"));
			m_ids.Add(wxT("gtk-print-paused"));
			m_ids.Add(wxT("gtk-print-report"));
			m_ids.Add(wxT("gtk-print-warning"));
			m_ids.Add(wxT("gtk-properties"));
			m_ids.Add(wxT("gtk-quit"));
			m_ids.Add(wxT("gtk-redo"));
			m_ids.Add(wxT("gtk-refresh"));
			m_ids.Add(wxT("gtk-remove"));
			m_ids.Add(wxT("gtk-save"));
			m_ids.Add(wxT("gtk-save-as"));
			m_ids.Add(wxT("gtk-select-all"));
			m_ids.Add(wxT("gtk-select-color"));
			m_ids.Add(wxT("gtk-select-font"));
			m_ids.Add(wxT("gtk-sort-ascending"));
			m_ids.Add(wxT("gtk-sort-descending"));
			m_ids.Add(wxT("gtk-spell-check"));
			m_ids.Add(wxT("gtk-stop"));
			m_ids.Add(wxT("gtk-strikethrough"));
			m_ids.Add(wxT("gtk-undelete"));
			m_ids.Add(wxT("gtk-underline"));
			m_ids.Add(wxT("gtk-undo"));
			m_ids.Add(wxT("gtk-unindent"));
			m_ids.Add(wxT("gtk-yes"));
			m_ids.Add(wxT("gtk-zoom-100"));
			m_ids.Add(wxT("gtk-zoom-fit"));
			m_ids.Add(wxT("gtk-zoom-in"));
			m_ids.Add(wxT("gtk-zoom-out"));
		}
		
		wxPGProperty* child = new wxEnumProperty( wxT("id"), wxPG_LABEL, m_ids, m_ids.Index( m_id ) );
		AddPrivateChild( child );
		child->SetHelpString( _("wxArtID unique identifier of the bitmap. IDs with prefix 'gtk-' are available under wxGTK only.") );
		
		if( m_clients.IsEmpty() )
		{
			m_clients.Add(wxT("wxART_TOOLBAR"));
			m_clients.Add(wxT("wxART_MENU"));
			m_clients.Add(wxT("wxART_BUTTON"));
			m_clients.Add(wxT("wxART_FRAME_ICON"));
			m_clients.Add(wxT("wxART_CMN_DIALOG"));
			m_clients.Add(wxT("wxART_HELP_BROWSER"));
			m_clients.Add(wxT("wxART_MESSAGE_BOX"));
			m_clients.Add(wxT("wxART_OTHER"));
		}
		
		child = new wxEnumProperty( wxT("client"), wxPG_LABEL, m_clients, m_clients.Index( m_client ) );
		AddPrivateChild( child );
		child->SetHelpString( _("wxArtClient identifier of the client (i.e. who is asking for the bitmap).") );
	}
	else
	{
		wxPGProperty* child = new wxStringProperty( wxT("resource_name"), wxPG_LABEL, m_image );
		AddPrivateChild( child );
		child->SetHelpString( _("Windows Only. Name of the resource in the .rc file.") );
	}

	wxPGProperty* child2 = new wxEnumProperty(wxT("source"), wxPG_LABEL, m_strings, m_strings.Index( m_source ) );
	AddPrivateChild( child2 );
	child2->SetHelpString( 	wxString(_("Load From File:\n") ) +
							wxString(_("Load the image from a file on disk.\n\n") ) +
							wxString(_("Load From Embedded File:\n") ) +
							wxString(_("C++ Only. Embed the image file in the exe and load it.\nFor other languages, behaves like \"Load From File\".\n\n") ) +
							wxString(_("Load From Resource:\n") ) +
							wxString(_("Windows Only. Load the image from a BITMAP resource in a .rc file\n\n") ) +
							wxString(_("Load From Icon Resource:\n") ) +
							wxString(_("Windows Only. Load the image from a ICON resource in a .rc file\n\n") ) +
							wxString(_("Load From Art Provider:\n") ) +
							wxString(_("Query registered providers for bitmap with given ID.\n\n") )
						);

    if ( m_source == _("Load From Icon Resource") )
    {
        wxPGProperty* child3 = new wxSizeProperty(wxT("ico_size"), wxPG_LABEL, wxDefaultSize);
        AddPrivateChild( child3 );
        child3->SetHelpString( _("The size of the icon to use from a ICON resource with multiple icons in it.") );
    }

	RefreshChildren();
}

wxBitmapWithResourceProperty::~wxBitmapWithResourceProperty()
{

}

void wxBitmapWithResourceProperty::DoSetValue ( wxVariant value )
{
	wxString newValue = value.GetString();

    TypeConv::ParseBitmapWithResource( newValue, &m_image, &m_source, &m_icoSize );

	if ( wxNOT_FOUND == m_strings.Index( m_source.c_str() ) )
    {
        m_source = _("Load From File");
    }
	else if( m_source == _("Load From Art Provider") )
	{
		m_id = m_image.BeforeFirst( wxT(':') );
		m_client = m_image.AfterFirst( wxT(':') );
	}

	RefreshChildren();
}

wxVariant wxBitmapWithResourceProperty::DoGetValue() const
{
	wxString value;
	value.Printf( wxT("%s; %s [%i; %i]"), m_image.c_str(), m_source.c_str(), m_icoSize.GetWidth(), m_icoSize.GetHeight() );
	
	return wxVariant( value );
}

void wxBitmapWithResourceProperty::RefreshChildren()
{
    size_t count = GetChildCount();
	if ( 0 == count )
	{
		return;
	}
	
	if( m_source != _("Load From Art Provider") )
	{
		if ( 3 == count )
		{
			wxVariant variant; variant << m_icoSize;
			Item( 2 )->SetValue( variant );
		}
		Item( ITEM_FILE_OR_RESOURCE )->SetValue( m_image );
		Item( ITEM_SOURCE )->SetValue( m_strings.Index( m_source ) );
	}
	else
	{
		Item( 0 )->SetValue( m_ids.Index( m_id ) );
		Item( 1 )->SetValue( m_clients.Index( m_client ) );
		Item( 2 )->SetValue( m_strings.Index( m_source ) );
	}
}

wxVariant wxBitmapWithResourceProperty::ChildChanged( wxVariant& thisValue,
                                                           int childIndex,
                                                           wxVariant& childValue ) const
{
	wxString  path = thisValue.GetString();
	wxVariant variant;

	switch ( childIndex )
	{
	case 0:
	
	case 1:
	
	default:
		g_imageFilterIndex = 0;

		wxFileName imgPath( path );
		g_imageInitialPath = imgPath.GetPath();
	}

    wxVariant newVariant;
    newVariant = wxVariant( path );
    return newVariant;
}

// -----------------------------------------------------------------------
// ObjectInspector
// -----------------------------------------------------------------------
//DECLARE_EVENT_TYPE( RECREATE_GRID_EVENT, -1 )
DEFINE_EVENT_TYPE( RECREATE_GRID_EVENT )

BEGIN_EVENT_TABLE(ObjectInspector, wxPanel)
	EVT_PG_CHANGED(WXFB_PROPERTY_GRID, ObjectInspector::OnPropertyGridChange)
	EVT_PG_CHANGED(WXFB_EVENT_GRID, ObjectInspector::OnEventGridChange)
//	EVT_PG_DOUBLE_CLICK(WXFB_EVENT_GRID, ObjectInspector::OnEventGridDblClick)
//	EVT_PG_DOUBLE_CLICK(WXFB_PROPERTY_GRID, ObjectInspector::OnPropertyGridDblClick)
	EVT_PG_ITEM_COLLAPSED(WXFB_PROPERTY_GRID, ObjectInspector::OnPropertyGridExpand)
	EVT_PG_ITEM_EXPANDED (WXFB_PROPERTY_GRID, ObjectInspector::OnPropertyGridExpand)

	EVT_COMMAND( wxID_ANY, RECREATE_GRID_EVENT, ObjectInspector::OnReCreateGrid )

	EVT_FB_OBJECT_SELECTED( ObjectInspector::OnObjectSelected )
	EVT_FB_PROJECT_REFRESH( ObjectInspector::OnProjectRefresh )
	EVT_FB_PROPERTY_MODIFIED( ObjectInspector::OnPropertyModified )
	EVT_FB_EVENT_HANDLER_MODIFIED( ObjectInspector::OnEventHandlerModified )

END_EVENT_TABLE()

ObjectInspector::ObjectInspector( wxWindow* parent, int id, int style )
: wxPanel(parent,id), m_style(style)
{
	AppData()->AddHandler( this->GetEventHandler() );
	m_currentSel = PObjectBase();

	long nbStyle;

	wxConfigBase* config = wxConfigBase::Get();

#ifdef WXFB_USE_AUIBOOK
    config->Read( wxT("/mainframe/objectInspector/auinbook_style"), &nbStyle, wxAUI_NB_WINDOWLIST_BUTTON | wxAUI_NB_SCROLL_BUTTONS );

    m_nb = new wxAuiNotebook( this, -1, wxDefaultPosition, wxDefaultSize, nbStyle );
#else
	config->Read( wxT("/mainframe/objectInspector/notebook_style"), &nbStyle, wxFNB_NO_X_BUTTON | wxFNB_NO_NAV_BUTTONS | wxFNB_NODRAG | wxFNB_DROPDOWN_TABS_LIST | wxFNB_FF2 | wxFNB_CUSTOM_DLG );

	m_nb = new wxFlatNotebook( this, -1, wxDefaultPosition, wxDefaultSize, FNB_STYLE_OVERRIDES( nbStyle ) );
	m_nb->SetCustomizeOptions( wxFNB_CUSTOM_TAB_LOOK | wxFNB_CUSTOM_ORIENTATION | wxFNB_CUSTOM_LOCAL_DRAG );

	m_icons.Add( AppBitmaps::GetBitmap( wxT("properties"), 16 ) );
	m_icons.Add( AppBitmaps::GetBitmap( wxT("events"), 16 ) );
	m_nb->SetImageList( &m_icons );
#endif
	// the colour of property grid description looks ugly if we don't set this
	// colour
	m_nb->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_3DFACE));

	// Register the slider editor
#if wxUSE_SLIDER
//	wxPGRegisterEditorClass( Slider );
#endif

	m_pg = CreatePropertyGridManager(m_nb, WXFB_PROPERTY_GRID);
	m_eg = CreatePropertyGridManager(m_nb, WXFB_EVENT_GRID);

#ifdef WXFB_USE_AUIBOOK
	m_nb->AddPage( m_pg, _("Properties"), false, AppBitmaps::GetBitmap( wxT("properties"), 16 ) );
	m_nb->AddPage( m_eg, _("Events"),     false, AppBitmaps::GetBitmap( wxT("events"), 16 ) );
#else
	m_nb->AddPage( m_pg, _("Properties"), false, 0 );
	m_nb->AddPage( m_eg, _("Events"),     false, 1 );
#endif
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
	// Save Layout
	wxConfigBase* config = wxConfigBase::Get();
	config->Write( wxT("/mainframe/objectInspector/DescBoxHeight" ), m_pg->GetDescBoxHeight() );
#ifdef WXFB_USE_AUIBOOK
    config->Write( wxT("/mainframe/objectInspector/auinbook_style"), m_nb->GetWindowStyleFlag() );
#else
	config->Write( wxT("/mainframe/objectInspector/notebook_style"), m_nb->GetWindowStyleFlag() );
#endif
}

void ObjectInspector::Create( bool force )
{
	PObjectBase sel_obj = AppData()->GetSelectedObject();
	if ( sel_obj && ( sel_obj != m_currentSel || force ) )
	{
		Freeze();

		m_currentSel = sel_obj;

		int pageNumber = m_pg->GetSelectedPage();
		wxString pageName;
		if ( pageNumber != wxNOT_FOUND )
		{
			pageName = m_pg->GetPageName( pageNumber );
		}

		// Clear Property Grid Manager
		int pageCount = (int)m_pg->GetPageCount();
		if ( pageCount > 0 )
		{
			for ( int pageIndex = pageCount - 1; pageIndex >= 0; --pageIndex )
			{
				m_pg->RemovePage( pageIndex );
			}
		}

		// now we do the same thing for event grid...
		pageCount = (int)m_eg->GetPageCount();
		if ( pageCount > 0)
		{
		  for ( int pageIndex = pageCount - 1; pageIndex >= 0; --pageIndex)
		  {
		    m_eg->RemovePage( pageIndex );
		  }
		}

		m_propMap.clear();
		m_eventMap.clear();

		PObjectInfo obj_desc = sel_obj->GetObjectInfo();
		if (obj_desc)
		{

			PropertyMap propMap, dummyPropMap;
			EventMap eventMap, dummyEventMap;

			// We create the categories with the properties of the object organized by "classes"
			CreateCategory( obj_desc->GetClassName(), sel_obj, obj_desc, propMap, false );
			CreateCategory( obj_desc->GetClassName(), sel_obj, obj_desc, eventMap, true );

			for (unsigned int i=0; i<obj_desc->GetBaseClassCount() ; i++)
			{
				PObjectInfo info_base = obj_desc->GetBaseClass(i);
				CreateCategory( info_base->GetClassName(), sel_obj, info_base, propMap, false );
				CreateCategory( info_base->GetClassName(), sel_obj, info_base, eventMap, true );
			}

			PObjectBase parent = sel_obj->GetParent();
			if ( parent )
			{
				PObjectInfo parent_desc = parent->GetObjectInfo();
				if ( parent_desc->GetObjectType()->IsItem())
				{
					CreateCategory( parent_desc->GetClassName(), parent, parent_desc, dummyPropMap, false );
					CreateCategory( parent_desc->GetClassName(), parent, parent_desc, dummyEventMap, true );

					for (unsigned int i=0; i<parent_desc->GetBaseClassCount() ; i++)
					{
						PObjectInfo info_base = parent_desc->GetBaseClass(i);
						CreateCategory( info_base->GetClassName(), parent, info_base, dummyPropMap, false );
						CreateCategory( info_base->GetClassName(), parent, info_base, dummyEventMap, true );
					}
				}
			}

			// Select previously selected page, or first page
			if ( m_pg->GetPageCount() > 0 )
			{
				int pageIndex = m_pg->GetPageByName( pageName );
				if ( wxNOT_FOUND != pageIndex )
				{
					m_pg->SelectPage( pageIndex );
				}
				else
				{
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
	while (strTok.HasMoreTokens())
	{
		wxString token = strTok.GetNextToken();
		unsigned int i = 0;
		bool done = false;
		while (i < constants.GetCount() && !done)
		{
			if (constants.GetLabel(i) == token)
			{
				val |= constants.GetValue(i);
				done = true;
			}
			i++;
		}
	}
	return val;
}

wxPGProperty* ObjectInspector::GetProperty( PProperty prop )
{
	wxPGProperty *result = NULL;
	PropertyType type = prop->GetType();
	wxString name = prop->GetName();
	wxVariant vTrue = wxVariant( true, wxT("true") );

	if (type == PT_MACRO)
	{
		result = new wxStringProperty( name, wxPG_LABEL, prop->GetValueAsString() );
	}
	else if (type == PT_INT)
	{
		result = new wxIntProperty( name, wxPG_LABEL, prop->GetValueAsInteger() );
	}
	else if (type == PT_UINT)
	{
		result = new wxUIntProperty( name, wxPG_LABEL, (unsigned)prop->GetValueAsInteger() );
	}
  	else if (type == PT_WXSTRING || type == PT_WXSTRING_I18N)
  	{
		result = new wxLongStringProperty( name, wxPG_LABEL, prop->GetValueAsText() );
  	}
  	else if (type == PT_TEXT)
	{
		result = new wxLongStringProperty( name, wxPG_LABEL, prop->GetValueAsString() );
		result->ChangeFlag( wxPG_PROP_NO_ESCAPE, true );
	}
	else if (type == PT_BOOL)
	{
		result = new wxBoolProperty( name, wxPG_LABEL, prop->GetValue() == "1" );
	}
	else if (type == PT_BITLIST)
	{
		PPropertyInfo prop_desc = prop->GetPropertyInfo();
		POptionList opt_list = prop_desc->GetOptionList();

		assert(opt_list && opt_list->GetOptionCount() > 0);

		wxPGChoices constants;
		const std::map< wxString, wxString > options = opt_list->GetOptions();
		std::map< wxString, wxString >::const_iterator it;
		unsigned int i = 0;
		for( it = options.begin(); it != options.end(); ++it )
		{
			constants.Add( it->first, 1 << i++ );
		}

		int val = StringToBits(prop->GetValueAsString(), constants);
		result = new wxFlagsProperty(name, wxPG_LABEL, constants, val);

		// Workaround to set the help strings for individual members of a wxFlagsProperty
		wxFlagsProperty* flagsProp = dynamic_cast< wxFlagsProperty* >( result );
		if ( NULL != flagsProp )
		{
			for ( size_t i = 0; i < flagsProp->GetItemCount(); i++ )
			{
				wxPGProperty* prop = flagsProp->Item( i );
				std::map< wxString, wxString >::const_iterator option = options.find( prop->GetLabel() );
				if ( option != options.end() )
				{
					m_pg->SetPropertyHelpString( prop, option->second );
				}
			}
		}
	}
	else if (type == PT_INTLIST || type == PT_UINTLIST)
	{
		result = new wxStringProperty( name, wxPG_LABEL, IntList( prop->GetValueAsString(), type == PT_UINTLIST ).ToString() );
	}
	else if (type == PT_OPTION)
	{
		PPropertyInfo prop_desc = prop->GetPropertyInfo();
		POptionList opt_list = prop_desc->GetOptionList();

		assert(opt_list && opt_list->GetOptionCount() > 0);

		wxString value = prop->GetValueAsString();
		wxString help;

		wxPGChoices constants;
		const std::map< wxString, wxString > options = opt_list->GetOptions();
		std::map< wxString, wxString >::const_iterator it;
		unsigned int i = 0;
		for( it = options.begin(); it != options.end(); ++it )
		{
			constants.Add( it->first, i++ );
			if ( it->first == value )
			{
				// Save help
				help = it->second;
			}
		}

		result = new wxEnumProperty( name, wxPG_LABEL, constants );
		result->SetValueFromString( value, 0 );
		wxString desc = prop_desc->GetDescription();
		if ( desc.empty() )
		{
			desc = value + wxT(":\n") + help;
		}
		else
		{
			desc += wxT("\n\n") + value + wxT(":\n") + help;
		}
		result->SetHelpString( wxGetTranslation( desc ) );

	}
	else if (type == PT_WXPOINT)
	{
		result = new wxPointProperty( name, wxPG_LABEL, prop->GetValueAsPoint() );
	}
	else if (type == PT_WXSIZE)
	{
		result = new wxSizeProperty( name, wxPG_LABEL, prop->GetValueAsSize() );
	}
	else if (type == PT_WXFONT)
	{
		wxFontContainer container = TypeConv::StringToFont( prop->GetValueAsString() );
		result = new wxFontProperty( name, wxPG_LABEL, container.GetFont() );
	}
	else if (type == PT_WXCOLOUR)
	{
		wxString value = prop->GetValueAsString();
		if ( value.empty() )  // Default Colour
		{
			wxColourPropertyValue def;
			def.m_type = wxSYS_COLOUR_WINDOW;
			result = new wxSystemColourProperty( name, wxPG_LABEL, def );
		}
		else
		{
			if ( value.find_first_of( wxT("wx") ) == 0 )
			{
				// System Colour
				wxColourPropertyValue def;
				def.m_type = TypeConv::StringToSystemColour( value );
				result = new wxSystemColourProperty( name, wxPG_LABEL, def );
			}
			else
			{
				result = new wxSystemColourProperty( name, wxPG_LABEL, prop->GetValueAsColour() );
			}
		}
	}
	else if (type == PT_PATH)
	{
		result = new wxDirProperty( name, wxPG_LABEL, prop->GetValueAsString() );
	}
	else if (type == PT_FILE)
	{
		result = new wxFileProperty( name, wxPG_LABEL, prop->GetValueAsString() );
	}
	else if (type == PT_BITMAP)
	{
		result = new wxBitmapWithResourceProperty( name, wxPG_LABEL, prop->GetValueAsString() ); // TODO: wxBitmapWithResourceProperty
	}
	else if (type == PT_STRINGLIST)
	{
		result = new wxArrayStringProperty( name, wxPG_LABEL,prop->GetValueAsArrayString() );
	}
	else if (type == PT_FLOAT)
	{
		result = new wxFloatProperty( name, wxPG_LABEL,prop->GetValueAsFloat() );
	}
	else if ( type == PT_PARENT )
	{
//		wxPGProperty* parent = new wxPGProperty( name, wxPG_LABEL );
		wxPGProperty* parent = new wxStringProperty( name, wxPG_LABEL, "<composed>" );

		PPropertyInfo prop_desc = prop->GetPropertyInfo();
		std::list< PropertyChild >* children = prop_desc->GetChildren();
		std::list< PropertyChild >::iterator it;
		for ( it = children->begin(); it != children->end(); ++it )
		{
			wxPGProperty* child = new wxStringProperty( it->m_name, wxPG_LABEL, wxEmptyString );
			parent->AppendChild( child );
			m_pg->SetPropertyHelpString( child, it->m_description );
		}

//		parent->SetValueFromString( prop->GetValueAsString(), wxPG_FULL_VALUE );
		parent->SetValueFromString( prop->GetValueAsString() );
		result = parent;
	}
	else // propiedad desconocida
	{
		result = new wxStringProperty( name, wxPG_LABEL, prop->GetValueAsString() );
		result->SetAttribute( wxPG_BOOL_USE_DOUBLE_CLICK_CYCLING, vTrue );
		wxLogError(_("Property type Unknown") );
	}

	return result;
}

void ObjectInspector::AddItems( const wxString& name, PObjectBase obj,
  PObjectInfo obj_info, PPropertyCategory category, PropertyMap &properties )
{
	size_t propCount = category->GetPropertyCount();
	for ( size_t i = 0; i < propCount; i++ )
	{
		wxString propName = category->GetPropertyName( i );
		PProperty prop = obj->GetProperty( propName );

		if ( !prop )
			continue;

		PPropertyInfo propInfo = prop->GetPropertyInfo();

		// we do not want to duplicate inherited properties
		if ( properties.find( propName ) == properties.end() )
		{

			wxPGProperty* id = m_pg->Append( GetProperty( prop ) );
			if ( prop->GetType() != PT_OPTION )
			{
				m_pg->SetPropertyHelpString( id, propInfo->GetDescription() );
			}
			wxString customEditor = propInfo->GetCustomEditor();
			if ( !customEditor.empty() )
			{
				wxPGEditor* editor = m_pg->GetEditorByName( customEditor );
				if ( editor )
				{
					m_pg->SetPropertyEditor( id, editor );
				}
			}

			if (m_style != wxFB_OI_MULTIPAGE_STYLE)
			{
				// Most common classes will be showed with a slightly different
				// colour.
				if (name == wxT("wxWindow"))
					m_pg->SetPropertyBackgroundColour(id,wxColour(255,255,205)); // yellow
				else if (name == wxT("sizeritem") || name == wxT("gbsizeritem") || name == wxT("sizeritembase") )
					m_pg->SetPropertyBackgroundColour(id,wxColour(220,255,255)); // cyan
			}

			ExpandMap::iterator it = m_isExpanded.find( propName );
			if ( it != m_isExpanded.end() )
			{
				id->SetExpanded( it->second );
			}

			properties.insert( PropertyMap::value_type( propName, prop ) );
			m_propMap.insert( ObjInspectorPropertyMap::value_type( id, prop ) );
		}
	}

	size_t catCount = category->GetCategoryCount();
	for ( size_t i = 0; i < catCount; i++ )
	{
		PPropertyCategory nextCat = category->GetCategory( i );
		if ( 0 == nextCat->GetCategoryCount() && 0 == nextCat->GetPropertyCount() )
		{
			continue;
		}
		wxPGProperty* catId = m_pg->AppendIn( category->GetName() , new wxPropertyCategory( nextCat->GetName() ) );
		ExpandMap::iterator it = m_isExpanded.find( nextCat->GetName() );
		if ( it != m_isExpanded.end() )
		{
			catId->SetExpanded( it->second );
		}

		AddItems( name, obj, obj_info, nextCat, properties );
	}
}

void ObjectInspector::AddItems( const wxString& name, PObjectBase obj,
  PObjectInfo obj_info, PPropertyCategory category, EventMap &events )
{
	size_t eventCount = category->GetEventCount();
	for ( size_t i = 0; i < eventCount; i++ )
	{
		wxString eventName = category->GetEventName( i );
		PEvent event = obj->GetEvent( eventName );

		if ( !event )
			continue;

		PEventInfo eventInfo = event->GetEventInfo();

		// we do not want to duplicate inherited events
		if ( events.find( eventName ) == events.end() )
		{
			wxPGProperty* pgProp = new wxStringProperty( eventInfo->GetName(), wxPG_LABEL, event->GetValue() );
			wxPGProperty* id = m_eg->Append( pgProp );

			m_eg->SetPropertyHelpString( id, wxGetTranslation( eventInfo->GetDescription() ) );

			if (m_style != wxFB_OI_MULTIPAGE_STYLE)
			{
				// Most common classes will be showed with a slightly different
				// colour.
				if (name == wxT("wxWindow"))
					m_eg->SetPropertyBackgroundColour( id, wxColour( 255, 255, 205 ) ); // Yellow
				else if (name == wxT("sizeritem") || name == wxT("gbsizeritem") || name == wxT("sizeritembase") )
					m_eg->SetPropertyBackgroundColour( id, wxColour( 220, 255, 255 ) ); // Cyan
			}

			events.insert( EventMap::value_type( eventName, event ) );
			m_eventMap.insert( ObjInspectorEventMap::value_type( id, event ) );
		}
	}

	size_t catCount = category->GetCategoryCount();
	for ( size_t i = 0; i < catCount; i++ )
	{
		PPropertyCategory nextCat = category->GetCategory( i );
		if ( 0 == nextCat->GetCategoryCount() && 0 == nextCat->GetEventCount() )
		{
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

	if ( m_propMap.end() == it )
	{
		// Could be a child property
		propPtr = propPtr->GetParent();
		it = m_propMap.find( propPtr );
	}

	if ( it != m_propMap.end() )
	{
		PProperty prop = it->second;
		switch ( prop->GetType() )
		{

			case PT_FLOAT:
			{
				// Use typeconv to properly handle locale
				double val = m_pg->GetPropertyValueAsDouble( propPtr );
				AppData()->ModifyProperty( prop, TypeConv::FloatToString( val ) );
				break;
			}
			case PT_TEXT:
			case PT_MACRO:
			case PT_INT:
			case PT_UINT:
			{
				AppData()->ModifyProperty( prop, m_pg->GetPropertyValueAsString( propPtr ) );
				break;
			}
			case PT_OPTION:
			{
				wxString value = m_pg->GetPropertyValueAsString( propPtr );
				AppData()->ModifyProperty( prop, value );

				// Update displayed description for the new selection
				PPropertyInfo prop_desc = prop->GetPropertyInfo();
				POptionList opt_list = prop_desc->GetOptionList();

				wxString helpString = prop_desc->GetDescription();
				if ( opt_list && opt_list->GetOptionCount() > 0 )
				{
					const std::map< wxString, wxString > options = opt_list->GetOptions();
					std::map< wxString, wxString >::const_iterator option = options.find( value );
					if ( option != options.end() )
					{
						if ( helpString.empty() )
						{
							helpString = value + wxT(":\n") + option->second;
						}
						else
						{
							helpString += wxT("\n\n") + value + wxT(":\n") + option->second;
						}
					}
				}
				wxString localized = wxGetTranslation( helpString );
				m_pg->SetPropertyHelpString( propPtr, localized );
				m_pg->SetDescription( propPtr->GetLabel(), localized );
				break;
			}
			case PT_PARENT:
			{
				AppData()->ModifyProperty( prop, propPtr->GetValueAsString( wxPG_FULL_VALUE ) );
				break;
			}
			case PT_WXSTRING:
			case PT_WXSTRING_I18N:
			{
				// las cadenas de texto del inspector son formateadas
				wxString value = m_pg->GetPropertyValueAsString( propPtr );
				AppData()->ModifyProperty( prop, value );
				break;
			}
			case PT_BOOL:
			{
				if( prop->GetName() == wxT("aui_managed") )
				{
					PObjectBase propobj = prop->GetObject();
					if( propobj->GetChildCount() )
					{
						wxMessageBox(_("You have to remove all child widgets first."));
						
						// modified property must be reverted to its original form later.
						wxCommandEvent e( RECREATE_GRID_EVENT );
						e.SetString( event.GetPropertyName() );
						AddPendingEvent( e );
					}
					else
						AppData()->ModifyProperty( prop, m_pg->GetPropertyValueAsBool( propPtr ) ? wxT("1") : wxT("0") );
				}
				else
					AppData()->ModifyProperty( prop, m_pg->GetPropertyValueAsBool( propPtr ) ? wxT("1") : wxT("0") );
				break;
			}
			case PT_BITLIST:
			{
				wxString aux = m_pg->GetPropertyValueAsString( propPtr );
				aux.Replace( wxT(" "), wxT("") );
				aux.Replace( wxT(","), wxT("|") );
				AppData()->ModifyProperty( prop, aux );
				break;
			}
			case PT_WXPOINT:
			{
				wxPoint point = wxPointRefFromVariant( event.GetPropertyValue () );
				AppData()->ModifyProperty( prop, wxString::Format(  wxT("%i,%i"), point.x, point.y ) );
				break;
			}
			case PT_WXSIZE:
			{
				wxSize size = wxSizeRefFromVariant( event.GetPropertyValue() );
				AppData()->ModifyProperty( prop, wxString::Format( wxT("%i,%i"), size.GetWidth(), size.GetHeight() ) );
				break;
			}
			case PT_WXFONT:
			{
				wxFont font;
				font << event.GetPropertyValue() ;
				wxFontContainer container( 	font.GetPointSize(),
											font.GetFamily(),
											font.GetStyle(),
											font.GetWeight(),
											font.GetUnderlined(),
											font.GetFaceName() );
				AppData()->ModifyProperty( prop, TypeConv::FontToString( container ) );
				break;
			}
			case PT_WXCOLOUR:
			{
				wxColourPropertyValue colour;
				colour << event.GetPropertyValue();
				switch ( colour.m_type ) {
				case wxSYS_COLOUR_MAX:
					AppData()->ModifyProperty( prop, wxT("") );
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
			case PT_UINTLIST:
			{
				IntList il( event.GetPropertyValue(), PT_UINTLIST == prop->GetType() );
				AppData()->ModifyProperty( prop, il.ToString() );
				break;
			}
			case PT_BITMAP:
			{
			    // Get property value
				wxString path = m_pg->GetPropertyValueAsString( propPtr );
				size_t semicolon_index = path.find_first_of( wxT(";") );
				if ( semicolon_index != path.npos )
				{
					path = TypeConv::MakeRelativeURL( path.substr( 0, semicolon_index ), AppData()->GetProjectPath() ) + path.substr( semicolon_index  );
				}

				// Save state from old property to use after grid is recreated
				wxPGProperty* pwc = dynamic_cast< wxPGProperty* >( event.GetProperty() );
				bool expanded = false;
				if ( pwc )
				{
					expanded = pwc->IsExpanded();
				}
				wxString name = event.GetPropertyName();

				// Respond to property modification
				AppData()->ModifyProperty( prop, path );

                // It is bad to delete the property while handling an event from it!
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
    // Recreate grid, the bitmap property may need to change
    Create( true );

    // Re-expand the bitmap property, if it was expanded
	wxPGProperty* bitmapProp = m_pg->GetPropertyByName( event.GetString() );
	if( bitmapProp )
	{
		m_pg->SelectProperty( bitmapProp );
		if ( event.GetInt() != 0 )
		{
			m_pg->Expand( bitmapProp );
			m_pg->Expand( dynamic_cast< wxPGProperty* >( bitmapProp )->Last() );
		}
	}
}

void ObjectInspector::OnEventGridChange(wxPropertyGridEvent& event)
{
	ObjInspectorEventMap::iterator it = m_eventMap.find( event.GetProperty() );

	if ( it != m_eventMap.end() )
	{
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
void ObjectInspector::OnObjectSelected( wxFBObjectEvent& event)
{
	if( event.GetString() == wxT("force") )	Create(true);
	else
		Create(false);
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
	if ( !shouldContinue )
	{
		// Item objects cannot be selected - their children are selected instead
		if ( propobj->GetObjectInfo()->GetObjectType()->IsItem() )
		{
			if ( propobj->GetChildCount() > 0 )
			{
				shouldContinue = ( appobj == propobj->GetChild( 0 ) );
			}
		}
	}
	if ( !shouldContinue )
	{
		return;
	}

	wxPGProperty* pgProp = m_pg->GetPropertyByLabel(prop->GetName() );
	if ( pgProp == NULL ) return; // Puede que no se esté mostrando ahora esa página


	switch (prop->GetType())
	{
	case PT_FLOAT:
	{
		// use float instead of string -> typeconv handles locale
		pgProp->SetValue( wxVariant( prop->GetValueAsFloat() ) );
		break;
	}
	case PT_INT:
	case PT_UINT:
	{
		pgProp->SetValueFromString(prop->GetValueAsString(), 0);
		break;
	}
	case PT_TEXT:
		pgProp->SetValueFromString(prop->GetValueAsString(), 0);
		break;
	case PT_MACRO:
	case PT_OPTION:
	case PT_PARENT:
	case PT_WXSTRING:
		pgProp->SetValueFromString(prop->GetValueAsText(), 0);
		break;
	case PT_WXSTRING_I18N:
		pgProp->SetValueFromString(prop->GetValueAsText(), 0);
		break;
	case PT_BOOL:
		pgProp->SetValueFromInt(prop->GetValueAsString() == wxT("0") ? 0 : 1, 0);
		break;
	case PT_BITLIST:
		{
			wxString aux = prop->GetValueAsString();
			aux.Replace(wxT("|"), wxT(", "));
			if (aux == wxT("0")) aux = wxT("");
			pgProp->SetValueFromString(aux, 0);
		}
		break;
	case PT_WXPOINT:
		m_pg->SetPropertyValue( pgProp, prop->GetValue() );
		break;
	case PT_WXSIZE:
		m_pg->SetPropertyValue( pgProp, prop->GetValue() );
		break;
	case PT_WXFONT:
		{
			wxFontContainer container = TypeConv::StringToFont( prop->GetValueAsString() );
			wxVariant value;
			value << container.GetFont();
			pgProp->SetValue( value );




		}
		break;
	case PT_WXCOLOUR:
		{
			wxString value = prop->GetValueAsString();
			if ( value.empty() )  // Default Colour
			{
				wxColourPropertyValue def; def.m_type = wxSYS_COLOUR_WINDOW;
				m_pg->SetPropertyValue( pgProp, def );
			}
			else
			{
				if ( value.find_first_of( wxT("wx") ) == 0 )
				{
					// System Colour
					wxColourPropertyValue def;
					def.m_type = TypeConv::StringToSystemColour( value );
					def.m_colour = prop->GetValueAsColour();
					m_pg->SetPropertyValue( pgProp, def );
				}
				else
				{
					wxColourPropertyValue def( wxPG_COLOUR_CUSTOM, prop->GetValueAsColour() );
					m_pg->SetPropertyValue( pgProp, def );
				}
			}
		}
		break;
	case PT_BITMAP:
		break;
	default:
		pgProp->SetValueFromString(prop->GetValueAsString(), wxPG_FULL_VALUE);
	}
//	AutoGenerateId(AppData()->GetSelectedObject(), event.GetFBProperty(), wxT("PropChange"));
//	m_pg->Refresh();
}

wxPropertyGridManager* ObjectInspector::CreatePropertyGridManager(wxWindow *parent, wxWindowID id)
{
	int pgStyle;
	int defaultDescBoxHeight;

	switch (m_style)
	{
		case wxFB_OI_MULTIPAGE_STYLE:

			pgStyle = 	wxPG_BOLD_MODIFIED | wxPG_SPLITTER_AUTO_CENTER | wxPG_TOOLBAR |
						wxPG_DESCRIPTION | wxPGMAN_DEFAULT_STYLE;
			defaultDescBoxHeight = 50;
			break;

		case wxFB_OI_DEFAULT_STYLE:
		case wxFB_OI_SINGLE_PAGE_STYLE:
		default:

			pgStyle = 	wxPG_BOLD_MODIFIED | wxPG_SPLITTER_AUTO_CENTER | wxPG_DESCRIPTION |
						wxPGMAN_DEFAULT_STYLE;
			defaultDescBoxHeight = 150;
			break;
	}

	int descBoxHeight;
	wxConfigBase* config = wxConfigBase::Get();
	config->Read( wxT( "/mainframe/objectInspector/DescBoxHeight" ), &descBoxHeight, defaultDescBoxHeight );
	if ( -1 == descBoxHeight )
	{
		descBoxHeight = defaultDescBoxHeight;
	}

	wxPropertyGridManager* pg;
	pg = new wxPropertyGridManager( parent, id, wxDefaultPosition, wxDefaultSize, pgStyle );
	pg->SetDescBoxHeight( descBoxHeight );
	pg->SetExtraStyle( wxPG_EX_NATIVE_DOUBLE_BUFFERING );
//	pg->SetExtraStyle( wxPG_EX_PROCESS_EVENTS_IMMEDIATELY );

	return pg;
}
