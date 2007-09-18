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

#include "component.h"
#include "plugin.h"
#include "xrcconv.h"
#include "default.xpm"

#include <wx/plotctrl/plotctrl.h>
#include <wx/awx/led.h>
#include <wx/ledBarGraph/ledBarGraph.h>
#include <wx/treelistctrl/treelistctrl.h>

#include <math.h>

#include <wx/object.h>
#include <wx/image.h>
#include <wx/window.h>

///////////////////////////////////////////////////////////////////////////////

/**
Event handler for events generated by wxTreeListCtrl.
*/
class TreeListCtrlEvtHandler : public wxEvtHandler
{
public:
	TreeListCtrlEvtHandler( wxWindow* win, IManager* manager )
	:
	m_window( win ),
	m_manager( manager )
	{
	}

protected:
	void OnColClick( wxListEvent& event );
	void OnColEndDrag( wxListEvent& event );
	void OnLeftDClick( wxMouseEvent& event );

	DECLARE_EVENT_TABLE()
private:
	wxWindow* m_window;
	IManager* m_manager;

};

BEGIN_EVENT_TABLE( TreeListCtrlEvtHandler, wxEvtHandler )
	EVT_LIST_COL_CLICK( wxID_ANY, TreeListCtrlEvtHandler::OnColClick )
	EVT_LIST_COL_END_DRAG( wxID_ANY, TreeListCtrlEvtHandler::OnColEndDrag )
	EVT_LEFT_DCLICK( TreeListCtrlEvtHandler::OnLeftDClick )
END_EVENT_TABLE()

///////////////////////////////////////////////////////////////////////////////
class wxTreeListCtrlComponent : public ComponentBase
{
public:
	void AddImageList( IObject* obj, wxTreeListCtrl* treeListCtrl )
	{
		if ( obj->IsNull( _("column_image_size") ) )
		{
			return;
		}

		wxSize imageSize = obj->GetPropertyAsSize(_("column_image_size"));
		if ( wxDefaultCoord == imageSize.GetWidth() || wxDefaultCoord == imageSize.GetHeight() )
		{
			return;
		}

		wxImageList* images = new wxImageList( imageSize.GetWidth(), imageSize.GetHeight() );
		wxImage image = wxBitmap( default_xpm ).ConvertToImage();
		images->Add( image.Scale( imageSize.GetWidth(), imageSize.GetHeight() ) );
		treeListCtrl->SetImageList( images );
	}

    wxObject* Create(IObject *obj, wxObject *parent)
    {
        wxTreeListCtrl* treeListCtrl = new wxTreeListCtrl( (wxWindow *)parent, -1,
                obj->GetPropertyAsPoint(_("pos")),
                obj->GetPropertyAsSize(_("size")),
                obj->GetPropertyAsInteger(_("style")) | obj->GetPropertyAsInteger(_("window_style")));

		// Add image list.
		AddImageList( obj, treeListCtrl );

		// Connect to event handler.
		treeListCtrl->PushEventHandler( new TreeListCtrlEvtHandler( treeListCtrl, GetManager() ) );

        return treeListCtrl;
    }

    void OnCreated( wxObject* wxobject, wxWindow* wxparent )
    {
		// initialize tree
		wxTreeListCtrl* treeListCtrl = wxDynamicCast( wxparent, wxTreeListCtrl );
		int colCount = treeListCtrl->GetColumnCount();

		// Check for columns
		if ( 0 == colCount )
		{
			return;
		}

        wxTreeItemId root = treeListCtrl->AddRoot (_("Root") );

        wxTreeItemId treeListParent;
        wxTreeItemId treeListItem;
        int n = 0;

		// Build tree.
		treeListItem = treeListCtrl->AppendItem( root, wxString::Format( _("Item #%d"), ++n ) );
		FillItem( treeListCtrl, treeListItem, colCount, n );

		treeListParent = treeListItem;
		for ( int i = 0; i < 5; ++i )
		{
			treeListItem = treeListCtrl->AppendItem( treeListParent, wxString::Format( _("Item #%d"), ++n ) );
			FillItem( treeListCtrl, treeListItem, colCount, n );
		}

		treeListParent = treeListItem;
		for ( int i = 0; i < 5; ++i )
		{
			treeListItem = treeListCtrl->AppendItem( treeListParent, wxString::Format( _("Item #%d"), ++n ) );
			FillItem( treeListCtrl, treeListItem, colCount, n );
		}

        treeListCtrl->ExpandAll( root );
    }

