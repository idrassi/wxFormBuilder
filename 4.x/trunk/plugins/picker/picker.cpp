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

#include <component.h>
#include <plugin.h>
#include <xrcconv.h>
#include <ticpp.h>

#include <wx/clrpicker.h>
#include <wx/datectrl.h>
#include <wx/filepicker.h>
#include <wx/fontpicker.h>

/**
Event handler for events generated by controls in this plugin
*/
class ComponentEvtHandler : public wxEvtHandler
{
private:
	wxWindow* m_window;
	IManager* m_manager;

public:
	ComponentEvtHandler( wxWindow* win, IManager* manager )
	:
	m_window( win ),
	m_manager( manager )
	{
	}

protected:
	void OnColourPickerColourChanged( wxColourPickerEvent& event );
	void OnDirPickerDirChanged( wxFileDirPickerEvent& event );
	void OnFilePickerFileChanged( wxFileDirPickerEvent& event );
	void OnFontPickerFontChanged( wxFontPickerEvent& event );
};

class PickerComponentBase : public ComponentBase, public wxEvtHandler
{
public:
	void OnLeftClick( wxMouseEvent& event )
	{
		wxWindow* window = dynamic_cast< wxWindow* >( event.GetEventObject() );
		wxPickerBase* picker = dynamic_cast< wxPickerBase* >( window->GetParent() );
		if ( 0 != picker )
		{
			if ( !GetManager()->SelectObject( picker ) )
			{
				event.Skip();
			}
		}
	}

	void OnCreated( wxObject* wxobject, wxWindow* /*wxparent*/ )
	{
		wxPickerBase* picker = dynamic_cast< wxPickerBase* >( wxobject );
		if ( picker != 0 )
		{
			picker->GetPickerCtrl()->Connect( 	wxEVT_LEFT_DOWN,
												wxMouseEventHandler( PickerComponentBase::OnLeftClick ), NULL, this );

			wxTextCtrl* text = picker->GetTextCtrl();
			if ( 0 != text )
			{
				text->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( PickerComponentBase::OnLeftClick ), NULL, this );
			}
		}
	}

	void Cleanup( wxObject* obj )
	{
		wxPickerBase* picker = dynamic_cast< wxPickerBase* >( obj );
		if ( picker != 0 )
		{
			picker->GetPickerCtrl()->Disconnect(wxEVT_LEFT_DOWN,
												wxMouseEventHandler( PickerComponentBase::OnLeftClick ), NULL, this );

			wxTextCtrl* text = picker->GetTextCtrl();
			if ( 0 != text )
			{
				text->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( PickerComponentBase::OnLeftClick ), NULL, this );
			}
		}
		ComponentBase::Cleanup( obj );
	}
};

class ColourPickerComponent : public PickerComponentBase
{
private:

public:
	wxObject* Create( IObject *obj, wxObject *parent )
	{
		wxColourPickerCtrl* colourpicker = new wxColourPickerCtrl( (wxWindow*)parent,
																	obj->GetPropertyAsInteger("id"),
																	obj->GetPropertyAsColour("colour"),
																	obj->GetPropertyAsPoint("pos"),
																	obj->GetPropertyAsSize("size"),
																	obj->GetPropertyAsInteger("style") |
																	obj->GetPropertyAsInteger("window_style") );

		colourpicker->PushEventHandler( new ComponentEvtHandler( colourpicker, GetManager() ) );
		return colourpicker;
	}

	ticpp::Element* ExportToXrc(IObject *obj)
	{
		ObjectToXrcFilter xrc( obj, "wxColourPickerCtrl", obj->GetPropertyAsString("name") );
		xrc.AddProperty( "colour", "value", XRC_TYPE_COLOUR );
		xrc.AddWindowProperties();
		return xrc.GetXrcObject();
	}

	ticpp::Element* ImportFromXrc( ticpp::Element* xrcObj )
	{
		XrcToXfbFilter filter( xrcObj, "wxColourPickerCtrl" );
		filter.AddProperty( "value", "colour", XRC_TYPE_COLOUR );
		filter.AddWindowProperties();
		return filter.GetXfbObject();
	}
};

void ComponentEvtHandler::OnColourPickerColourChanged( wxColourPickerEvent& )
{
	wxColourPickerCtrl* window = wxDynamicCast( m_window, wxColourPickerCtrl );
	if ( window != NULL )
	{
		wxColour colour = window->GetColour();
		m_manager->ModifyProperty( window, "colour",
								wxString::Format( "%d,%d,%d", colour.Red(), colour.Green(), colour.Blue() ) );
	}
}

