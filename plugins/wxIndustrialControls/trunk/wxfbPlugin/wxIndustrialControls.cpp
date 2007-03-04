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
#include <tinyxml.h>


#include "wx/wxIndustrialControls/LCDWindow.h"
#include "wx/wxIndustrialControls/LCDClock.h"
#include "wx/wxIndustrialControls/AngularMeter.h"
#include "wx/wxIndustrialControls/AngularRegulator.h"
#include "wx/wxIndustrialControls/LinearMeter.h"
#include "wx/wxIndustrialControls/LinearRegulator.h"


class LCDDisplayComponent : public ComponentBase
{
public:
	wxObject* Create(IObject *obj, wxObject *parent)
	{
	   kwxLCDDisplay  *lcd = new kwxLCDDisplay( (wxWindow*)parent,
	     obj->GetPropertyAsPoint(_("pos")),
		 obj->GetPropertyAsSize(_("size")));

	   lcd->SetNumberDigits( obj->GetPropertyAsInteger( _("n_digits")) );
	   lcd->SetValue(obj->GetPropertyAsString( _("value"))) ;

	   if (!obj->IsNull(_("light_colour")))
	     lcd->SetLightColour( obj->GetPropertyAsColour( _("light_colour")) );

       if (!obj->IsNull(_("gray_colour")))
	     lcd->SetGrayColour( obj->GetPropertyAsColour( _("gray_colour")) );

	   return lcd;
	}
};

class LCDClockComponent : public ComponentBase
{
public:
	wxObject* Create(IObject *obj, wxObject *parent)
	{
	   kwxLCDClock *lcd = new kwxLCDClock( (wxWindow*)parent,
	     obj->GetPropertyAsPoint(_("pos")),
		 obj->GetPropertyAsSize(_("size")));

       lcd->SetNumberDigits( obj->GetPropertyAsInteger( _("n_digits")) );
       lcd->SetValue(obj->GetPropertyAsString( _("value"))) ;

	   if (!obj->IsNull(_("light_colour")))
	     lcd->SetLightColour( obj->GetPropertyAsColour( _("light_colour")) );

       if (!obj->IsNull(_("gray_colour")))
	     lcd->SetGrayColour( obj->GetPropertyAsColour( _("gray_colour")) );

	   if (obj->GetPropertyAsInteger( _("start_clock")))
	     lcd->StartClock();
	   return lcd;
	}
};

class AngularMeterComponent : public ComponentBase
{
	wxObject* Create(IObject *obj, wxObject *parent)
	{
      kwxAngularMeter *angularmeter = new kwxAngularMeter((wxWindow*)parent, -1, wxT(""),
  				   obj->GetPropertyAsPoint(_("pos")),
		           obj->GetPropertyAsSize(_("size")));

      angularmeter->SetNumSectors(obj->GetPropertyAsInteger(_("num_sectors")));
      angularmeter->SetNumTick(obj->GetPropertyAsInteger(_("num_tick")));
      angularmeter->SetRange(obj->GetPropertyAsInteger(_("range_min")),obj->GetPropertyAsInteger(_("range_max"))) ;
	  angularmeter->SetAngle(obj->GetPropertyAsInteger(_("angle_min")),obj->GetPropertyAsInteger(_("angle_max"))) ;
	  angularmeter->SetValue(obj->GetPropertyAsInteger(_("value")));
      angularmeter->DrawCurrent(obj->GetPropertyAsInteger(_("draw_current"))) ;

      if (!obj->IsNull(_("needle_colour")))
        angularmeter->SetNeedleColour(obj->GetPropertyAsColour(_("needle_colour")));

      if (!obj->IsNull(_("back_colour")))
        angularmeter->SetBackColour(obj->GetPropertyAsColour(_("back_colour")));

      if (!obj->IsNull(_("border_colour")))
        angularmeter->SetBorderColour(obj->GetPropertyAsColour(_("border_colour")));

      if (!obj->IsNull(_("text_font")))
        angularmeter->SetTxtFont(obj->GetPropertyAsFont(_("text_font")));

      return angularmeter;
	}
};

class AngularRegulatorComponent : public ComponentBase
{
	wxObject* Create(IObject *obj, wxObject *parent)
	{
      kwxAngularRegulator * angularreg = new kwxAngularRegulator((wxWindow*)parent,-1,wxT(""),
  				   obj->GetPropertyAsPoint(_("pos")),
		           obj->GetPropertyAsSize(_("size")) );

	  angularreg->SetRange(obj->GetPropertyAsInteger(_("range_min")),obj->GetPropertyAsInteger(_("range_max"))) ;
	  angularreg->SetAngle(obj->GetPropertyAsInteger(_("angle_min")),obj->GetPropertyAsInteger(_("angle_max"))) ;
	  angularreg->SetValue(obj->GetPropertyAsInteger(_("value"))) ;

	  if (!obj->IsNull(_("ext_circle_colour")))
	    angularreg->SetExtCircleColour(obj->GetPropertyAsColour(_("ext_circle_colour"))) ;

	  if (!obj->IsNull(_("int_circle_colour")))
	    angularreg->SetIntCircleColour(obj->GetPropertyAsColour(_("int_circle_colour"))) ;

	  if (!obj->IsNull(_("tags_colour")))
	    angularreg->SetTagsColour(obj->GetPropertyAsColour(_("tags_colour"))) ;

	  if (!obj->IsNull(_("knob_border_colour")))
	    angularreg->SetKnobBorderColour(obj->GetPropertyAsColour(_("knob_border_colour"))) ;

	  if (!obj->IsNull(_("knob_colour")))
	    angularreg->SetKnobColour(obj->GetPropertyAsColour(_("knob_colour"))) ;

	  return angularreg;
	}
};