    void FillItem( wxTreeListCtrl* treeListCtrl, wxTreeItemId itemId, int colCount, int row )
    {
    	for ( int i = 0; i < colCount; ++i )
		{
			treeListCtrl->SetItemText( itemId, i, wxString::Format( _("Item #%d, text #%d" ), row, i ) );
		}
    }
};

class wxTreeListCtrlColumnComponent : public ComponentBase
{
public:
	void OnCreated( wxObject* wxobject, wxWindow* wxparent )
	{
		// Easy read-only property access
		IObject* obj = GetManager()->GetIObject( wxobject );
		wxTreeListCtrl* treeList = wxDynamicCast( wxparent, wxTreeListCtrl );

		// Error checking
		if ( !( obj && treeList ) )
		{
			wxLogError( _("wxTreeListCtrlColumnComponent is missing its wxFormBuilder object(%i) or its parent(%i)"), obj,treeList );
			return;
		}

		// Apply image to page
		bool doImageAdd = false;
		wxImageList* imageList;
		IObject* parentObj = GetManager()->GetIObject( wxparent );
		if ( !parentObj->IsNull( _("column_image_size") ) )
		{
			if ( !obj->IsNull( _("image") ) )
			{
				wxSize imageSize = parentObj->GetPropertyAsSize( _("column_image_size") );
				int width = imageSize.GetWidth();
				int height = imageSize.GetHeight();
				if ( width > 0 && height > 0 )
				{
					imageList = treeList->GetImageList();
					if ( imageList != NULL )
					{
						wxImage image = obj->GetPropertyAsBitmap( _("image") ).ConvertToImage();
						imageList->Add( image.Scale( width, height ) );
						doImageAdd = true;
					}
				}
			}
		}

		treeList->AddColumn( obj->GetPropertyAsString( _("name") ),
			obj->GetPropertyAsInteger( _("width") ),
			obj->GetPropertyAsInteger( _("alignment") ),
			doImageAdd ? imageList->GetImageCount() - 1 : -1,
			obj->GetPropertyAsInteger( _("shown") ) != 0,
			obj->GetPropertyAsInteger( _("edit") ) !=0
			);
	}

	void OnSelected( wxObject* wxobject )
	{

	}
};

void TreeListCtrlEvtHandler::OnColClick( wxListEvent& event )
{
	// Select the appropriate column
	wxTreeListCtrl* tlc = wxDynamicCast( m_window, wxTreeListCtrl );
	if ( tlc != NULL )
	{
		m_manager->SelectObject( m_manager->GetChild( m_window, event.GetColumn() ) );
	}
}

void TreeListCtrlEvtHandler::OnColEndDrag( wxListEvent& event )
{
	// Set the width property for the column.
	wxTreeListCtrl* tlc = wxDynamicCast( m_window, wxTreeListCtrl );
	if ( tlc != NULL )
	{
		wxObject* col = m_manager->GetChild( m_window, event.GetColumn() );
		m_manager->SelectObject( col );
		m_manager->ModifyProperty( col, _("width"),
			wxString::Format( wxT("%i"), tlc->GetColumnWidth( event.GetColumn() ) ), true );
	}
}

void TreeListCtrlEvtHandler::OnLeftDClick( wxMouseEvent& event )
{
	// Set the width property for the column.
	wxTreeListCtrl* tlc = wxDynamicCast( m_window, wxTreeListCtrl );
	if ( tlc != NULL )
	{
		int count = m_manager->GetChildCount( tlc );
		wxLogDebug( wxT("Child count: %i"), count );
		for ( int i =0; i < count; ++i )
		{
			wxObject* col = m_manager->GetChild( m_window, i );
			IObject* childObj = m_manager->GetIObject( col );
			int colWidth = tlc->GetColumnWidth( i );
			if ( childObj->GetPropertyAsInteger( _("width") ) != colWidth )
			{
				m_manager->ModifyProperty( col, _("width"),
					wxString::Format( wxT("%i"), colWidth ), true );
				m_manager->SelectObject( col );
				// One dclick means at most one column change.
				break;
			}
		}
	}
}

