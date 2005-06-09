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
  wxObject* Create(IObject *obj, wxObject *parent)
  {
    wxPanel *panel = new wxPanel((wxWindow *)parent,-1);
    panel->SetBackgroundColour(wxColour(50,50,50));
    return panel;
  }
  
  TiXmlElement* ExportToXrc(IObject *obj)
  {
    ObjectToXrcFilter xrc(obj, _("wxFrame"), obj->GetPropertyAsString(_("name")));                       
    xrc.AddWindowProperties();
    xrc.AddProperty( _("title"), _("title"), XRC_TYPE_TEXT);
    return xrc.GetXrcObject();
  }

  TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
  {
    XrcToXfbFilter filter(xrcObj, _("Frame"));
    filter.AddWindowProperties();
    filter.AddProperty( _("title"), _("title"), XRC_TYPE_TEXT);
    return filter.GetXfbObject();
  }
};

class PanelFormComponent : public ComponentBase
{
 public:
  wxObject* Create(IObject *obj, wxObject *parent)
  {
    wxPanel *panel = new wxPanel((wxWindow *)parent,-1);
    return panel;
  }
  
  TiXmlElement* ExportToXrc(IObject *obj)
  {
    ObjectToXrcFilter xrc(obj, _("wxPanel"), obj->GetPropertyAsString(_("name")));
    xrc.AddWindowProperties();
    xrc.AddProperty(_("style"),_("style"),XRC_TYPE_BITLIST);
    return xrc.GetXrcObject();
  }
  
  TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
  {
    XrcToXfbFilter filter(xrcObj, _("Panel"));
    filter.AddWindowProperties();
    filter.AddProperty(_("style"),_("style"),XRC_TYPE_BITLIST);
    return filter.GetXfbObject();
  }
};

class DialogFormComponent : public ComponentBase
{
 public:
  wxObject* Create(IObject *obj, wxObject *parent)
  {
    wxPanel *panel = new wxPanel((wxWindow *)parent,-1);
    return panel;
  }
  
  TiXmlElement* ExportToXrc(IObject *obj)
  {
    ObjectToXrcFilter xrc(obj, _("wxDialog"), obj->GetPropertyAsString(_("name")));
    xrc.AddWindowProperties();
    xrc.AddProperty( _("title"), _("title"), XRC_TYPE_TEXT);
    return xrc.GetXrcObject();
  }
  
  TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
  {
    XrcToXfbFilter filter(xrcObj, _("Dialog"));
    filter.AddWindowProperties();
    filter.AddProperty( _("title"), _("title"), XRC_TYPE_TEXT);
    return filter.GetXfbObject();
  }
};

///////////////////////////////////////////////////////////////////////////////
// WIDGETS
///////////////////////////////////////////////////////////////////////////////

class ButtonComponent : public ComponentBase
{
 public: 
    
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
    ObjectToXrcFilter xrc(obj, _("wxButton"), obj->GetPropertyAsString(_("name")));
    xrc.AddWindowProperties();
    xrc.AddProperty(_("label"),_("label"),XRC_TYPE_TEXT);
    xrc.AddPropertyValue(_("default"),_("0"));
    return xrc.GetXrcObject();
  }
  
  TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
  {
    XrcToXfbFilter filter(xrcObj, _("wxButton"));
    filter.AddWindowProperties();
    filter.AddProperty(_("label"),_("label"),XRC_TYPE_TEXT);
    return filter.GetXfbObject();
  }
};


class TextCtrlComponent : public ComponentBase
{
 public:
     
  wxObject* Create(IObject *obj, wxObject *parent)
  {
    return new wxTextCtrl((wxWindow *)parent,-1,
      obj->GetPropertyAsString(_("value")),
      obj->GetPropertyAsPoint(_("pos")),
      obj->GetPropertyAsSize(_("size")),
      obj->GetPropertyAsInteger(_("style")));
  }
  
  TiXmlElement* ExportToXrc(IObject *obj)
  {
    ObjectToXrcFilter xrc(obj, _("wxTextCtrl"), obj->GetPropertyAsString(_("name")));
    xrc.AddWindowProperties();    
    xrc.AddProperty(_("style"),_("style"),XRC_TYPE_BITLIST);
    xrc.AddProperty(_("value"),_("value"),XRC_TYPE_TEXT);
    return xrc.GetXrcObject();
  }
  
  TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
  {
    XrcToXfbFilter filter(xrcObj, _("wxTextCtrl"));
    filter.AddWindowProperties();
    filter.AddProperty(_("style"),_("style"),XRC_TYPE_BITLIST);
    filter.AddProperty(_("value"),_("value"),XRC_TYPE_TEXT);
    return filter.GetXfbObject();
  }

};