class DatePickerCtrlComponent : public ComponentBase
{
public:
	wxObject* Create(IObject *obj, wxObject *parent)
	{
		return new wxDatePickerCtrl((wxWindow *)parent,-1,
									wxDefaultDateTime,
									obj->GetPropertyAsPoint("pos"),
									obj->GetPropertyAsSize("size"),
									obj->GetPropertyAsInteger("style") |
									obj->GetPropertyAsInteger("window_style") );
	}

	ticpp::Element* ExportToXrc(IObject *obj)
	{
		ObjectToXrcFilter xrc( obj, "wxDatePickerCtrl", obj->GetPropertyAsString("name") );
		xrc.AddWindowProperties();
		return xrc.GetXrcObject();
	}

	ticpp::Element* ImportFromXrc( ticpp::Element* xrcObj )
	{
		XrcToXfbFilter filter( xrcObj, "wxDatePickerCtrl" );
		filter.AddWindowProperties();
		return filter.GetXfbObject();
	}
};

class DirPickerComponent : public PickerComponentBase
{
public:
	wxObject* Create( IObject *obj, wxObject *parent )
	{
		wxDirPickerCtrl* picker = new wxDirPickerCtrl( (wxWindow*)parent,
														obj->GetPropertyAsInteger("id"),
														obj->GetPropertyAsString("value"),
														obj->GetPropertyAsString("message"),
														obj->GetPropertyAsPoint("pos"),
														obj->GetPropertyAsSize("size"),
														obj->GetPropertyAsInteger("style") |
														obj->GetPropertyAsInteger("window_style") );

		picker->PushEventHandler( new ComponentEvtHandler( picker, GetManager() ) );
		return picker;
	}

	ticpp::Element* ExportToXrc( IObject *obj )
	{
		ObjectToXrcFilter xrc( obj, "wxDirPickerCtrl", obj->GetPropertyAsString("name") );
		xrc.AddProperty( "value", "value", XRC_TYPE_TEXT );
		xrc.AddProperty( "message", "message", XRC_TYPE_TEXT );
		xrc.AddWindowProperties();
		return xrc.GetXrcObject();
	}

	ticpp::Element* ImportFromXrc( ticpp::Element* xrcObj )
	{
		XrcToXfbFilter filter( xrcObj, "wxDirPickerCtrl" );
		filter.AddProperty( "value", "value", XRC_TYPE_FONT);
		filter.AddProperty( "message", "message", XRC_TYPE_TEXT );
		filter.AddWindowProperties();
		return filter.GetXfbObject();
	}
};

void ComponentEvtHandler::OnDirPickerDirChanged( wxFileDirPickerEvent& )
{
	wxDirPickerCtrl* window = wxDynamicCast( m_window, wxDirPickerCtrl );
	if ( window != NULL )
	{
		m_manager->ModifyProperty( window, "value", window->GetPath() );
	}
}

class FilePickerComponent : public PickerComponentBase
{
public:
	wxObject* Create( IObject *obj, wxObject *parent )
	{
		wxFilePickerCtrl* picker = new wxFilePickerCtrl((wxWindow*)parent,
														obj->GetPropertyAsInteger("id"),
														obj->GetPropertyAsString("value"),
														obj->GetPropertyAsString("message"),
														obj->GetPropertyAsString("wildcard"),
														obj->GetPropertyAsPoint("pos"),
														obj->GetPropertyAsSize("size"),
														obj->GetPropertyAsInteger("style") |
														obj->GetPropertyAsInteger("window_style") );

		picker->PushEventHandler( new ComponentEvtHandler( picker, GetManager() ) );
		return picker;
	}

	ticpp::Element* ExportToXrc( IObject *obj )
	{
		ObjectToXrcFilter xrc( obj, "wxFilePickerCtrl", obj->GetPropertyAsString("name") );
		xrc.AddProperty( "value", "value", XRC_TYPE_TEXT );
		xrc.AddProperty( "message", "message", XRC_TYPE_TEXT );
		xrc.AddProperty( "wildcard", "wildcard", XRC_TYPE_TEXT );
		xrc.AddWindowProperties();
		return xrc.GetXrcObject();
	}

	ticpp::Element* ImportFromXrc( ticpp::Element* xrcObj )
	{
		XrcToXfbFilter filter( xrcObj, "wxFilePickerCtrl" );
		filter.AddProperty( "value", "value", XRC_TYPE_FONT);
		filter.AddProperty( "message", "message", XRC_TYPE_TEXT );
		filter.AddProperty( "wildcard", "wildcard", XRC_TYPE_TEXT );
		filter.AddWindowProperties();
		return filter.GetXfbObject();
	}
};

