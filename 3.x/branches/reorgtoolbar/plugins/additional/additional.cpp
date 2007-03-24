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

#include <wx/calctrl.h>
#include <wx/html/htmlwin.h>
#include <wx/treectrl.h>
#include <wx/spinbutt.h>
#include <wx/spinctrl.h>
#include <wx/tglbtn.h>
#include <wx/scrolbar.h>
#include <wx/checklst.h>
#include <wx/datectrl.h>
#include <wx/clrpicker.h>
#include <wx/grid.h>

///////////////////////////////////////////////////////////////////////////////

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
	void OnGridClick( wxGridEvent& event );
	void OnColourPickerColourChanged( wxColourPickerEvent& event );

	DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE( ComponentEvtHandler, wxEvtHandler )
	EVT_COLOURPICKER_CHANGED( -1, ComponentEvtHandler::OnColourPickerColourChanged )

	// Grid also seems to ignore clicks
	EVT_GRID_CELL_LEFT_CLICK( ComponentEvtHandler::OnGridClick )
	EVT_GRID_LABEL_LEFT_CLICK( ComponentEvtHandler::OnGridClick )
END_EVENT_TABLE()

///////////////////////////////////////////////////////////////////////////////

class CalendarCtrlComponent : public ComponentBase
{
public:
	wxObject* Create(IObject *obj, wxObject *parent)
	{
		return new wxCalendarCtrl((wxWindow *)parent,-1,
			wxDefaultDateTime,
			obj->GetPropertyAsPoint(_("pos")),
			obj->GetPropertyAsSize(_("size")),
			obj->GetPropertyAsInteger(_("style")) | obj->GetPropertyAsInteger(_("window_style")));
	}

	TiXmlElement* ExportToXrc(IObject *obj)
	{
		ObjectToXrcFilter xrc(obj, _("wxCalendarCtrl"), obj->GetPropertyAsString(_("name")));
		xrc.AddWindowProperties();
		//xrc.AddProperty(_("style"),_("style"), XRC_TYPE_BITLIST);
		return xrc.GetXrcObject();
	}

	TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
	{
		XrcToXfbFilter filter(xrcObj, _("wxCalendarCtrl"));
		filter.AddWindowProperties();
		//filter.AddProperty(_("style"),_("style"), XRC_TYPE_BITLIST);
		return filter.GetXfbObject();
	}
};

class DatePickerCtrlComponent : public ComponentBase
{
public:
	wxObject* Create(IObject *obj, wxObject *parent)
	{
		return new wxDatePickerCtrl((wxWindow *)parent,-1,
			wxDefaultDateTime,
			obj->GetPropertyAsPoint(_("pos")),
			obj->GetPropertyAsSize(_("size")),
			obj->GetPropertyAsInteger(_("style")) | obj->GetPropertyAsInteger(_("window_style")));
	}

	TiXmlElement* ExportToXrc(IObject *obj)
	{
		ObjectToXrcFilter xrc(obj, _("wxDatePickerCtrl"), obj->GetPropertyAsString(_("name")));
		xrc.AddWindowProperties();
		//xrc.AddProperty(_("style"),_("style"), XRC_TYPE_BITLIST);
		return xrc.GetXrcObject();
	}

	TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
	{
		XrcToXfbFilter filter(xrcObj, _("wxDatePickerCtrl"));
		filter.AddWindowProperties();
		//filter.AddProperty(_("style"),_("style"), XRC_TYPE_BITLIST);
		return filter.GetXfbObject();
	}
};

class HtmlWindowComponent : public ComponentBase
{
public:
	wxObject* Create(IObject *obj, wxObject *parent)
	{
		wxHtmlWindow *hw = new wxHtmlWindow((wxWindow *)parent,-1,
			obj->GetPropertyAsPoint(_("pos")),
			obj->GetPropertyAsSize(_("size")),
			obj->GetPropertyAsInteger(_("style")) | obj->GetPropertyAsInteger(_("window_style")));

		wxString dummy_page(
			wxT("<b>wxHtmlWindow</b><br />")
			wxT("This is a dummy page.</body></html>"));

		hw->SetPage(dummy_page);

		return hw;
	}

	TiXmlElement* ExportToXrc(IObject *obj)
	{
		ObjectToXrcFilter xrc(obj, _("wxHtmlWindow"), obj->GetPropertyAsString(_("name")));
		xrc.AddWindowProperties();
		return xrc.GetXrcObject();
	}

	TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
	{
		XrcToXfbFilter filter(xrcObj, _("wxHtmlWindow"));
		filter.AddWindowProperties();
		return filter.GetXfbObject();
	}
};

class RadioButtonComponent : public ComponentBase
{
public:
	wxObject* Create(IObject *obj, wxObject *parent)
	{
		wxRadioButton *rb = new wxRadioButton((wxWindow *)parent,-1,
			obj->GetPropertyAsString(_("label")),
			obj->GetPropertyAsPoint(_("pos")),
			obj->GetPropertyAsSize(_("size")),
			obj->GetPropertyAsInteger(_("style")) | obj->GetPropertyAsInteger(_("window_style")));

		rb->SetValue( ( obj->GetPropertyAsInteger(_("value")) != 0 ) );
		return rb;
	}

	TiXmlElement* ExportToXrc(IObject *obj)
	{
		ObjectToXrcFilter xrc(obj, _("wxRadioButton"), obj->GetPropertyAsString(_("name")));
		xrc.AddWindowProperties();
		//xrc.AddProperty(_("style"),_("style"), XRC_TYPE_BITLIST);
		xrc.AddProperty(_("label"),_("label"), XRC_TYPE_TEXT);
		xrc.AddProperty(_("value"),_("value"), XRC_TYPE_BOOL);
		return xrc.GetXrcObject();
	}

	TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
	{
		XrcToXfbFilter filter(xrcObj, _("wxRadioButton"));
		filter.AddWindowProperties();
		//filter.AddProperty(_("style"),_("style"), XRC_TYPE_BITLIST);
		filter.AddProperty(_("label"),_("label"), XRC_TYPE_TEXT);
		filter.AddProperty(_("value"),_("value"), XRC_TYPE_BOOL);
		return filter.GetXfbObject();
	}
};

class ToggleButtonComponent : public ComponentBase
{
public:
	wxObject* Create(IObject *obj, wxObject *parent)
	{
		wxToggleButton* tb = new wxToggleButton((wxWindow *)parent,-1,
			obj->GetPropertyAsString(_("label")),
			obj->GetPropertyAsPoint(_("pos")),
			obj->GetPropertyAsSize(_("size")),
			obj->GetPropertyAsInteger(_("window_style")));

		tb->SetValue( ( obj->GetPropertyAsInteger(_("value")) != 0 ) );
		return tb;
	}

	TiXmlElement* ExportToXrc(IObject *obj)
	{
		ObjectToXrcFilter xrc(obj, _("wxToggleButton"), obj->GetPropertyAsString(_("name")));
		xrc.AddWindowProperties();
		//xrc.AddProperty(_("style"),_("style"), XRC_TYPE_BITLIST);
		xrc.AddProperty(_("label"),_("label"), XRC_TYPE_TEXT);
		xrc.AddProperty(_("value"),_("checked"), XRC_TYPE_BOOL);
		return xrc.GetXrcObject();
	}

	TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
	{
		XrcToXfbFilter filter(xrcObj, _("wxToggleButton"));
		filter.AddWindowProperties();
		//filter.AddProperty(_("style"),_("style"), XRC_TYPE_BITLIST);
		filter.AddProperty(_("label"),_("label"), XRC_TYPE_TEXT);
		filter.AddProperty(_("checked"),_("value"), XRC_TYPE_BOOL);
		return filter.GetXfbObject();
	}

};

class TreeCtrlComponent : public ComponentBase
{
public:
	wxObject* Create(IObject *obj, wxObject *parent)
	{
		wxTreeCtrl *tc = new wxTreeCtrl((wxWindow *)parent,-1,
			obj->GetPropertyAsPoint(_("pos")),
			obj->GetPropertyAsSize(_("size")),
			obj->GetPropertyAsInteger(_("style")) | obj->GetPropertyAsInteger(_("window_style")));

		// dummy nodes
		wxTreeItemId root = tc->AddRoot(wxT("root node"));
		wxTreeItemId node1 = tc->AppendItem(root,wxT("node1"));
		wxTreeItemId node2 = tc->AppendItem(root,wxT("node2"));
		wxTreeItemId node3 = tc->AppendItem(node2,wxT("node3"));
		tc->Expand(root);
		tc->Expand(node1);
		tc->Expand(node2);
		tc->Expand(node3);

		return tc;
	}