class PlotCtrlComponent : public ComponentBase
{
public:
    wxObject* Create(IObject *obj, wxObject *parent)
    {
        // Set plot style
        wxPlotCtrl* plot = new wxPlotCtrl((wxWindow*)parent,-1,
                                          obj->GetPropertyAsPoint(_("pos")),
                                          obj->GetPropertyAsSize(_("size")) );

        plot->SetScrollOnThumbRelease( obj->GetPropertyAsInteger(_("scroll_on_thumb_release")) != 0 );
        plot->SetCrossHairCursor( obj->GetPropertyAsInteger( _("crosshair_cursor") ) != 0 );
        plot->SetDrawSymbols( obj->GetPropertyAsInteger( _("draw_symbols") ) != 0 );
        plot->SetDrawLines( obj->GetPropertyAsInteger( _("draw_lines") ) != 0 );
        plot->SetDrawSpline( obj->GetPropertyAsInteger( _("draw_spline") ) != 0 );
        plot->SetDrawGrid( obj->GetPropertyAsInteger( _("draw_grid") ) != 0 );

        plot->SetShowXAxis( obj->GetPropertyAsInteger( _("show_x_axis") ) != 0 );
        plot->SetShowYAxis( obj->GetPropertyAsInteger( _("show_y_axis") ) != 0 );
        plot->SetShowXAxisLabel( obj->GetPropertyAsInteger( _("show_x_axis_label") ) != 0 );
        plot->SetShowYAxisLabel( obj->GetPropertyAsInteger( _("show_y_axis_label") ) != 0 );
        plot->SetShowPlotTitle( obj->GetPropertyAsInteger( _("show_plot_title") ) != 0 );
        plot->SetShowKey( obj->GetPropertyAsInteger( _("show_key") ) != 0 );

        plot->SetAreaMouseFunction( (wxPlotCtrlMouse_Type)obj->GetPropertyAsInteger( _("area_mouse_function") ) );
        plot->SetAreaMouseMarker( (wxPlotCtrlMarker_Type)obj->GetPropertyAsInteger( _("area_mouse_marker") ) );

        if ( !obj->IsNull( _("grid_colour") ) )
        {
            plot->SetGridColour( obj->GetPropertyAsColour( _("grid_colour") ) );
        }
        if ( !obj->IsNull( _("border_colour") ) )
        {
            plot->SetBorderColour( obj->GetPropertyAsColour( _("border_colour") ) );
        }

        if ( !obj->IsNull( _("axis_font") ) )
        {
            plot->SetAxisFont( obj->GetPropertyAsFont( _("axis_font") ) );
        }
        if ( !obj->IsNull( _("axis_colour") ) )
        {
            plot->SetAxisColour( obj->GetPropertyAsColour( _("axis_colour") ) );
        }

        if ( !obj->IsNull( _("axis_label_font") ) )
        {
            plot->SetAxisLabelFont( obj->GetPropertyAsFont( _("axis_label_font") ) );
        }
        if ( !obj->IsNull( _("axis_label_colour") ) )
        {
            plot->SetAxisLabelColour( obj->GetPropertyAsColour( _("axis_label_colour") ) );
        }

        if ( !obj->IsNull( _("plot_title_font") ) )
        {
            plot->SetPlotTitleFont( obj->GetPropertyAsFont( _("plot_title_font") ) );
        }
        if ( !obj->IsNull( _("plot_title_colour") ) )
        {
            plot->SetPlotTitleColour( obj->GetPropertyAsColour( _("plot_title_colour") ) );
        }

        if ( !obj->IsNull( _("key_font") ) )
        {
            plot->SetKeyFont( obj->GetPropertyAsFont( _("key_font") ) );
        }
        if ( !obj->IsNull( _("key_colour") ) )
        {
            plot->SetKeyColour( obj->GetPropertyAsColour( _("key_colour") ) );
        }

        plot->SetXAxisLabel( obj->GetPropertyAsString( _("x_axis_label") ) );
        plot->SetYAxisLabel( obj->GetPropertyAsString( _("y_axis_label") ) );
        plot->SetPlotTitle( obj->GetPropertyAsString( _("plot_title") ) );
        plot->SetKeyPosition( obj->GetPropertyAsPoint( _("key_position") ) );

        wxPlotFunction plotFunc;
        plotFunc.Create( obj->GetPropertyAsString(_("sample_function")), wxT("x") );
        if ( plotFunc.Ok() )
        {
            plot->AddCurve( plotFunc, true, true );
        }

        return plot;

    }
    /*TiXmlElement* ExportToXrc(IObject *obj)
    {
    	ObjectToXrcFilter xrc(obj, _("wxPlotWindow"), obj->GetPropertyAsString(_("name")));
    	xrc.AddWindowProperties();
    	xrc.AddProperty(_("style"),_("style"), XRC_TYPE_BITLIST);
    	return xrc.GetXrcObject();
    }

    TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
    {
    	XrcToXfbFilter filter(xrcObj, _("wxPlotWindow"));
    	filter.AddWindowProperties();
    	filter.AddProperty(_("style"),_("style"), XRC_TYPE_BITLIST);
    	return filter.GetXfbObject();
    }*/
};