class StaticTextComponent : public ComponentBase
{
 public:
     
  wxObject* Create(IObject *obj, wxObject *parent)
  {
    return  new wxStaticText((wxWindow *)parent,-1,
      obj->GetPropertyAsString(_("label")),
      obj->GetPropertyAsPoint(_("pos")),
      obj->GetPropertyAsSize(_("size")),
      obj->GetPropertyAsInteger(_("style")));
  }

  TiXmlElement* ExportToXrc(IObject *obj)
  {
    ObjectToXrcFilter xrc(obj, _("wxStaticText"), obj->GetPropertyAsString(_("name")));
    xrc.AddWindowProperties();    
    xrc.AddProperty(_("style"),_("style"),XRC_TYPE_BITLIST);
    xrc.AddProperty(_("label"),_("label"),XRC_TYPE_TEXT);
    return xrc.GetXrcObject();
  }
  
  TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
  {
    XrcToXfbFilter filter(xrcObj, _("wxStaticText"));
    filter.AddWindowProperties();
    filter.AddProperty(_("label"),_("label"),XRC_TYPE_TEXT);
    return filter.GetXfbObject();
  }
};

class PanelComponent : public ComponentBase
{
 public:
     
  wxObject* Create(IObject *obj, wxObject *parent)
  {
    return new wxPanel((wxWindow *)parent,-1,
      obj->GetPropertyAsPoint(_("pos")),
      obj->GetPropertyAsSize(_("size")),
      obj->GetPropertyAsInteger(_("style")));
  }
  
  TiXmlElement* ExportToXrc(IObject *obj)
  {
    ObjectToXrcFilter xrc(obj, _("wxPanel"), obj->GetPropertyAsString(_("name")));
    xrc.AddWindowProperties();    
    xrc.AddProperty(_("style"),_("style"),XRC_TYPE_BITLIST);
    return xrc.GetXrcObject();
  }

  TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
  {
    XrcToXfbFilter filter(xrcObj, _("wxPanel"));
    filter.AddWindowProperties();
    filter.AddProperty(_("style"),_("style"),XRC_TYPE_BITLIST);
    return filter.GetXfbObject();
  }

};

class GridComponent : public ComponentBase
{
 public:
     
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
 public: 
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
  
  TiXmlElement* ExportToXrc(IObject *obj)
  {
    ObjectToXrcFilter xrc(obj, _("wxComboBox"), obj->GetPropertyAsString(_("name")));
    xrc.AddWindowProperties();    
    xrc.AddProperty(_("style"),_("style"),XRC_TYPE_BITLIST);
    xrc.AddProperty(_("value"),_("value"),XRC_TYPE_TEXT);
    //xrc.AddProperty(_("value"),_("value"),XRC_TYPE_INTEGER);
    return xrc.GetXrcObject();
  }
  
  TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
  {
    XrcToXfbFilter filter(xrcObj, _("wxComboBox"));
    filter.AddWindowProperties();
    filter.AddProperty(_("style"),_("style"),XRC_TYPE_BITLIST);
    filter.AddProperty(_("value"),_("value"),XRC_TYPE_TEXT);
    return filter.GetXfbObject();
  }
};

class CheckBoxComponent : public ComponentBase
{
 public:  
  wxObject* Create(IObject *obj, wxObject *parent)
  {
    return new wxCheckBox((wxWindow *)parent,-1,
      obj->GetPropertyAsString(_("label")),
      obj->GetPropertyAsPoint(_("pos")),
      obj->GetPropertyAsSize(_("size")),
      obj->GetPropertyAsInteger(_("style")));
  }
  
  TiXmlElement* ExportToXrc(IObject *obj)
  {
    ObjectToXrcFilter xrc(obj, _("wxCheckBox"), obj->GetPropertyAsString(_("name")));
    xrc.AddWindowProperties();    
    xrc.AddProperty(_("label"),_("label"),XRC_TYPE_TEXT);
    return xrc.GetXrcObject();
  }
  
  TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
  {
    XrcToXfbFilter filter(xrcObj, _("wxCheckBox"));
    filter.AddWindowProperties();
    filter.AddProperty(_("label"),_("label"),XRC_TYPE_TEXT);
    return filter.GetXfbObject();
  }
};

class StaticBitmapComponent : public ComponentBase
{
 public: 
  wxObject* Create(IObject *obj, wxObject *parent)
  {
    return new wxStaticBitmap((wxWindow *)parent,-1,
      obj->GetPropertyAsBitmap(_("bitmap")),
      obj->GetPropertyAsPoint(_("pos")),
      obj->GetPropertyAsSize(_("size")),
      obj->GetPropertyAsInteger(_("style")));
  }
  
