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
// Modified by
//   Andrea Zanellato - zanellato.andrea@gmail.com
//   This code was part of previous objtree.cpp version.
//
///////////////////////////////////////////////////////////////////////////////
#include "wxfbadvprops.h"
#include "wx/log.h"

#include "utils/typeconv.h"

// -----------------------------------------------------------------------
// wxSizeProperty
// -----------------------------------------------------------------------
WX_PG_IMPLEMENT_PROPERTY_CLASS( wxSizeProperty, wxPGProperty, wxSize, const wxSize&, TextCtrl )

wxSizeProperty::wxSizeProperty( const wxString& label,
                                const wxString& name,
                                const wxSize&   value ) : wxPGProperty( label, name )
{
    SetValueI( value );
    AddPrivateChild( new wxIntProperty( wxT("Width"), wxPG_LABEL, value.x ) );
    AddPrivateChild( new wxIntProperty( wxT("Height"), wxPG_LABEL, value.y ) );
}

wxSizeProperty::~wxSizeProperty() {}

void wxSizeProperty::RefreshChildren()
{
    if ( !GetChildCount() ) return;
#if wxVERSION_NUMBER < 2900
    const wxSize& size = wxSizeFromVariant( m_value );
#else
    const wxSize& size = wxSizeRefFromVariant( m_value );
#endif
    Item(0)->SetValue( (long)size.x );
    Item(1)->SetValue( (long)size.y );
}

#if wxVERSION_NUMBER < 2900
    void wxSizeProperty::ChildChanged( wxVariant& thisValue,
#else
    wxVariant wxSizeProperty::ChildChanged( wxVariant& thisValue,
#endif
                                        int childIndex,
                                        wxVariant& childValue ) const
{
#if wxVERSION_NUMBER < 2900
    wxSize& size = wxSizeFromVariant( thisValue );
#else
    wxSize& size = wxSizeRefFromVariant( thisValue );
#endif
    int val = childValue.GetLong();
    switch ( childIndex ) {
    case 0:
        size.x = val;
        break;
    case 1:
        size.y = val;
        break;
    }
#if wxVERSION_NUMBER >= 2900
    wxVariant newVariant;
    newVariant << size;
    return newVariant;
#endif
}

// -----------------------------------------------------------------------
// wxPointProperty
// -----------------------------------------------------------------------

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
#if wxVERSION_NUMBER < 2900
    const wxPoint& point = wxPointFromVariant( m_value );
#else
    const wxPoint& point = wxPointRefFromVariant( m_value );
#endif
    Item(0)->SetValue( (long)point.x );
    Item(1)->SetValue( (long)point.y );
}