	TiXmlElement* ExportToXrc(IObject *obj)
	{
		ObjectToXrcFilter xrc(obj, _("wxTreeCtrl"), obj->GetPropertyAsString(_("name")));
		xrc.AddWindowProperties();
		return xrc.GetXrcObject();
	}

	TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
	{
		XrcToXfbFilter filter(xrcObj, _("wxTreeCtrl"));
		filter.AddWindowProperties();
		return filter.GetXfbObject();
	}
};

class ScrollBarComponent : public ComponentBase
{
public:
	wxObject* Create(IObject *obj, wxObject *parent)
	{
		wxScrollBar *sb = new wxScrollBar((wxWindow *)parent,-1,
			obj->GetPropertyAsPoint(_("pos")),
			obj->GetPropertyAsSize(_("size")),
			obj->GetPropertyAsInteger(_("style")) | obj->GetPropertyAsInteger(_("window_style")));

        sb->SetScrollbar(obj->GetPropertyAsInteger(_T("value")),
            obj->GetPropertyAsInteger(_T("thumbsize")),
            obj->GetPropertyAsInteger(_T("range")),
            obj->GetPropertyAsInteger(_T("pagesize")));
        return sb;
	}

	TiXmlElement* ExportToXrc(IObject *obj)
	{
		ObjectToXrcFilter xrc(obj, _("wxScrollBar"), obj->GetPropertyAsString(_("name")));
		xrc.AddWindowProperties();
		xrc.AddProperty(_("value"), _("value"), XRC_TYPE_INTEGER);
		xrc.AddProperty(_("thumbsize"), _("thumbsize"), XRC_TYPE_INTEGER);
		xrc.AddProperty(_("range"), _("range"), XRC_TYPE_INTEGER);
		xrc.AddProperty(_("pagesize"), _("pagesize"), XRC_TYPE_INTEGER);
		return xrc.GetXrcObject();
	}

	TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
	{
		XrcToXfbFilter filter(xrcObj, _("wxScrollBar"));
		filter.AddWindowProperties();
		filter.AddProperty(_("value"), _("value"), XRC_TYPE_INTEGER);
		filter.AddProperty(_("thumbsize"), _("thumbsize"), XRC_TYPE_INTEGER);
		filter.AddProperty(_("range"), _("range"), XRC_TYPE_INTEGER);
		filter.AddProperty(_("pagesize"), _("pagesize"), XRC_TYPE_INTEGER);
		return filter.GetXfbObject();
	}
};

class SpinCtrlComponent : public ComponentBase
{
public:
	wxObject* Create(IObject *obj, wxObject *parent)
	{
		return new wxSpinCtrl((wxWindow *)parent,-1,
			obj->GetPropertyAsString(_("value")),
			obj->GetPropertyAsPoint(_("pos")),
			obj->GetPropertyAsSize(_("size")),
			obj->GetPropertyAsInteger(_("style")) | obj->GetPropertyAsInteger(_("window_style")),
			obj->GetPropertyAsInteger(_("min")),
			obj->GetPropertyAsInteger(_("max")),
			obj->GetPropertyAsInteger(_("initial")));
	}

	TiXmlElement* ExportToXrc(IObject *obj)
	{
		ObjectToXrcFilter xrc(obj, _("wxSpinCtrl"), obj->GetPropertyAsString(_("name")));
		xrc.AddWindowProperties();
		xrc.AddProperty(_("initial"),_("value"), XRC_TYPE_TEXT);
		xrc.AddProperty(_("min"),_("min"), XRC_TYPE_INTEGER);
		xrc.AddProperty(_("max"),_("max"), XRC_TYPE_INTEGER);
		return xrc.GetXrcObject();
	}

	TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
	{
		XrcToXfbFilter filter(xrcObj, _("wxSpinCtrl"));
		filter.AddWindowProperties();
		filter.AddProperty(_("value"),_("value"), XRC_TYPE_TEXT);
		filter.AddProperty(_("value"),_("initial"), XRC_TYPE_TEXT);
		filter.AddProperty(_("min"),_("min"), XRC_TYPE_INTEGER);
		filter.AddProperty(_("max"),_("max"), XRC_TYPE_INTEGER);

		return filter.GetXfbObject();
	}
};

class SpinButtonComponent : public ComponentBase
{
public:
	wxObject* Create(IObject *obj, wxObject *parent)
	{
		return new wxSpinButton((wxWindow *)parent,-1,
			obj->GetPropertyAsPoint(_("pos")),
			obj->GetPropertyAsSize(_("size")),
			obj->GetPropertyAsInteger(_("style")) | obj->GetPropertyAsInteger(_("window_style")));
	}