  TiXmlElement* ExportToXrc(IObject *obj)
  {
    ObjectToXrcFilter xrc(obj, _("wxStaticBitmap"), obj->GetPropertyAsString(_("name")));
    xrc.AddWindowProperties();    
    xrc.AddProperty(_("bitmap"),_("bitmap"),XRC_TYPE_TEXT);
    return xrc.GetXrcObject();
  }

  TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
  {
    XrcToXfbFilter filter(xrcObj, _("wxStaticBitmap"));
    filter.AddWindowProperties();
    filter.AddProperty(_("bitmap"),_("bitmap"),XRC_TYPE_TEXT);
    return filter.GetXfbObject();
  }
};	

class XpmStaticBitmapComponent : public StaticBitmapComponent
{
};

class StaticLineComponent : public ComponentBase
{
 public:
  wxObject* Create(IObject *obj, wxObject *parent)
  {
    return new wxStaticLine((wxWindow *)parent,-1,
      obj->GetPropertyAsPoint(_("pos")),
      obj->GetPropertyAsSize(_("size")),
      obj->GetPropertyAsInteger(_("style")));
  }	

  TiXmlElement* ExportToXrc(IObject *obj)
  {
    ObjectToXrcFilter xrc(obj, _("wxStaticLine"), obj->GetPropertyAsString(_("name")));
    xrc.AddWindowProperties();    
    xrc.AddProperty(_("style"),_("style"),XRC_TYPE_BITLIST);
    return xrc.GetXrcObject();
  }

  TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
  {
    XrcToXfbFilter filter(xrcObj, _("wxStaticLine"));
    filter.AddWindowProperties();
    filter.AddProperty(_("style"),_("style"),XRC_TYPE_BITLIST);
    return filter.GetXfbObject();
  }
};

class NotebookComponent : public ComponentBase
{
 public: 
  wxObject* Create(IObject *obj, wxObject *parent)
  {
    return new wxNotebook((wxWindow *)parent,-1,
      obj->GetPropertyAsPoint(_("pos")),
      obj->GetPropertyAsSize(_("size")),
      obj->GetPropertyAsInteger(_("style")));
  }

  TiXmlElement* ExportToXrc(IObject *obj)
  {
    ObjectToXrcFilter xrc(obj, _("wxNotebook"), obj->GetPropertyAsString(_("name")));
    xrc.AddWindowProperties();    
    xrc.AddProperty(_("style"),_("style"),XRC_TYPE_BITLIST);
    return xrc.GetXrcObject();
  }  
  
  TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
  {
    XrcToXfbFilter filter(xrcObj, _("wxNotebook"));
    filter.AddWindowProperties();
    filter.AddProperty(_("style"),_("style"),XRC_TYPE_BITLIST);
    return filter.GetXfbObject();
  }
  
  bool KeepEvtHandler() { return true; }
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

  TiXmlElement* ExportToXrc(IObject *obj)
  {
    ObjectToXrcFilter xrc(obj, _("notebookpage"));
    xrc.AddProperty(_("label"),_("label"),XRC_TYPE_TEXT);
    xrc.AddProperty(_("selected"),_("selected"),XRC_TYPE_BOOL);
    return xrc.GetXrcObject();
  }
  
  TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
  {
    XrcToXfbFilter filter(xrcObj, _("notebookpage"));
    filter.AddWindowProperties();
    filter.AddProperty(_("selected"),_("selected"),XRC_TYPE_BOOL);
    filter.AddProperty(_("label"),_("label"),XRC_TYPE_TEXT);
    return filter.GetXfbObject();
  }
};

class ListCtrlComponent : public ComponentBase
{
 public: 
  wxObject* Create(IObject *obj, wxObject *parent)
  {
    return new wxListCtrl((wxWindow*)parent, -1,
      obj->GetPropertyAsPoint(_("pos")),
      obj->GetPropertyAsSize(_("size")),
      obj->GetPropertyAsInteger(_("style")));
  }

  TiXmlElement* ExportToXrc(IObject *obj)
  {
    ObjectToXrcFilter xrc(obj, _("wxListCtrl"), obj->GetPropertyAsString(_("name")));
    xrc.AddWindowProperties();    
    xrc.AddProperty(_("style"),_("style"),XRC_TYPE_BITLIST);
    return xrc.GetXrcObject();
  } 

  TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
  {
    XrcToXfbFilter filter(xrcObj, _("wxListCtrl"));
    filter.AddWindowProperties();
    filter.AddProperty(_("style"),_("style"),XRC_TYPE_BITLIST);
    return filter.GetXfbObject();
  }
};

