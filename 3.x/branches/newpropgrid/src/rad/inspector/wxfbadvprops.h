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
#ifndef __WXFBADVPROPS_H__
#define __WXFBADVPROPS_H__

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
    virtual void ChildChanged( wxVariant& thisValue,
#else
    virtual wxVariant ChildChanged( wxVariant& thisValue,
#endif
                                    int childIndex,
                                    wxVariant& childValue ) const;
    virtual void RefreshChildren();

protected:
    // I stands for internal
    void SetValueI( const wxSize& value ) {
        m_value = WXVARIANT( value );
    }
};

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

#if wxVERSION_NUMBER < 2900
    virtual void ChildChanged( wxVariant& thisValue,
#else
    virtual wxVariant ChildChanged( wxVariant& thisValue,
#endif
                                    int childIndex,
                                    wxVariant& childValue ) const;
    virtual void RefreshChildren();

protected:
    void SetValueI( const wxPoint& value ) {
        m_value = WXVARIANT( value );
    }
};

// -----------------------------------------------------------------------
// wxBitmapWithResourceProperty TODO
// -----------------------------------------------------------------------
DECLARE_EVENT_TYPE( RECREATE_GRID_EVENT, wxID_ANY )
DECLARE_EVENT_TYPE( REPLACE_PROPERTY_EVENT, wxID_ANY )

class wxBitmapWithResourceProperty : public wxPGProperty
{
    WX_PG_DECLARE_PROPERTY_CLASS( wxBitmapWithResourceProperty )

public:
    wxBitmapWithResourceProperty( const wxString& label = wxPG_LABEL,
                                       const wxString& name  = wxPG_LABEL,
                                       const wxString& value = wxString() );

    virtual ~wxBitmapWithResourceProperty();

//  virtual wxVariant DoGetValue() const;

    void DoSetValue( wxVariant value );

#if wxVERSION_NUMBER < 2900
    virtual void ChildChanged( wxVariant& thisValue,
#else
    virtual wxVariant ChildChanged( wxVariant& thisValue,
#endif
                                    int childIndex,
                                    wxVariant& childValue ) const;
    virtual void RefreshChildren();

protected:
    wxString m_image;;
    wxString m_id;
    wxString m_client;
    wxString m_source;
    wxSize m_icoSize;

#if wxVERSION_NUMBER < 2900
    static wxPGChoices m_ids;
    static wxPGChoices m_clients;
    wxPGChoices m_strings;
#else
    static wxArrayString m_ids;
    static wxArrayString m_clients;
    wxArrayString m_strings;
#endif

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

// -----------------------------------------------------------------------
// wxSlider-based property editor
// -----------------------------------------------------------------------

#if wxUSE_SLIDER
//
// Implement an editor control that allows using wxSlider to edit value of
// wxFloatProperty (and similar).
//
// Note that new editor classes needs to be registered before use.
// This can be accomplished using wxPGRegisterEditorClass macro.
// Registeration can also be performed in a constructor of a
// property that is likely to require the editor in question.
//
#include <wx/slider.h>

class wxPGSliderEditor : public wxPGEditor
{
    WX_PG_DECLARE_EDITOR_CLASS( wxPGSliderEditor )
public:
    wxPGSliderEditor()
    :
    m_max( 10000 )
    {
    }

    virtual ~wxPGSliderEditor();

    // See below for short explanations of what these are supposed to do.
    wxPG_DECLARE_CREATECONTROLS

    virtual void UpdateControl( wxPGProperty* property, wxWindow* wnd ) const;
    virtual bool OnEvent( wxPropertyGrid* propgrid, wxPGProperty* property,
                          wxWindow* wnd, wxEvent& event ) const;
    virtual bool GetValueFromControl( wxVariant& variant, wxPGProperty* property, wxWindow* ctrl ) const;
    virtual void SetValueToUnspecified( wxPGProperty* property, wxWindow* ctrl ) const;

private:
    int m_max;
};
#endif // wxUSE_SLIDER

#endif //__WXFBADVPROPS_H__