#if wxVERSION_NUMBER < 2900
    void wxPointProperty::ChildChanged( wxVariant& thisValue,
#else
    wxVariant wxPointProperty::ChildChanged( wxVariant& thisValue,
#endif
                                        int childIndex,
                                        wxVariant& childValue ) const
{
#if wxVERSION_NUMBER < 2900
    wxPoint& point = wxPointFromVariant( thisValue );
#else
    wxPoint& point = wxPointRefFromVariant( thisValue );
#endif
    int val = childValue.GetLong();
    switch ( childIndex ) {
        case 0:
            point.x = val;
            break;
        case 1:
            point.y = val;
            break;
    }
#if wxVERSION_NUMBER >= 2900
    wxVariant newVariant;
    newVariant << point;
    return newVariant;
#endif
}

// -----------------------------------------------------------------------
// wxBitmapWithResourceProperty TODO
// -----------------------------------------------------------------------

static long g_imageFilterIndex = -1;
static wxString g_imageInitialPath = wxEmptyString;

#if wxVERSION_NUMBER < 2900
    wxPGChoices wxBitmapWithResourceProperty::m_ids;
    wxPGChoices wxBitmapWithResourceProperty::m_clients;
#else
    wxArrayString wxBitmapWithResourceProperty::m_ids;
    wxArrayString wxBitmapWithResourceProperty::m_clients;
#endif

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
wxLogDebug( wxT("===========================================") );
wxLogDebug( wxT("wxBWRP::wxBWRP(): value:%s"), value.c_str() ); 
    // Parse default value, ( sets m_image and m_source based on 'value' )
    DoSetValue( WXVARIANT( value ) );

    // Add the appropriate child
    if ( (m_source == _("Load From File")) || (m_source == _("Load From Embedded File")) )
    {
        wxPGProperty* child = new wxImageFileProperty( wxT("file_path"), wxPG_LABEL, m_image );
        AddPrivateChild( child );
        child->SetHelpString( _("Path to the image file.") );
/*
    wxFileProperty::GetFilterIndex() and wxPG_FILE_FILTER_INDEX are vanished in new propgrid
    so I asked as a Feature Request in propgrid 1.4.15 sf.net project...
        if ( g_imageFilterIndex >= 0 )
        {
            wxVariant filterIndex( g_imageFilterIndex ); 
            child->SetAttribute( wxPG_FILE_FILTER_INDEX, filterIndex );
        }
*/
        if ( !g_imageInitialPath.empty() )
        {
            wxVariant initialPath( g_imageInitialPath );
            child->SetAttribute( wxPG_FILE_INITIAL_PATH, initialPath );
        }
    }
    else if ( m_source == _("Load From Art Provider") )
    {
#if wxVERSION_NUMBER < 2900
        if( m_ids.GetCount() == 0 )
#else
        if( m_ids.IsEmpty() )
#endif
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

        wxPGProperty *child = new wxEnumProperty( wxT("id"), wxPG_LABEL, m_ids, m_ids.Index( m_id ) );
        AddPrivateChild( child );
        child->SetHelpString( _("wxArtID unique identifier of the bitmap. IDs with prefix 'gtk-' are available under wxGTK only.") );
        
#if wxVERSION_NUMBER < 2900
        if( m_ids.GetCount() == 0 )
#else
        if( m_ids.IsEmpty() )
#endif
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
        wxPGProperty *child = new wxStringProperty( wxT("resource_name"), wxPG_LABEL, m_image );
        AddPrivateChild( child );
        child->SetHelpString( _("Windows Only. Name of the resource in the .rc file.") );
    }

    wxPGProperty *child2 = new wxEnumProperty(wxT("source"), wxPG_LABEL, m_strings, m_strings.Index( m_source ) );
    AddPrivateChild( child2 );
    child2->SetHelpString( wxString(_("Load From File:\n") ) +
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
        wxPGProperty *child3 = new wxSizeProperty(wxT("ico_size"), wxPG_LABEL, wxDefaultSize);
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
    wxString oldSource = m_source;
    TypeConv::ParseBitmapWithResource( newValue, &m_image, &m_source, &m_icoSize );
    bool isChanged = ( (m_source != oldSource) && (oldSource != wxT("")) );
//    newValue.Printf( wxT("%s; %s [%i; %i]"), m_image.c_str(), m_source.c_str(), m_icoSize.GetWidth(), m_icoSize.GetHeight() );
wxLogDebug( wxT("wxBWRP::DoSetValue: newValue:%s m_image:%s m_source:%s"), newValue.c_str(), m_image.c_str(), m_source.c_str() );
    if ( wxNOT_FOUND == m_strings.Index( m_source ) )
    {
        m_source = _("Load From File");
    }
    else if( m_source == _("Load From Art Provider") )
    {
        m_id = m_image.BeforeFirst( wxT(':') );
        m_client = m_image.AfterFirst( wxT(':') );
    }

    SetValue( WXVARIANT( newValue ) );

wxLogDebug( wxT("wxBWRP::DoSetValue: m_value:%s"), m_value.GetString().c_str() );

//  RefreshChildren();
}
/*
wxVariant wxBitmapWithResourceProperty::DoGetValue() const
{
    wxString value, image, source;
    wxSize   icoSize = wxSize( m_icoSize.GetWidth(), m_icoSize.GetHeight() );
    value.Printf( wxT("%s"), m_value.GetString().c_str() );
    image.Printf( wxT("%s"), m_image.c_str() );
    source.Printf( wxT("%s"), m_source.c_str() );
    
    TypeConv::ParseBitmapWithResource( value, &image, &source, &icoSize );
wxLogDebug( wxT("wxBWRP::DoGetValue: value:%s|m_image:%s|m_source:%s|m_value:%s|"), value.c_str(), m_image.c_str(), m_source.c_str(), m_value.GetString().c_str() );
    return WXVARIANT( value );
}
*/
void wxBitmapWithResourceProperty::RefreshChildren()
{
wxLogDebug( wxT("wxBWRP::RefreshChildren: m_image:%s m_source:%s m_value:%s"), m_image.c_str(), m_source.c_str(), m_value.GetString().c_str() );
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

        if ( !m_image.empty() )
        {
            wxBitmap bmp = wxBitmap( m_image, wxBITMAP_TYPE_ANY );
            Item( ITEM_FILE_OR_RESOURCE )->SetValue( m_image );
        }
        Item( ITEM_SOURCE )->SetValue( m_strings.Index( m_source ) );
    }
    else if ( 3 == count )
    {
        Item( 0 )->SetValue( m_ids.Index( m_id ) );
        Item( 1 )->SetValue( m_clients.Index( m_client ) );
        Item( 2 )->SetValue( m_strings.Index( m_source ) );
    }
}

