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

// -----------------------------------------------------------------------
// wxFBSizeProperty
// -----------------------------------------------------------------------
WX_PG_IMPLEMENT_PROPERTY_CLASS( wxFBSizeProperty, wxPGProperty, wxSize, const wxSize&, TextCtrl )

wxFBSizeProperty::wxFBSizeProperty( const wxString& label,
                                const wxString& name,
                                const wxSize&   value ) : wxPGProperty( label, name )
{
    SetValueI( value );
    AddPrivateChild( new wxIntProperty( wxT("Width"), wxPG_LABEL, value.x ) );
    AddPrivateChild( new wxIntProperty( wxT("Height"), wxPG_LABEL, value.y ) );
}

wxFBSizeProperty::~wxFBSizeProperty() {}

void wxFBSizeProperty::RefreshChildren()
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
    void wxFBSizeProperty::ChildChanged( wxVariant& thisValue,
#else
    wxVariant wxFBSizeProperty::ChildChanged( wxVariant& thisValue,
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
// wxFBPointProperty
// -----------------------------------------------------------------------

WX_PG_IMPLEMENT_PROPERTY_CLASS( wxFBPointProperty, wxPGProperty,
                                wxPoint, const wxPoint&, TextCtrl )

wxFBPointProperty::wxFBPointProperty( const wxString& label,
                                  const wxString& name,
                                  const wxPoint&  value ) : wxPGProperty( label, name )
{
    SetValueI( value );
    AddPrivateChild( new wxIntProperty( wxT("X"), wxPG_LABEL, value.x ) );
    AddPrivateChild( new wxIntProperty( wxT("Y"), wxPG_LABEL, value.y ) );
}

wxFBPointProperty::~wxFBPointProperty() { }

void wxFBPointProperty::RefreshChildren()
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
    void wxFBPointProperty::ChildChanged( wxVariant& thisValue,
#else
    wxVariant wxFBPointProperty::ChildChanged( wxVariant& thisValue,
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
// wxFBBitmapProperty
// -----------------------------------------------------------------------

static long gs_imageFilterIndex = -1;
static wxString gs_imageInitialPath = wxEmptyString;

WX_PG_IMPLEMENT_PROPERTY_CLASS( wxFBBitmapProperty, wxPGProperty,
                                wxString, const wxString&, TextCtrl )

wxFBBitmapProperty::wxFBBitmapProperty( const wxString& label,
                                        const wxString& name,
                                        const wxString& value )
: wxPGProperty( label, name )
{
    m_value = WXVARIANT( value );
}

wxPGProperty *wxFBBitmapProperty::CreatePropertySource()
{
#if wxVERSION_NUMBER < 2900
    wxPGChoices sourceChoices;
#else
    wxArrayString sourceChoices;
#endif

    // Add 'source' property (common for all other children)
    sourceChoices.Add(_("Load From File") );
    sourceChoices.Add(_("Load From Embedded File") );
    sourceChoices.Add(_("Load From Resource") );
    sourceChoices.Add(_("Load From Icon Resource") );
    sourceChoices.Add(_("Load From Art Provider") );

    wxPGProperty *srcProp = new wxEnumProperty( wxT("source"), wxPG_LABEL, sourceChoices, 0 );
    srcProp->SetHelpString( wxString(_("Load From File:\n") ) +
                            wxString(_("Load the image from a file on disk.\n\n") ) +
                            wxString(_("Load From Embedded File:\n") ) +
                            wxString(_("C++ Only. Embed the image file in the exe and load it.\nFor other languages, behaves like \"Load From File\".\n\n") ) +
                            wxString(_("Load From Resource:\n") ) +
                            wxString(_("Windows Only. Load the image from a BITMAP resource in a .rc file\n\n") ) +
                            wxString(_("Load From Icon Resource:\n") ) +
                            wxString(_("Windows Only. Load the image from a ICON resource in a .rc file\n\n") ) +
                            wxString(_("Load From Art Provider:\n") ) +
                            wxString(_("Query registered providers for bitmap with given ID.\n\n") ) );
    AppendChild( srcProp );

    wxPGProperty *propFilePath = CreatePropertyFilePath();
    AppendChild( propFilePath );

    return srcProp;
}

wxPGProperty *wxFBBitmapProperty::CreatePropertyFilePath()
{
    // Add 'file_path' property (common for 'Load From File' and 'Load From Embedded File' choices)
    wxPGProperty *propFilePath = new wxImageFileProperty( wxT("file_path"), wxPG_LABEL );
    propFilePath->SetHelpString(_("Path to the image file.") );

    if ( !gs_imageInitialPath.empty() )
    {
        wxVariant initialPath( gs_imageInitialPath );
        propFilePath->SetAttribute( wxPG_FILE_INITIAL_PATH, initialPath );
    }

    return propFilePath;
}

wxPGProperty *wxFBBitmapProperty::CreatePropertyResourceName()
{
    // Create 'resource_name' property (common for 'Load From Resource' and 'Load From Icon Resource' choices)
    wxPGProperty *propResName = new wxStringProperty( wxT("resource_name"), wxPG_LABEL );
    propResName->SetHelpString(_("Windows Only. Name of the resource in the .rc file.") );

    return propResName;
}

wxPGProperty *wxFBBitmapProperty::CreatePropertyIconSize()
{
    // Create 'ico_size' property ('Load From Icon Resource' only)
    wxPGProperty *propIcoSize = new wxFBSizeProperty(wxT("ico_size"), wxPG_LABEL, wxDefaultSize);
    propIcoSize->SetHelpString(_("The size of the icon to use from a ICON resource with multiple icons in it.") );

    return propIcoSize;
}

wxPGProperty *wxFBBitmapProperty::CreatePropertyArtId()
{
#if wxVERSION_NUMBER < 2900
    wxPGChoices artIdChoices;
#else
    wxArrayString artIdChoices;
#endif
    // Create 'id' property ('Load From Art Provider' only)
    artIdChoices.Add(wxT("wxART_ADD_BOOKMARK"));
    artIdChoices.Add(wxT("wxART_DEL_BOOKMARK "));
    artIdChoices.Add(wxT("wxART_HELP_SIDE_PANEL"));
    artIdChoices.Add(wxT("wxART_HELP_SETTINGS"));
    artIdChoices.Add(wxT("wxART_HELP_BOOK"));
    artIdChoices.Add(wxT("wxART_HELP_FOLDER"));
    artIdChoices.Add(wxT("wxART_HELP_PAGE"));
    artIdChoices.Add(wxT("wxART_GO_BACK"));
    artIdChoices.Add(wxT("wxART_GO_FORWARD"));
    artIdChoices.Add(wxT("wxART_GO_UP"));
    artIdChoices.Add(wxT("wxART_GO_DOWN"));
    artIdChoices.Add(wxT("wxART_GO_TO_PARENT"));
    artIdChoices.Add(wxT("wxART_GO_HOME"));
    artIdChoices.Add(wxT("wxART_FILE_OPEN"));
    artIdChoices.Add(wxT("wxART_PRINT"));
    artIdChoices.Add(wxT("wxART_HELP"));
    artIdChoices.Add(wxT("wxART_TIP"));
    artIdChoices.Add(wxT("wxART_REPORT_VIEW"));
    artIdChoices.Add(wxT("wxART_LIST_VIEW"));
    artIdChoices.Add(wxT("wxART_NEW_DIR"));
    artIdChoices.Add(wxT("wxART_FOLDER"));
    artIdChoices.Add(wxT("wxART_GO_DIR_UP"));
    artIdChoices.Add(wxT("wxART_EXECUTABLE_FILE"));
    artIdChoices.Add(wxT("wxART_NORMAL_FILE"));
    artIdChoices.Add(wxT("wxART_TICK_MARK"));
    artIdChoices.Add(wxT("wxART_CROSS_MARK"));
    artIdChoices.Add(wxT("wxART_ERROR"));
    artIdChoices.Add(wxT("wxART_QUESTION"));
    artIdChoices.Add(wxT("wxART_WARNING"));
    artIdChoices.Add(wxT("wxART_INFORMATION"));
    artIdChoices.Add(wxT("wxART_MISSING_IMAGE"));

    artIdChoices.Add(wxT("gtk-about"));
    artIdChoices.Add(wxT("gtk-add"));
    artIdChoices.Add(wxT("gtk-apply"));
    artIdChoices.Add(wxT("gtk-bold"));
    artIdChoices.Add(wxT("gtk-cancel"));
    artIdChoices.Add(wxT("gtk-caps-lock-warning"));
    artIdChoices.Add(wxT("gtk-cdrom"));
    artIdChoices.Add(wxT("gtk-clear"));
    artIdChoices.Add(wxT("gtk-close"));
    artIdChoices.Add(wxT("gtk-color-picker"));
    artIdChoices.Add(wxT("gtk-convert"));
    artIdChoices.Add(wxT("gtk-copy"));
    artIdChoices.Add(wxT("gtk-cut"));
    artIdChoices.Add(wxT("gtk-delete"));
    artIdChoices.Add(wxT("gtk-dialog-authentication"));
    artIdChoices.Add(wxT("gtk-dialog-error"));
    artIdChoices.Add(wxT("gtk-dialog-info"));
    artIdChoices.Add(wxT("gtk-dialog-question"));
    artIdChoices.Add(wxT("gtk-dialog-warning"));
    artIdChoices.Add(wxT("gtk-warning"));
    artIdChoices.Add(wxT("gtk-discard"));
    artIdChoices.Add(wxT("gtk-disconnect"));
    artIdChoices.Add(wxT("gtk-dnd"));
    artIdChoices.Add(wxT("gtk-dnd-multiple"));
    artIdChoices.Add(wxT("gtk-edit"));
    artIdChoices.Add(wxT("gtk-execute"));
    artIdChoices.Add(wxT("gtk-file"));
    artIdChoices.Add(wxT("gtk-find"));
    artIdChoices.Add(wxT("gtk-find-and-replace"));
    artIdChoices.Add(wxT("gtk-fullscreen"));
    artIdChoices.Add(wxT("gtk-goto-bottom"));
    artIdChoices.Add(wxT("gtk-goto-first"));
    artIdChoices.Add(wxT("gtk-goto-last"));
    artIdChoices.Add(wxT("gtk-goto-top"));
    artIdChoices.Add(wxT("gtk-go-back"));
    artIdChoices.Add(wxT("gtk-go-down"));
    artIdChoices.Add(wxT("gtk-go-forward"));
    artIdChoices.Add(wxT("gtk-go-up"));
    artIdChoices.Add(wxT("gtk-harddisk"));
    artIdChoices.Add(wxT("gtk-indent"));
    artIdChoices.Add(wxT("gtk-index"));
    artIdChoices.Add(wxT("gtk-info"));
    artIdChoices.Add(wxT("gtk-italic"));
    artIdChoices.Add(wxT("gtk-jump-to"));
    artIdChoices.Add(wxT("gtk-justify-center"));
    artIdChoices.Add(wxT("gtk-justify-fill"));
    artIdChoices.Add(wxT("gtk-justify-left"));
    artIdChoices.Add(wxT("gtk-justify-right"));
    artIdChoices.Add(wxT("gtk-leave-fullscreen"));
    artIdChoices.Add(wxT("gtk-media-forward"));
    artIdChoices.Add(wxT("gtk-media-next"));
    artIdChoices.Add(wxT("gtk-media-forward"));
    artIdChoices.Add(wxT("gtk-media-pause"));
    artIdChoices.Add(wxT("gtk-media-play"));
    artIdChoices.Add(wxT("gtk-media-previous"));
    artIdChoices.Add(wxT("gtk-media-record"));
    artIdChoices.Add(wxT("gtk-media-rewind"));
    artIdChoices.Add(wxT("gtk-media-stop"));
    artIdChoices.Add(wxT("gtk-missing-image"));
    artIdChoices.Add(wxT("gtk-network"));
    artIdChoices.Add(wxT("gtk-new"));
    artIdChoices.Add(wxT("gtk-no"));
    artIdChoices.Add(wxT("gtk-ok"));
    artIdChoices.Add(wxT("gtk-open"));
    artIdChoices.Add(wxT("gtk-orientation-landscape"));
    artIdChoices.Add(wxT("gtk-orientation-portrait"));
    artIdChoices.Add(wxT("gtk-orientation-reverse-landscape"));
    artIdChoices.Add(wxT("gtk-orientation-reverse-portrait"));
    artIdChoices.Add(wxT("gtk-page-setup"));
    artIdChoices.Add(wxT("gtk-paste"));
    artIdChoices.Add(wxT("gtk-preferences"));
    artIdChoices.Add(wxT("gtk-print"));
    artIdChoices.Add(wxT("gtk-print-paused"));
    artIdChoices.Add(wxT("gtk-print-report"));
    artIdChoices.Add(wxT("gtk-print-warning"));
    artIdChoices.Add(wxT("gtk-properties"));
    artIdChoices.Add(wxT("gtk-quit"));
    artIdChoices.Add(wxT("gtk-redo"));
    artIdChoices.Add(wxT("gtk-refresh"));
    artIdChoices.Add(wxT("gtk-remove"));
    artIdChoices.Add(wxT("gtk-save"));
    artIdChoices.Add(wxT("gtk-save-as"));
    artIdChoices.Add(wxT("gtk-select-all"));
    artIdChoices.Add(wxT("gtk-select-color"));
    artIdChoices.Add(wxT("gtk-select-font"));
    artIdChoices.Add(wxT("gtk-sort-ascending"));
    artIdChoices.Add(wxT("gtk-sort-descending"));
    artIdChoices.Add(wxT("gtk-spell-check"));
    artIdChoices.Add(wxT("gtk-stop"));
    artIdChoices.Add(wxT("gtk-strikethrough"));
    artIdChoices.Add(wxT("gtk-undelete"));
    artIdChoices.Add(wxT("gtk-underline"));
    artIdChoices.Add(wxT("gtk-undo"));
    artIdChoices.Add(wxT("gtk-unindent"));
    artIdChoices.Add(wxT("gtk-yes"));
    artIdChoices.Add(wxT("gtk-zoom-100"));
    artIdChoices.Add(wxT("gtk-zoom-fit"));
    artIdChoices.Add(wxT("gtk-zoom-in"));
    artIdChoices.Add(wxT("gtk-zoom-out"));

    wxPGProperty *propArtId = new wxEnumProperty( wxT("id"), wxPG_LABEL, artIdChoices );
    propArtId->SetHelpString( _("wxArtID unique identifier of the bitmap. IDs with prefix 'gtk-' are available under wxGTK only.") );

    return propArtId;
}

wxPGProperty *wxFBBitmapProperty::CreatePropertyArtClient()
{
#if wxVERSION_NUMBER < 2900
    wxPGChoices artClientChoices;
#else
    wxArrayString artClientChoices;
#endif
    // Create 'client' property ('Load From Art Provider' only)
    artClientChoices.Add(wxT("wxART_TOOLBAR"));
    artClientChoices.Add(wxT("wxART_MENU"));
    artClientChoices.Add(wxT("wxART_BUTTON"));
    artClientChoices.Add(wxT("wxART_FRAME_ICON"));
    artClientChoices.Add(wxT("wxART_CMN_DIALOG"));
    artClientChoices.Add(wxT("wxART_HELP_BROWSER"));
    artClientChoices.Add(wxT("wxART_MESSAGE_BOX"));
    artClientChoices.Add(wxT("wxART_OTHER"));

    wxPGProperty *propArtClient = new wxEnumProperty( wxT("client"), wxPG_LABEL, artClientChoices );
    propArtClient->SetHelpString( _("wxArtClient identifier of the client (i.e. who is asking for the bitmap).") );

    return propArtClient;
}

wxFBBitmapProperty::~wxFBBitmapProperty()
{
}

#if wxVERSION_NUMBER < 2900
    void wxFBBitmapProperty::ChildChanged( wxVariant& thisValue,
#else
    wxVariant wxFBBitmapProperty::ChildChanged( wxVariant& thisValue,
#endif
                                                           int childIndex,
                                                           wxVariant& childValue ) const
{
wxLogDebug( wxT("ChildChanged: thisValue:%s childIndex:%i childValue:%s"), thisValue.GetString().c_str(), childIndex, childValue.GetString().c_str() );

    // Get our property instance
    wxFBBitmapProperty *bp = ( wxFBBitmapProperty * )Item( 0 )->GetParent();

    // Error check
    if ( !bp )
    {
        wxLogDebug( wxT("wxFBBitmapProperty creation failed.") );

#if wxVERSION_NUMBER >= 2900
        return thisValue;
#endif
    }

    wxString newValue, newImage, newResName, newIcoSize, newArtId, newArtClient;

    // Get the new source
    wxString newSource = wxGetTranslation( thisValue.GetString().BeforeFirst(';') );

    // Find the appropriate new state
    switch ( childIndex )
    {
        // source
        case 0:
        {
            unsigned int count = GetChildCount();

            // Delete all children but 'source' one
            for ( unsigned int i = 1; i < count; i++ )
            {
                wxPGProperty *p = Item( i );
                if ( p )
                {
                    wxLogDebug( wxT("ChildChanged: Removing:%s"), p->GetLabel().c_str() );
                    GetGrid()->RemoveProperty( p );
                }
            }       

            switch ( childValue.GetInteger() )
            {
                // 'Load From File' and 'Load From Embedded File'
                case 0:
                case 1:
                {
                    wxPGProperty *propFilePath = bp->CreatePropertyFilePath();

                    bp->AppendChild( propFilePath );
                    newValue  = newSource + wxT("; ");
                    break;
                }
                case 2:
                {
                    wxPGProperty *propResName = bp->CreatePropertyResourceName();

                    bp->AppendChild( propResName );
                    newValue = newSource + wxT("; ");
                    break;
                }
                case 3:
                {
                    wxPGProperty *propResName = bp->CreatePropertyResourceName();
                    wxPGProperty *propIcoSize = bp->CreatePropertyIconSize();

                    bp->AppendChild( propResName );
                    bp->AppendChild( propIcoSize );

                    newValue   = newSource + wxT("; ; ") + propIcoSize->GetValueAsString();
                    break;
                }
                case 4:
                {
                    wxPGProperty *propArtId = bp->CreatePropertyArtId();
                    wxPGProperty *propArtClient = bp->CreatePropertyArtClient();

                    bp->AppendChild( propArtId );
                    bp->AppendChild( propArtClient );

                    newValue = newSource + wxT("; ; ");
                    break;
                }
            }
            break;
        }

        // file_path || id || resource_name
        case 1:
        {
            if ( (newSource == _("Load From File")) || (newSource == _("Load From Embedded File")) )
            {
                wxImageFileProperty* pgProp = wxDynamicCast( Item( 1 ), wxImageFileProperty );
                if ( pgProp )
                {
        //          g_imageFilterIndex = pgProp->GetFilterIndex();

                    wxFileName imgPath( childValue.GetString() );
                    gs_imageInitialPath = imgPath.GetPath();

                    pgProp->SetValue( childValue );

                    newValue = thisValue.GetString();
                }
            }
            break;
        }

        // resource_name
        case 2:
        {
            newValue = thisValue.GetString() + childValue.GetString();
            break;
        }
    }

    bp->SetValue( WXVARIANT( newValue ) );

    wxLogDebug( wxT("ChildChanged: New Value:%s"), newValue.c_str() );

#if wxVERSION_NUMBER >= 2900
    return WXVARIANT( newValue );
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