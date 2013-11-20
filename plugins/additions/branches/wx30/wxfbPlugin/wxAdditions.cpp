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

#include <math.h>

#include <wx/object.h>
#include <wx/image.h>
#include <wx/imaglist.h>
#include <wx/window.h>

///////////////////////////////////////////////////////////////////////////////

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

END_LIBRARY()