class StatusBarComponent : public ComponentBase
{
 public: 
  wxObject* Create(IObject *obj, wxObject *parent)
  {
    wxStatusBar *sb = new wxStatusBar((wxWindow*)parent, -1,
      obj->GetPropertyAsInteger(_("style")));
    sb->SetFieldsCount(obj->GetPropertyAsInteger(_("fields")));
    return sb;
  }

  TiXmlElement* ExportToXrc(IObject *obj)
  {
    ObjectToXrcFilter xrc(obj, _("wxStatusBar"), obj->GetPropertyAsString(_("name")));
    xrc.AddWindowProperties();    
    xrc.AddProperty(_("style"),_("style"),XRC_TYPE_BITLIST);
    xrc.AddProperty(_("fields"),_("fields"),XRC_TYPE_INTEGER);
    return xrc.GetXrcObject();
  } 
  
  TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
  {
    XrcToXfbFilter filter(xrcObj, _("wxStatusBar"));
    filter.AddWindowProperties();
    filter.AddProperty(_("style"),_("style"),XRC_TYPE_BITLIST);
    filter.AddProperty(_("fields"),_("fields"),XRC_TYPE_INTEGER);
    return filter.GetXfbObject();
  }
};

class MenuBarComponent : public ComponentBase
{
 public:

  TiXmlElement* ExportToXrc(IObject *obj)
  {
    ObjectToXrcFilter xrc(obj, _("wxMenuBar"), obj->GetPropertyAsString(_("name")));
    xrc.AddProperty(_("label"),_("label"),XRC_TYPE_TEXT);
    return xrc.GetXrcObject();
  }
  
  TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
  {
    XrcToXfbFilter filter(xrcObj, _("wxMenuBar"));
    filter.AddProperty(_("label"),_("label"),XRC_TYPE_TEXT);
    return filter.GetXfbObject();
  }
};

class MenuComponent : public ComponentBase
{
 public:

  TiXmlElement* ExportToXrc(IObject *obj)
  {
    ObjectToXrcFilter xrc(obj, _("wxMenu"), obj->GetPropertyAsString(_("name")));
    xrc.AddProperty(_("label"),_("label"),XRC_TYPE_TEXT);
    return xrc.GetXrcObject();
  }
  
  TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
  {
    XrcToXfbFilter filter(xrcObj, _("wxMenu"));
    filter.AddProperty(_("label"),_("label"),XRC_TYPE_TEXT);
    return filter.GetXfbObject();
  }
};

class MenuItemComponent : public ComponentBase
{
 public:

  TiXmlElement* ExportToXrc(IObject *obj)
  {
    ObjectToXrcFilter xrc(obj, _("wxMenuItem"), obj->GetPropertyAsString(_("name")));
    xrc.AddProperty(_("label"),_("label"),XRC_TYPE_TEXT);
    xrc.AddProperty(_("help"),_("help"),XRC_TYPE_TEXT);
    xrc.AddProperty(_("bitmap"),_("bitmap"),XRC_TYPE_TEXT);
    return xrc.GetXrcObject();
  }
  
  TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
  {
    XrcToXfbFilter filter(xrcObj, _("wxMenuItem"));
    filter.AddProperty(_("label"),_("label"),XRC_TYPE_TEXT);
    filter.AddProperty(_("help"),_("help"),XRC_TYPE_TEXT);
    filter.AddProperty(_("bitmap"),_("bitmap"),XRC_TYPE_TEXT);
    return filter.GetXfbObject();
  }
};

class SeparatorComponent : public ComponentBase
{
 public:

  TiXmlElement* ExportToXrc(IObject *obj)
  {
    ObjectToXrcFilter xrc(obj, _("separator"));
    return xrc.GetXrcObject();
  }

  TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
  {
    XrcToXfbFilter filter(xrcObj, _("separator"));
    return filter.GetXfbObject();
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
  COMPONENT("wxXpmStaticBitmap", XpmStaticBitmapComponent)
  COMPONENT("wxStaticLine", StaticLineComponent)
  COMPONENT("wxNotebook", NotebookComponent)
  COMPONENT("wxMenuBar", MenuBarComponent)
  COMPONENT("wxMenu", MenuComponent)
  COMPONENT("submenu", MenuComponent)
  COMPONENT("wxMenuItem", MenuItemComponent)
  COMPONENT("separator", SeparatorComponent)
  COMPONENT("wxListCtrl", ListCtrlComponent)
  COMPONENT("wxStatusBar", StatusBarComponent)

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
  
  // wxStatusBar
  MACRO(wxST_SIZEGRIP)
  
END_LIBRARY()

