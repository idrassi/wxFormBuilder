#ifndef __WXFB_PROPGRID_H__
#define __WXFB_PROPGRID_H__

#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/advprops.h>

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

#if wxVERSION_NUMBER < 2900
    virtual void
#else
    virtual wxVariant
#endif
    ChildChanged( wxVariant& thisValue, int childIndex, wxVariant& childValue ) const;

    virtual void RefreshChildren();

protected:
    void DoSetValue( const wxSize& value ) { m_value = WXVARIANT( value ); }
};

// -----------------------------------------------------------------------
// wxPointProperty
// -----------------------------------------------------------------------

class wxPointProperty : public wxPGProperty
{
    WX_PG_DECLARE_PROPERTY_CLASS( wxPointProperty )
public:
    wxPointProperty( const wxString& label = wxPG_LABEL,
                       const wxString& name  = wxPG_LABEL,
                       const wxPoint&  value = wxPoint() );
    virtual ~wxPointProperty();

#if wxVERSION_NUMBER < 2900
    virtual void
#else
    virtual wxVariant
#endif
    ChildChanged( wxVariant& thisValue, int childIndex, wxVariant& childValue ) const;

    virtual void RefreshChildren();

protected:
    void DoSetValue( const wxPoint& value ) { m_value = WXVARIANT( value ); }
};

#endif //__WXFB_PROPGRID_H__
