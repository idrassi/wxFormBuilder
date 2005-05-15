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

#include "plugins/component.h"
#include "plugins/plugin.h"
#include "utils/xrcconv.h"

#include "wx/grid.h"
#include "wx/statline.h"
#include "wx/notebook.h"
#include "wx/listctrl.h"

///////////////////////////////////////////////////////////////////////////////
// FORMS
///////////////////////////////////////////////////////////////////////////////

// TO-DO: El componente de tipo "Form" se dibujará en el designer, para así
//        por ejemplo, dibujar un panel oscuro para el caso de wxFrame
class FrameFormComponent : public ComponentBase
{
 public:
  TiXmlElement* ExportToXrc(IObject *obj)
  {
    ObjectToXrcFilter xrc(obj, _("wxFrame"), obj->GetPropertyAsString(_("name")));                       
    xrc.AddProperty( _("title"), _("title"), XRC_TYPE_TEXT);
    return xrc.GetXrcObject();
  } 
};

class PanelFormComponent : public ComponentBase
{
};

class DialogFormComponent : public ComponentBase
{
 public:
  TiXmlElement* ExportToXrc(IObject *obj)
  {
    ObjectToXrcFilter xrc(obj, _("wxDialog"), obj->GetPropertyAsString(_("name")));
    xrc.AddProperty( _("title"), _("title"), XRC_TYPE_TEXT);
    return xrc.GetXrcObject();
  }
};

///////////////////////////////////////////////////////////////////////////////
// WIDGETS
///////////////////////////////////////////////////////////////////////////////

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
  
  TiXmlElement* ExportToXrc(IObject *obj)
  {
    ObjectToXrcFilter xrc(obj,
                          _("wxButton"),
                          obj->GetPropertyAsString(_("name")));
    xrc.AddProperty(_("label"),_("label"),XRC_TYPE_TEXT);
    xrc.AddPropertyValue(_("default"),_("0"));
    return xrc.GetXrcObject();
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

class NotebookComponent : public ComponentBase
{
  wxObject* Create(IObject *obj, wxObject *parent)
  {
    return new wxNotebook((wxWindow *)parent,-1,
      obj->GetPropertyAsPoint(_("pos")),
      obj->GetPropertyAsSize(_("size")),
      obj->GetPropertyAsInteger(_("style")));
  }	
};

class NotebookPageComponent : public ComponentBase
{
 public:
  void OnCreated(IObjectView *objview, wxWindow *wxparent, IObjectView *parent,
                 IObjectView *first_child)
  {
    IObject *obj = objview->Object();
    wxNotebook *nb = (wxNotebook *)parent->Window();
    wxWindow *page = first_child->Window();

    int selection = nb->GetSelection();
    nb->AddPage(page,obj->GetPropertyAsString(_("label")));

    if (obj->GetPropertyAsString(_("select"))==wxT("0") && selection >= 0)
      nb->SetSelection(selection);
    else
      nb->SetSelection(nb->GetPageCount()-1);
  }
};

class MenuBarComponent : public ComponentBase
{
  wxObject* Create(IObject *obj, wxObject *parent)
  {
    return NULL;
  }	
};

class MenuComponent : public ComponentBase
{
  wxObject* Create(IObject *obj, wxObject *parent)
  {
    return NULL;
  }	
};

class MenuItemComponent : public ComponentBase
{
  wxObject* Create(IObject *obj, wxObject *parent)
  {
    return NULL;
  }	
};

class ListCtrlComponent : public ComponentBase
{
  wxObject* Create(IObject *obj, wxObject *parent)
  {
    return new wxListCtrl((wxWindow*)parent, -1,
      obj->GetPropertyAsPoint(_("pos")),
      obj->GetPropertyAsSize(_("size")),
      obj->GetPropertyAsInteger(_("style")));
  }
};

///////////////////////////////////////////////////////////////////////////////

BEGIN_LIBRARY()
  COMPONENT("Frame",FrameFormComponent)
  COMPONENT("Panel",PanelFormComponent)
  COMPONENT("Dialog",DialogFormComponent)
    
  COMPONENT("notebookpage",NotebookPageComponent)
  COMPONENT("wxButton",ButtonComponent)
  COMPONENT("wxTextCtrl",TextCtrlComponent)
  COMPONENT("wxStaticText",StaticTextComponent)
  COMPONENT("wxPanel",PanelComponent)
  COMPONENT("wxGrid",GridComponent)
  COMPONENT("wxComboBox", ComboBoxComponent)
  COMPONENT("wxCheckBox", CheckBoxComponent)
  COMPONENT("wxStaticBitmap", StaticBitmapComponent)
  COMPONENT("wxStaticLine", StaticLineComponent)
  COMPONENT("wxNotebook", NotebookComponent)
  COMPONENT("wxMenuBar", MenuBarComponent)
  COMPONENT("wxMenu", MenuComponent)
  COMPONENT("wxMenuItem", MenuItemComponent)
  COMPONENT("wxListCtrl", ListCtrlComponent)

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
  
  // wxNotebook
  MACRO(wxNB_TOP)
  MACRO(wxNB_LEFT)
  MACRO(wxNB_RIGHT)
  MACRO(wxNB_BOTTOM)
  MACRO(wxNB_FIXEDWIDTH)
  MACRO(wxNB_MULTILINE)
  MACRO(wxNB_NOPAGETHEME)
  MACRO(wxNB_FLAT)
  
  // wxListCtrl
  MACRO(wxLC_LIST)
  MACRO(wxLC_REPORT)
  MACRO(wxLC_VIRTUAL)
  MACRO(wxLC_ICON)
  MACRO(wxLC_SMALL_ICON)
  MACRO(wxLC_ALIGN_TOP)
  MACRO(wxLC_ALIGN_LEFT)
  MACRO(wxLC_AUTOARRANGE)
  MACRO(wxLC_EDIT_LABELS)
  MACRO(wxLC_NO_HEADER)
  MACRO(wxLC_SINGLE_SEL)
  MACRO(wxLC_SORT_ASCENDING)
  MACRO(wxLC_SORT_DESCENDING)
  MACRO(wxLC_HRULES)
  MACRO(wxLC_VRULES)
  
END_LIBRARY()

