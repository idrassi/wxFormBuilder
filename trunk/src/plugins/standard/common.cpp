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
// Written by José Antonio Hurtado - joseantonio.hurtado@hispalinux.es
//
///////////////////////////////////////////////////////////////////////////////
// Sustituir "label" por "bitmap" en wxStaticBitmap
// Juan Antonio Ortega (jortegalalmolda@gmail.com)

#include "../component.h"
#include "../plugin.h"
#include "wx/grid.h"
#include "wx/statline.h"

class ButtonComponent : public ComponentBase
{
  wxObject* Create(IObject *obj, wxObject *parent)
  {
    return new wxButton((wxWindow*)parent,-1,
      obj->GetPropertyAsString(_("label")),
      obj->GetPropertyAsPoint(_("pos")),
      obj->GetPropertyAsSize(_("size")),
      obj->GetPropertyAsInteger(_("style")));
  }
};


class TextCtrlComponent : public ComponentBase
{
  wxObject* Create(IObject *obj, wxObject *parent)
  {
    return new wxTextCtrl((wxWindow *)parent,-1,
      obj->GetPropertyAsString(_("value")),
      obj->GetPropertyAsPoint(_("pos")),
      obj->GetPropertyAsSize(_("size")),
      obj->GetPropertyAsInteger(_("style")));
  }
};

class StaticTextComponent : public ComponentBase
{
  wxObject* Create(IObject *obj, wxObject *parent)
  {
    return  new wxStaticText((wxWindow *)parent,-1,
      obj->GetPropertyAsString(_("label")),
      obj->GetPropertyAsPoint(_("pos")),
      obj->GetPropertyAsSize(_("size")),
      obj->GetPropertyAsInteger(_("style")));
  }
};

class PanelComponent : public ComponentBase
{
  wxObject* Create(IObject *obj, wxObject *parent)
  {
    return new wxPanel((wxWindow *)parent,-1,
      obj->GetPropertyAsPoint(_("pos")),
      obj->GetPropertyAsSize(_("size")),
      obj->GetPropertyAsInteger(_("style")));
  }
};

class GridComponent : public ComponentBase
{
  wxObject* Create(IObject *obj, wxObject *parent)
  {
    wxGrid *grid = new wxGrid((wxWindow *)parent,-1,
      obj->GetPropertyAsPoint(_("pos")),
      obj->GetPropertyAsSize(_("size")),
      obj->GetPropertyAsInteger(_("style")));
      
      grid->CreateGrid(
        obj->GetPropertyAsInteger(_("rows")),
        obj->GetPropertyAsInteger(_("cols")));
      
    return grid;
  }
};


class ComboBoxComponent : public ComponentBase
{
  wxObject* Create(IObject *obj, wxObject *parent)
  {
    return new wxComboBox((wxWindow *)parent,-1,
      obj->GetPropertyAsString(_("value")),
    obj->GetPropertyAsPoint(_("pos")),
    obj->GetPropertyAsSize(_("size")),
    0,
    NULL,
    obj->GetPropertyAsInteger(_("style")));
  }
};

class CheckBoxComponent : public ComponentBase
{
  wxObject* Create(IObject *obj, wxObject *parent)
  {
    return new wxCheckBox((wxWindow *)parent,-1,
      obj->GetPropertyAsString(_("label")),
      obj->GetPropertyAsPoint(_("pos")),
      obj->GetPropertyAsSize(_("size")),
      obj->GetPropertyAsInteger(_("style")));
  }
};

class StaticBitmapComponent : public ComponentBase
{
  wxObject* Create(IObject *obj, wxObject *parent)
  {
    return new wxStaticBitmap((wxWindow *)parent,-1,
      obj->GetPropertyAsBitmap(_("bitmap")),
      obj->GetPropertyAsPoint(_("pos")),
      obj->GetPropertyAsSize(_("size")),
      obj->GetPropertyAsInteger(_("style")));
  }
};	

class StaticLineComponent : public ComponentBase
{
  wxObject* Create(IObject *obj, wxObject *parent)
  {
    return new wxStaticLine((wxWindow *)parent,-1,
      obj->GetPropertyAsPoint(_("pos")),
      obj->GetPropertyAsSize(_("size")),
      obj->GetPropertyAsInteger(_("style")));
  }	
};
///////////////////////////////////////////////////////////////////////////////

BEGIN_LIBRARY()
  COMPONENT("wxButton",ButtonComponent)
  COMPONENT("wxTextCtrl",TextCtrlComponent)
  COMPONENT("wxStaticText",StaticTextComponent)
  COMPONENT("wxPanel",PanelComponent)
  COMPONENT("wxGrid",GridComponent)
  COMPONENT("wxComboBox", ComboBoxComponent)
  COMPONENT("wxCheckBox", CheckBoxComponent)
  COMPONENT("wxStaticBitmap", StaticBitmapComponent)
  COMPONENT("wxStaticLine", StaticLineComponent)

  // wxWindow style macros
  MACRO(wxSIMPLE_BORDER)
  MACRO(wxSUNKEN_BORDER)
  MACRO(wxDOUBLE_BORDER)
  MACRO(wxRAISED_BORDER)
  MACRO(wxTAB_TRAVERSAL)

  // wxButton
  MACRO(wxBU_LEFT)
  MACRO(wxBU_TOP)
  MACRO(wxBU_RIGHT)
  MACRO(wxBU_BOTTOM)
  MACRO(wxBU_EXACTFIT)
  
  // wxStaticText
  MACRO(wxALIGN_LEFT)
  MACRO(wxALIGN_CENTRE)
  MACRO(wxALIGN_RIGHT)
  MACRO(wxST_NO_AUTORESIZE)
  
  // wxTextCtrl
  MACRO(wxTE_MULTILINE)
  MACRO(wxTE_READONLY)
  MACRO(wxTE_RICH)  
  
  // wxStaticLine
  MACRO(wxLI_HORIZONTAL)
  MACRO(wxLI_VERTICAL)
END_LIBRARY()