	TiXmlElement* ExportToXrc(IObject *obj)
	{
		ObjectToXrcFilter xrc(obj, _("wxSpinButton"), obj->GetPropertyAsString(_("name")));
		xrc.AddWindowProperties();
		return xrc.GetXrcObject();
	}

	TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
	{
		XrcToXfbFilter filter(xrcObj, _("wxSpinButton"));
		filter.AddWindowProperties();
		return filter.GetXfbObject();
	}
};

class CheckListBoxComponent : public ComponentBase
{
public:

	wxObject* Create(IObject *obj, wxObject *parent)
	{
		wxArrayString choices (obj->GetPropertyAsArrayString(_("choices")));
		wxCheckListBox *cl =
			new wxCheckListBox((wxWindow *)parent,-1,
			obj->GetPropertyAsPoint(_("pos")),
			obj->GetPropertyAsSize(_("size")),
			choices,
			obj->GetPropertyAsInteger(_("style")) | obj->GetPropertyAsInteger(_("window_style")));

		return cl;
	}

	TiXmlElement* ExportToXrc(IObject *obj)
	{
		ObjectToXrcFilter xrc(obj, _("wxCheckListBox"), obj->GetPropertyAsString(_("name")));
		xrc.AddWindowProperties();
		//xrc.AddProperty(_("style"),_("style"), XRC_TYPE_BITLIST);
		xrc.AddProperty(_("choices"), _("content"), XRC_TYPE_STRINGLIST);
		return xrc.GetXrcObject();
	}

	TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
	{
		XrcToXfbFilter filter(xrcObj, _("wxCheckListBox"));
		filter.AddWindowProperties();
		//filter.AddProperty(_("style"),_("style"), XRC_TYPE_BITLIST);
		filter.AddProperty(_("content"), _("choices"), XRC_TYPE_STRINGLIST);
		return filter.GetXfbObject();
	}
};

class ColourPickerComponent : public ComponentBase
{
public:
	wxObject* Create(IObject *obj, wxObject *parent)
	{
		wxColourPickerCtrl* colourpicker = new wxColourPickerCtrl(
			(wxWindow*)parent,
			obj->GetPropertyAsInteger(_("id")),
			obj->GetPropertyAsColour(_("colour")),
			obj->GetPropertyAsPoint(_("pos")),
			obj->GetPropertyAsSize(_("size")),
			obj->GetPropertyAsInteger(_("style")) | obj->GetPropertyAsInteger(_("window_style"))
			);

		colourpicker->PushEventHandler( new ComponentEvtHandler( colourpicker, GetManager() ) );
		return colourpicker;
	}

	TiXmlElement* ExportToXrc(IObject *obj)
	{
		ObjectToXrcFilter xrc(obj, _("wxColourPickerCtrl"), obj->GetPropertyAsString(_("name")));
		xrc.AddProperty(_("colour"),_("value"),XRC_TYPE_COLOUR);
		xrc.AddWindowProperties();
		return xrc.GetXrcObject();
	}

	TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
	{
		XrcToXfbFilter filter(xrcObj, _("wxColourPickerCtrl"));
		filter.AddProperty(_("value"),_("colour"),XRC_TYPE_COLOUR);
		filter.AddWindowProperties();
		return filter.GetXfbObject();
	}
};

void ComponentEvtHandler::OnColourPickerColourChanged( wxColourPickerEvent& event )
{
	wxColourPickerCtrl* window = wxDynamicCast( m_window, wxColourPickerCtrl );
	if ( window != NULL )
	{
		wxColour colour = window->GetColour();
		m_manager->ModifyProperty( window, _("colour"), wxString::Format(wxT("%d,%d,%d"),colour.Red(),colour.Green(),colour.Blue())  );
	}
}

class GridComponent : public ComponentBase
{
public:

	wxObject* Create(IObject *obj, wxObject *parent)
	{
		wxGrid *grid = new wxGrid((wxWindow *)parent,-1,
			obj->GetPropertyAsPoint(_("pos")),
			obj->GetPropertyAsSize(_("size")),
			obj->GetPropertyAsInteger(_("window_style")));

		grid->CreateGrid(
			obj->GetPropertyAsInteger(_("rows")),
			obj->GetPropertyAsInteger(_("cols")));

		grid->PushEventHandler( new ComponentEvtHandler( grid, GetManager() ) );

		return grid;
	}