#if wxVERSION_NUMBER < 2900
    void wxBitmapWithResourceProperty::ChildChanged( wxVariant& thisValue,
#else
    wxVariant wxBitmapWithResourceProperty::ChildChanged( wxVariant& thisValue,
#endif
                                                           int childIndex,
                                                           wxVariant& childValue ) const
{
    wxString newValue = childValue.GetString();

wxLogDebug( wxT("wxBWRP::ChildChanged: thisValue:%s childIndex:%i childValue:%s"), thisValue.GetString().c_str(), childIndex, childValue.GetString().c_str() );
    if ( ( (m_source == _("Load From File")) || (m_source == _("Load From Embedded File")) ) && (childIndex == 0) )
    {
        wxImageFileProperty* pgProp = wxDynamicCast( Item( 0 ), wxImageFileProperty );
        if ( pgProp )
        {
//          g_imageFilterIndex = pgProp->GetFilterIndex();

            wxFileName imgPath( childValue.GetString() );
            g_imageInitialPath = imgPath.GetPath();

            pgProp->SetValue( childValue );
        }
    }
    else if ( (m_source != _("Load From Art Provider")) && (childIndex = 1) )
    {
        wxBitmapWithResourceProperty* pgBmpProp = wxDynamicCast( Item( 0 )->GetParent(), wxBitmapWithResourceProperty );
        if ( pgBmpProp )
        {
            switch ( childValue.GetInteger() )
            {
            case 0:
                newValue = _("Load From File");
                break;
            case 1:
                newValue = wxT("; ") + wxString(_("Load From Embedded File") );
                break;
            case 2:
                newValue = _("Load From Resource");
                break;
            case 3:
                newValue = _("Load From Icon Resource");
                break;
            case 4:
                pgBmpProp->m_client = pgBmpProp->m_id = wxT("");
                pgBmpProp->m_source = wxString(_("Load From Art Provider") );
                newValue = wxT("; ; ") + pgBmpProp->m_source;
                break;
            }
            pgBmpProp->SetValue( WXVARIANT( newValue ) );
        }
    }
/*  if ( m_source == _("Load From Art Provider") )
    {
        wxBitmapWithResourceProperty* pgBmpProp = wxDynamicCast( Item( 0 )->GetParent(), wxBitmapWithResourceProperty );
        if ( pgBmpProp )
        {
            pgBmpProp->DeleteChildren();

        wxPGProperty *child = new wxEnumProperty( wxT("id"), wxPG_LABEL, m_ids, m_ids.Index( m_id ) );
        pgBmpProp->AddPrivateChild( child );
        child->SetHelpString( _("wxArtID unique identifier of the bitmap. IDs with prefix 'gtk-' are available under wxGTK only.") );

        child = new wxEnumProperty( wxT("client"), wxPG_LABEL, m_clients, m_clients.Index( m_client ) );
        pgBmpProp->AddPrivateChild( child );
        child->SetHelpString( _("wxArtClient identifier of the client (i.e. who is asking for the bitmap).") );

    wxPGProperty *child2 = new wxEnumProperty(wxT("source"), wxPG_LABEL, pgBmpProp->m_strings, pgBmpProp->m_strings.Index( pgBmpProp->m_source ) );
    pgBmpProp->AddPrivateChild( child2 );
    child2->SetHelpString( wxString(_("Load From File:\n") ) +
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
        }

        wxEnumProperty* pgProp = wxDynamicCast( Item( childIndex ), wxEnumProperty );
        if ( pgProp )
        {
            if ( childIndex == 0 ) // art_id
            {
                pgProp->SetValue( m_ids.GetLabel( childValue.GetInteger() ) );
            }
            else // client_id
            {
                pgProp->SetValue( m_clients.GetLabel( childValue.GetInteger() ) );
            }
        }
    }*/
#if wxVERSION_NUMBER >= 2900
    return WXVARIANT( data );
#endif
}

// -----------------------------------------------------------------------
// wxSlider-based property editor
// -----------------------------------------------------------------------
#ifdef wxUSE_SLIDER

// This macro also defines global wxPGEditor_Slider for storing
// the singleton class instance.
WX_PG_IMPLEMENT_EDITOR_CLASS( Slider, wxPGSliderEditor, wxPGEditor )

// Destructor. It is useful to reset the global pointer in it.
wxPGSliderEditor::~wxPGSliderEditor()
{
    wxPG_EDITOR( Slider ) = NULL;
}

// Create controls and initialize event handling.
wxPGWindowList wxPGSliderEditor::CreateControls( wxPropertyGrid* propgrid,
                                                 wxPGProperty* property,
                                                 const wxPoint& pos,
                                                 const wxSize& sz ) const
{
    wxCHECK_MSG( property->IsKindOf( WX_PG_CLASSINFO( wxFloatProperty ) ),
                 NULL,
                 wxT("Slider editor can only be used with wxFloatProperty or derivative.") );

    // Use two stage creation to allow cleaner display on wxMSW
    wxSlider* ctrl = new wxSlider();
#ifdef __WXMSW__
    ctrl->Hide();
#endif
    wxString s = property->GetValueAsString();
    double v_d = 0;
    if ( s.ToDouble( &v_d ) )
    {
        if ( v_d < 0 )
            v_d = 0;
        else if ( v_d > 1 )
            v_d = 1;
    }

    ctrl->Create( propgrid->GetPanel(),
                  wxPG_SUBID1,
                  (int)(v_d * m_max),
                  0,
                  m_max,
                  pos,
                  sz,
                  wxSL_HORIZONTAL);

    // Connect all required events to grid's OnCustomEditorEvent
    // (all relevenat wxTextCtrl, wxComboBox and wxButton events are
    // already connected)
    propgrid->Connect( wxPG_SUBID1, wxEVT_SCROLL_THUMBTRACK,
                       (wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction)
                       &wxPropertyGrid::OnCustomEditorEvent, NULL, propgrid );
#ifdef __WXMSW__
    ctrl->Show();
#endif

    return ctrl;
}

// Copies value from property to control
void wxPGSliderEditor::UpdateControl( wxPGProperty* property, wxWindow* wnd ) const
{
    wxSlider *ctrl = ( wxSlider* ) wnd;
    wxASSERT( ctrl && ctrl->IsKindOf( CLASSINFO(wxSlider) ) );

    double val = property->GetValue().GetDouble();
    if ( val < 0 )
        val = 0;
    else if ( val > 1 )
        val = 1;

    ctrl->SetValue( (int)( val * m_max ) );
}

// Control's events are redirected here
bool wxPGSliderEditor::OnEvent( wxPropertyGrid* WXUNUSED( propgrid ),
                                wxPGProperty* property, wxWindow* wnd, wxEvent& event ) const
{
    if ( event.GetEventType() == wxEVT_SCROLL_THUMBTRACK )
    {
        wxSlider *ctrl = wxDynamicCast( wnd, wxSlider );
        if ( ctrl )
        {
            double val = (double)( ctrl->GetValue() ) / (double)(m_max);
            property->SetValue( WXVARIANT( val ) );
            return true;
        }
    }

    return false;
}

bool wxPGSliderEditor::GetValueFromControl( wxVariant& variant, wxPGProperty* WXUNUSED( property ), wxWindow* wnd ) const
{
    wxSlider* ctrl = ( wxSlider* ) wnd;
    wxASSERT( ctrl && ctrl->IsKindOf( CLASSINFO( wxSlider ) ) );

    variant = WXVARIANT( (double)ctrl->GetValue() / (double)(m_max) );

    return true;
}

void wxPGSliderEditor::SetValueToUnspecified( wxPGProperty* WXUNUSED( property ), wxWindow* WXUNUSED( ctrl ) ) const
{
}

#endif //wxUSE_SLIDER