class LinearMeterComponent : public ComponentBase
{
	wxObject* Create(IObject *obj, wxObject *parent)
	{
      kwxLinearMeter *linearmeter = new kwxLinearMeter((wxWindow*)parent, -1, wxT(""),
  				   obj->GetPropertyAsPoint(_("pos")),
		           obj->GetPropertyAsSize(_("size")));

      linearmeter->SetRangeVal(obj->GetPropertyAsInteger(_("range_min")),obj->GetPropertyAsInteger(_("range_max")));
      linearmeter->SetValue(obj->GetPropertyAsInteger(_("value")));
	  linearmeter->SetOrizDirection(obj->GetPropertyAsInteger(_("horiz_direction")));
	  linearmeter->ShowCurrent(obj->GetPropertyAsInteger(_("show_current")));
	  linearmeter->ShowLimits(obj->GetPropertyAsInteger(_("show_limits")));

	  if (!obj->IsNull(_("active_bar_colour")))
        linearmeter->SetActiveBarColour(obj->GetPropertyAsColour(_("active_bar_colour")));

      if (!obj->IsNull(_("passive_bar_colour")))
        linearmeter->SetPassiveBarColour(obj->GetPropertyAsColour(_("passive_bar_colour")));

	  if (!obj->IsNull(_("border_colour")))
        linearmeter->SetBorderColour(obj->GetPropertyAsColour(_("border_colour")));

      if (!obj->IsNull(_("text_limit_colour")))
        linearmeter->SetTxtLimitColour(obj->GetPropertyAsColour(_("text_limit_colour")));

      if (!obj->IsNull(_("text_value_colour")))
        linearmeter->SetTxtValueColour(obj->GetPropertyAsColour(_("text_value_colour")));

      if (!obj->IsNull(_("tags_colour")))
        linearmeter->SetTagsColour(obj->GetPropertyAsColour(_("tags_colour")));

	  if (!obj->IsNull(_("text_font")))
        linearmeter->SetTxtFont(obj->GetPropertyAsFont(_("text_font")));

      return linearmeter;
	}
};

class LinearRegulatorComponent : public ComponentBase
{
	wxObject* Create(IObject *obj, wxObject *parent)
	{
      kwxLinearRegulator *linearreg = new kwxLinearRegulator((wxWindow*)parent, -1, wxT(""),
  				   obj->GetPropertyAsPoint(_("pos")),
		           obj->GetPropertyAsSize(_("size")));

      linearreg->SetRangeVal(obj->GetPropertyAsInteger(_("range_min")),obj->GetPropertyAsInteger(_("range_max")));
      linearreg->SetValue(obj->GetPropertyAsInteger(_("value")));
	  linearreg->SetOrizDirection(obj->GetPropertyAsInteger(_("horiz_direction")));
	  linearreg->ShowCurrent(obj->GetPropertyAsInteger(_("show_current")));
	  linearreg->ShowLimits(obj->GetPropertyAsInteger(_("show_limits")));

	  if (!obj->IsNull(_("active_bar_colour")))
        linearreg->SetActiveBarColour(obj->GetPropertyAsColour(_("active_bar_colour")));

      if (!obj->IsNull(_("passive_bar_colour")))
        linearreg->SetPassiveBarColour(obj->GetPropertyAsColour(_("passive_bar_colour")));

	  if (!obj->IsNull(_("border_colour")))
        linearreg->SetBorderColour(obj->GetPropertyAsColour(_("border_colour")));

      if (!obj->IsNull(_("text_limit_colour")))
        linearreg->SetTxtLimitColour(obj->GetPropertyAsColour(_("text_limit_colour")));

      if (!obj->IsNull(_("text_value_colour")))
        linearreg->SetTxtValueColour(obj->GetPropertyAsColour(_("text_value_colour")));

      if (!obj->IsNull(_("tags_colour")))
        linearreg->SetTagsColour(obj->GetPropertyAsColour(_("tags_colour")));

	  if (!obj->IsNull(_("text_font")))
        linearreg->SetTxtFont(obj->GetPropertyAsFont(_("text_font")));

      return linearreg;
	}
};

///////////////////////////////////////////////////////////////////////////////

BEGIN_LIBRARY()

WINDOW_COMPONENT("kwxLCDDisplay",LCDDisplayComponent)
WINDOW_COMPONENT("kwxLCDClock",LCDClockComponent)
WINDOW_COMPONENT("kwxAngularMeter",AngularMeterComponent)
WINDOW_COMPONENT("kwxAngularRegulator",AngularRegulatorComponent)
WINDOW_COMPONENT("kwxLinearMeter",LinearMeterComponent)
WINDOW_COMPONENT("kwxLinearRegulator",LinearRegulatorComponent)


END_LIBRARY()