	TiXmlElement* ExportToXrc(IObject *obj)
	{
		ObjectToXrcFilter xrc(obj, _("wxGrid"), obj->GetPropertyAsString(_("name")));
		xrc.AddWindowProperties();
		return xrc.GetXrcObject();
	}

	TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
	{
		XrcToXfbFilter filter(xrcObj, _("wxGrid"));
		filter.AddWindowProperties();
		return filter.GetXfbObject();
	}
};

void ComponentEvtHandler::OnGridClick( wxGridEvent& event )
{
	m_manager->SelectObject( m_window );
	event.Skip();
}

///////////////////////////////////////////////////////////////////////////////

BEGIN_LIBRARY()

WINDOW_COMPONENT("wxCalendarCtrl",CalendarCtrlComponent)
WINDOW_COMPONENT("wxDatePickerCtrl", DatePickerCtrlComponent )
WINDOW_COMPONENT("wxHtmlWindow",HtmlWindowComponent)
WINDOW_COMPONENT("wxRadioButton",RadioButtonComponent)
WINDOW_COMPONENT("wxToggleButton",ToggleButtonComponent)
WINDOW_COMPONENT("wxTreeCtrl",TreeCtrlComponent)
WINDOW_COMPONENT("wxGrid",GridComponent)
WINDOW_COMPONENT("wxScrollBar",ScrollBarComponent)
WINDOW_COMPONENT("wxSpinCtrl",SpinCtrlComponent)
WINDOW_COMPONENT("wxSpinButton",SpinButtonComponent)

// wxCheckListBox
WINDOW_COMPONENT("wxCheckListBox",CheckListBoxComponent)

// wxColourPickerCtrl
WINDOW_COMPONENT("wxColourPickerCtrl", ColourPickerComponent)
MACRO(wxCLRP_DEFAULT_STYLE)
MACRO(wxCLRP_USE_TEXTCTRL)
MACRO(wxCLRP_SHOW_LABEL)

// wxCalendarCtrl
MACRO(wxCAL_SUNDAY_FIRST)
MACRO(wxCAL_MONDAY_FIRST)
MACRO(wxCAL_SHOW_HOLIDAYS)
MACRO(wxCAL_NO_YEAR_CHANGE)
MACRO(wxCAL_NO_MONTH_CHANGE)
MACRO(wxCAL_SHOW_SURROUNDING_WEEKS)
MACRO(wxCAL_SEQUENTIAL_MONTH_SELECTION)

// wxDatePickerCtrl
MACRO(wxDP_SPIN)
MACRO(wxDP_DROPDOWN)
MACRO(wxDP_SHOWCENTURY)
MACRO(wxDP_ALLOWNONE)
MACRO(wxDP_DEFAULT)

// wxHtmlWindow
MACRO(wxHW_SCROLLBAR_NEVER)
MACRO(wxHW_SCROLLBAR_AUTO)
MACRO(wxHW_NO_SELECTION)

// wxTreeCtrl
MACRO(wxTR_EDIT_LABELS)
MACRO(wxTR_NO_BUTTONS)
MACRO(wxTR_HAS_BUTTONS)
MACRO(wxTR_TWIST_BUTTONS)
MACRO(wxTR_NO_LINES)
MACRO(wxTR_FULL_ROW_HIGHLIGHT)
MACRO(wxTR_LINES_AT_ROOT)
MACRO(wxTR_HIDE_ROOT)
MACRO(wxTR_ROW_LINES)
MACRO(wxTR_HAS_VARIABLE_ROW_HEIGHT)
MACRO(wxTR_SINGLE)
MACRO(wxTR_MULTIPLE)
MACRO(wxTR_EXTENDED)
MACRO(wxTR_DEFAULT_STYLE)

// wxRadioButton
MACRO(wxRB_GROUP)
MACRO(wxRB_SINGLE)
MACRO(wxRB_USE_CHECKBOX)

// wxScrollBar
MACRO(wxSB_HORIZONTAL)
MACRO(wxSB_VERTICAL)

// wxSpinCtrl and wxSpinButton
MACRO(wxSP_ARROW_KEYS)
MACRO(wxSP_WRAP)
MACRO(wxSP_HORIZONTAL)
MACRO(wxSP_VERTICAL)

END_LIBRARY()