void ComponentEvtHandler::OnFilePickerFileChanged( wxFileDirPickerEvent& )
{
	wxFilePickerCtrl* window = wxDynamicCast( m_window, wxFilePickerCtrl );
	if ( window != NULL )
	{
		m_manager->ModifyProperty( window, "value", window->GetPath() );
	}
}

class FontPickerComponent : public PickerComponentBase
{
public:
	wxObject* Create( IObject *obj, wxObject *parent )
	{
		wxFontPickerCtrl* picker = new wxFontPickerCtrl((wxWindow*)parent,
														obj->GetPropertyAsInteger("id"),
														obj->GetPropertyAsFont("value"),
														obj->GetPropertyAsPoint("pos"),
														obj->GetPropertyAsSize("size"),
														obj->GetPropertyAsInteger("style") |
														obj->GetPropertyAsInteger("window_style") );
		if ( !obj->IsNull("max_point_size") )
		{
			picker->SetMaxPointSize( obj->GetPropertyAsInteger("max_point_size") );
		}
		picker->PushEventHandler( new ComponentEvtHandler( picker, GetManager() ) );
		return picker;
	}

	ticpp::Element* ExportToXrc( IObject *obj )
	{
		ObjectToXrcFilter xrc( obj, "wxFontPickerCtrl", obj->GetPropertyAsString("name") );
		if ( !obj->IsNull("value") )
		{
			xrc.AddProperty( "value", "value", XRC_TYPE_FONT );
		}
		xrc.AddWindowProperties();
		return xrc.GetXrcObject();
	}

	ticpp::Element* ImportFromXrc( ticpp::Element* xrcObj )
	{
		XrcToXfbFilter filter( xrcObj, "wxFontPickerCtrl" );
		filter.AddProperty( "value", "value", XRC_TYPE_FONT );
		filter.AddWindowProperties();
		return filter.GetXfbObject();
	}
};

void ComponentEvtHandler::OnFontPickerFontChanged( wxFontPickerEvent& )
{
	wxFontPickerCtrl* window = wxDynamicCast( m_window, wxFontPickerCtrl );
	if ( window != NULL )
	{
		wxFont font = window->GetSelectedFont();
		m_manager->ModifyProperty( window, "value", wxString::Format("%s,%d,%d,%d",
																	font.GetFaceName().c_str(), font.GetStyle(),
																	font.GetWeight(), font.GetPointSize() ) );
	}
}

BEGIN_LIBRARY()

WINDOW_COMPONENT( "wxColourPickerCtrl", ColourPickerComponent )
WINDOW_COMPONENT( "wxDatePickerCtrl", 	DatePickerCtrlComponent )
WINDOW_COMPONENT( "wxDirPickerCtrl", 	DirPickerComponent )
WINDOW_COMPONENT( "wxFilePickerCtrl", 	FilePickerComponent )
WINDOW_COMPONENT( "wxFontPickerCtrl", 	FontPickerComponent )

// wxColourPickerCtrl
MACRO(wxCLRP_DEFAULT_STYLE)
MACRO(wxCLRP_USE_TEXTCTRL)
MACRO(wxCLRP_SHOW_LABEL)

// wxDatePickerCtrl
MACRO(wxDP_SPIN)
MACRO(wxDP_DROPDOWN)
MACRO(wxDP_SHOWCENTURY)
MACRO(wxDP_ALLOWNONE)
MACRO(wxDP_DEFAULT)

// wxDirPickerCtrl
MACRO(wxDIRP_DEFAULT_STYLE)
MACRO(wxDIRP_USE_TEXTCTRL)
MACRO(wxDIRP_DIR_MUST_EXIST)
MACRO(wxDIRP_CHANGE_DIR)

// wxFilePickerCtrl
MACRO(wxFLP_DEFAULT_STYLE)
MACRO(wxFLP_USE_TEXTCTRL)
MACRO(wxFLP_OPEN)
MACRO(wxFLP_SAVE)
MACRO(wxFLP_OVERWRITE_PROMPT)
MACRO(wxFLP_FILE_MUST_EXIST)
MACRO(wxFLP_CHANGE_DIR)

// wxFontPickerCtrl
MACRO(wxFNTP_DEFAULT_STYLE)
MACRO(wxFNTP_USE_TEXTCTRL)
MACRO(wxFNTP_FONTDESC_AS_LABEL)
MACRO(wxFNTP_USEFONT_FOR_LABEL)

END_LIBRARY()
