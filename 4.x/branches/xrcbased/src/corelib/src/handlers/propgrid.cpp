#include "handlers/propgrid.h"

// -----------------------------------------------------------------------
// wxSizeProperty
// -----------------------------------------------------------------------
WX_PG_IMPLEMENT_PROPERTY_CLASS( wxSizeProperty, wxPGProperty, wxSize, const wxSize&, TextCtrl )

wxSizeProperty::wxSizeProperty( const wxString& label,
                                    const wxString& name,
                                    const wxSize&   value ) : wxPGProperty( label, name )
{
    DoSetValue( value );
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
    void
#else
    wxVariant
#endif

wxSizeProperty::ChildChanged( wxVariant& thisValue, int childIndex, wxVariant& childValue ) const
{
#if wxVERSION_NUMBER < 2900
    wxSize& size = wxSizeFromVariant( thisValue );
#else
    wxSize& size = wxSizeRefFromVariant( thisValue );
#endif

    int val = childValue.GetLong();
    switch ( childIndex )
    {
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

WX_PG_IMPLEMENT_PROPERTY_CLASS( wxPointProperty, wxPGProperty, wxPoint, const wxPoint&, TextCtrl )

wxPointProperty::wxPointProperty( const wxString& label,
                                      const wxString& name,
                                      const wxPoint&  value ) : wxPGProperty( label, name )
{
    DoSetValue( value );
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
    void
#else
    wxVariant
#endif

wxPointProperty::ChildChanged( wxVariant& thisValue, int childIndex, wxVariant& childValue ) const
{
#if wxVERSION_NUMBER < 2900
    wxPoint& point = wxPointFromVariant( thisValue );
#else
    wxPoint& point = wxPointRefFromVariant( thisValue );
#endif

    int val = childValue.GetLong();
    switch ( childIndex )
    {
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