class awxLedComponent : public ComponentBase
{
public:
    wxObject* Create(IObject *obj, wxObject *parent)
    {
        awxLed* led = new awxLed((wxWindow *)parent, -1,
                                 obj->GetPropertyAsPoint(_("pos")),
                                 obj->GetPropertyAsSize(_("size")),
                                 (awxLedColour)obj->GetPropertyAsInteger(_("color")),
                                 obj->GetPropertyAsInteger(_("window_style")));
        led->SetState( (awxLedState)obj->GetPropertyAsInteger(_("state")));
        return led;
    }
};

class wxLedBarGraphComponent : public ComponentBase
{
public:
    wxObject* Create(IObject *obj, wxObject *parent)
    {
        wxLedBarGraph* ledbg = new wxLedBarGraph((wxWindow *)parent, -1,
                obj->GetPropertyAsPoint(_("pos")),
                obj->GetPropertyAsSize(_("size")),
                obj->GetPropertyAsInteger(_("window_style")));

        ledbg->SetDrawingMode( (ledBGDrawMode) obj->GetPropertyAsInteger( _("drawing_mode") ));
        ledbg->SetSizingMode( (ledBGSizeMode) obj->GetPropertyAsInteger( _("sizing_mode") ));
        ledbg->SetOrientation( (ledBGOrient) obj->GetPropertyAsInteger( _("orientation") ));

        ledbg->SetBarWidths( obj->GetPropertyAsInteger( _("bar_widths") ));
        ledbg->SetNBars( obj->GetPropertyAsInteger( _("nbars") ));

        double max = obj->GetPropertyAsFloat( _("max_value"));
        double min = obj->GetPropertyAsFloat( _("min_value"));

        ledbg->SetMaxValue( max );
        ledbg->SetMinValue( min );

        double val = obj->GetPropertyAsFloat( _("value") );
        val = val* (max-min) + min;
        ledbg->SetValue( val );

        return ledbg;
    }
};

///////////////////////////////////////////////////////////////////////////////

BEGIN_LIBRARY()

// wxPlotWindow
WINDOW_COMPONENT( "wxPlotCtrl",PlotCtrlComponent)
MACRO(wxPLOTCTRL_MOUSE_NOTHING)
MACRO(wxPLOTCTRL_MOUSE_ZOOM)
MACRO(wxPLOTCTRL_MOUSE_SELECT)
MACRO(wxPLOTCTRL_MOUSE_DESELECT)
MACRO(wxPLOTCTRL_MOUSE_PAN)
MACRO(wxPLOTCTRL_MARKER_NONE)
MACRO(wxPLOTCTRL_MARKER_RECT)
MACRO(wxPLOTCTRL_MARKER_VERT)
MACRO(wxPLOTCTRL_MARKER_HORIZ)

// awxLed
WINDOW_COMPONENT( "awxLed", awxLedComponent )
MACRO(awxLED_OFF)
MACRO(awxLED_ON)
MACRO(awxLED_BLINK)
MACRO(awxLED_LUCID)
MACRO(awxLED_RED)
MACRO(awxLED_GREEN)
MACRO(awxLED_YELLOW)

// wxLedBarGraph
WINDOW_COMPONENT( "wxLedBarGraph", wxLedBarGraphComponent )
MACRO(ledBG_DOUBLE_SIDED)
MACRO(ledBG_SINGLE_SIDED_TOP_LEFT)
MACRO(ledBG_SINGLE_SIDED_BOTTOM_RIGHT)
MACRO(ledBG_FIXED_N_BARS)
MACRO(ledBG_FIXED_BAR_SIZE)
MACRO(ledBG_ORIENT_VERTICAL)
MACRO(ledBG_ORIENT_HORIZONTAL)

// wxTreeListCtrl
WINDOW_COMPONENT( "wxTreeListCtrl", wxTreeListCtrlComponent )
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
MACRO(wxTR_VIRTUAL)

// wxTreeListCtrl
ABSTRACT_COMPONENT( "wxTreeListCtrlColumn", wxTreeListCtrlColumnComponent )

END_LIBRARY()
