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

#include "plugins/component.h"
#include "plugins/plugin.h"
#include "utils/xrcconv.h"
#include "icons/unknown.xpm"

#include "wx/grid.h"
#include "wx/statline.h"
#include "wx/notebook.h"
#include "wx/listctrl.h"
#include "wx/radiobox.h"


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
    wxComboBox *combo = new wxComboBox((wxWindow *)parent,-1,
      obj->GetPropertyAsString(_("value")),
      obj->GetPropertyAsPoint(_("pos")),
      obj->GetPropertyAsSize(_("size")),
      0,
      NULL,
      obj->GetPropertyAsInteger(_("style")));
    
    // choices
    wxArrayString choices = obj->GetPropertyAsArrayString(_("choices"));
    for (unsigned int i=0; i<choices.Count(); i++)
      combo->Append(choices[i]);
      
    return combo;
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

class ListBoxComponent : public ComponentBase
{
  public:
  wxObject* Create(IObject *obj, wxObject *parent)
  {
    wxListBox *listbox = new wxListBox((wxWindow*)parent, -1,
      obj->GetPropertyAsPoint(_("pos")),
      obj->GetPropertyAsSize(_("size")),
      0,
      NULL,
      obj->GetPropertyAsInteger(_("style")));

    // choices
    wxArrayString choices = obj->GetPropertyAsArrayString(_("choices"));
    for (unsigned int i=0; i<choices.Count(); i++)
      listbox->Append(choices[i]);
      
    return listbox;
  }
};

class RadioBoxComponent : public ComponentBase
{
  public:
  wxObject* Create(IObject *obj, wxObject *parent)
  {
    wxArrayString choices = obj->GetPropertyAsArrayString(_("choices"));
    wxString *strings = new wxString[choices.Count()];
    for (unsigned int i=0; i < choices.Count(); i++)
      strings[i] = choices[i];
      
    int majorDim = obj->GetPropertyAsInteger(_("majorDimension"));
    if (majorDim < 1)
    {
      wxLogWarning(wxT("Property majorDimension of wxRadioBox set to \'1\'"));
      majorDim = 1;
    }
    
    wxRadioBox *radiobox = new wxRadioBox((wxWindow*)parent, -1,
      obj->GetPropertyAsString(_("label")),
      obj->GetPropertyAsPoint(_("pos")),
      obj->GetPropertyAsSize(_("size")),
      choices.Count(),
      strings,
      majorDim,
      obj->GetPropertyAsInteger(_("style")));
 
    delete []strings;
         
    return radiobox;
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
    //xrc.AddProperty(_("label"),_("label"),XRC_TYPE_TEXT);
    wxString shortcut = obj->GetPropertyAsString(_("shortcut"));
    wxString label;
    if (shortcut.IsEmpty())
      label = obj->GetPropertyAsString(_("label"));
    else
      label = obj->GetPropertyAsString(_("label")) + _T("\\t") + shortcut;
      
    xrc.AddPropertyValue(_("label"), label);
    xrc.AddProperty(_("help"),_("help"),XRC_TYPE_TEXT);
    xrc.AddProperty(_("bitmap"),_("bitmap"),XRC_TYPE_TEXT);
    
    int kind = obj->GetPropertyAsInteger(_("kind"));
    
    if (obj->GetPropertyAsInteger(_("checked")) && (kind == wxITEM_RADIO || kind == wxITEM_CHECK))
      xrc.AddProperty(_("checked"), _("checked"), XRC_TYPE_BOOL);
    
    if (obj->GetPropertyAsInteger(_("enabled")) == 0)
      xrc.AddProperty(_("enabled"), _("enabled"), XRC_TYPE_BOOL);
    
    switch (kind)
    {
      case wxITEM_CHECK: xrc.AddPropertyValue(_("checkable"), _("1")); break;
      case wxITEM_RADIO: xrc.AddPropertyValue(_("radio"), _("1")); break;
    }
    
    return xrc.GetXrcObject();
  }
  
  TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
  {
    XrcToXfbFilter filter(xrcObj, _("wxMenuItem"));
    //filter.AddProperty(_("label"),_("label"),XRC_TYPE_TEXT);
    TiXmlElement *labelElement = xrcObj->FirstChildElement("label");
    
    wxString label, shortcut;
    if (labelElement)
    {
      TiXmlNode *labelNode;
      labelNode = labelElement->FirstChild();
      if (labelNode && labelNode->ToText())
      {
        label = wxString(labelNode->ToText()->Value(),wxConvUTF8);
        int pos = label.Find(_T("\\t"));
        if (pos >= 0)
        {
          shortcut = label.Mid(pos + 2);
          label = label.Left(pos);
        }
      }
    }
    
    filter.AddPropertyValue(_("label"), label);
    filter.AddPropertyValue(_("shortcut"), shortcut);
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

class ToolBarComponent : public ComponentBase
{
 public: 
  wxObject* Create(IObject *obj, wxObject *parent)
  {
    wxToolBar *tb = new wxToolBar((wxWindow*)parent, -1,
      obj->GetPropertyAsPoint(_("pos")),
      obj->GetPropertyAsSize(_("size")),
      obj->GetPropertyAsInteger(_("style")) | wxTB_NOALIGN | wxTB_NODIVIDER | wxNO_BORDER);
    
    if (!obj->IsNull(_("bitmapsize")))
      tb->SetToolBitmapSize(obj->GetPropertyAsSize(_("bitmapsize")));
    if (!obj->IsNull(_("marings")))
    {
      //tb->SetMargins(obj->GetPropertyAsSize(_("margins")));
      wxSize margins(obj->GetPropertyAsSize(_("margins")));
      tb->SetMargins(margins.GetWidth(), margins.GetHeight());
    }
    if (!obj->IsNull(_("packing")))
      tb->SetToolPacking(obj->GetPropertyAsInteger(_("packing")));
    if (!obj->IsNull(_("separation")))
      tb->SetToolSeparation(obj->GetPropertyAsInteger(_("separation")));
      
    return tb;
  }
  
  void OnCreated(IObjectView *objview, wxWindow *wxparent, IObjectView *parent,
                 IObjectView *first_child)
  {
    wxToolBar *tb = (wxToolBar*) objview->Window();
    wxASSERT(tb->IsKindOf(CLASSINFO(wxToolBar)));
    tb->Realize();
  }

  TiXmlElement* ExportToXrc(IObject *obj)
  {
    ObjectToXrcFilter xrc(obj, _("wxToolBar"), obj->GetPropertyAsString(_("name")));
    xrc.AddWindowProperties();    
    xrc.AddProperty(_("bitmapsize"), _("bitmapsize"), XRC_TYPE_SIZE);
    xrc.AddProperty(_("margins"), _("margins"), XRC_TYPE_SIZE);
    xrc.AddProperty(_("packing"), _("packing"), XRC_TYPE_INTEGER);
    xrc.AddProperty(_("separation"), _("separation"), XRC_TYPE_INTEGER);
    xrc.AddProperty(_("style"), _("style"), XRC_TYPE_BITLIST);
    return xrc.GetXrcObject();
  } 
  
  TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
  {
    XrcToXfbFilter filter(xrcObj, _("wxToolBar"));
    filter.AddWindowProperties();
    filter.AddProperty(_("bitmapsize"), _("bitmapsize"), XRC_TYPE_SIZE);
    filter.AddProperty(_("margins"), _("margins"), XRC_TYPE_SIZE);
    filter.AddProperty(_("packing"), _("packing"), XRC_TYPE_INTEGER);
    filter.AddProperty(_("separation"), _("separation"), XRC_TYPE_INTEGER);
    filter.AddProperty(_("style"), _("style"), XRC_TYPE_BITLIST);
    return filter.GetXfbObject();
  }
};  

class ToolComponent : public ComponentBase
{
 public: 
  wxObject* Create(IObject *obj, wxObject *parent)
  {
    wxToolBar *tb = (wxToolBar*) parent;
    tb->AddTool(wxID_HIGHEST + 200,
      obj->GetPropertyAsString(_("label")),
      obj->GetPropertyAsBitmap(_("bitmap")),
      obj->GetPropertyAsString(_("help"))); 

    return NULL;
  }

  TiXmlElement* ExportToXrc(IObject *obj)
  {
    ObjectToXrcFilter xrc(obj, _("tool"), obj->GetPropertyAsString(_("name")));
    xrc.AddWindowProperties();    
    xrc.AddProperty(_("label"), _("label"), XRC_TYPE_TEXT);
    xrc.AddProperty(_("bitmap"), _("bitmap"), XRC_TYPE_TEXT);
    return xrc.GetXrcObject();
  } 
  
  TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
  {
    XrcToXfbFilter filter(xrcObj, _("tool"));
    filter.AddWindowProperties();
    filter.AddProperty(_("label"), _("label"), XRC_TYPE_TEXT);
    filter.AddProperty(_("bitmap"), _("bitmap"), XRC_TYPE_TEXT);
    return filter.GetXfbObject();
  }
};   

///////////////////////////////////////////////////////////////////////////////

BEGIN_LIBRARY()

  // Los forms no son considerados como windows !
  ABSTRACT_COMPONENT("Frame",FrameFormComponent)
  ABSTRACT_COMPONENT("Panel",PanelFormComponent)
  ABSTRACT_COMPONENT("Dialog",DialogFormComponent)
    
  WINDOW_COMPONENT("notebookpage",NotebookPageComponent)
  WINDOW_COMPONENT("wxButton",ButtonComponent)
  WINDOW_COMPONENT("wxTextCtrl",TextCtrlComponent)
  WINDOW_COMPONENT("wxStaticText",StaticTextComponent)
  WINDOW_COMPONENT("wxPanel",PanelComponent)
  WINDOW_COMPONENT("wxGrid",GridComponent)
  WINDOW_COMPONENT("wxComboBox", ComboBoxComponent)
  WINDOW_COMPONENT("wxListBox", ListBoxComponent)
  WINDOW_COMPONENT("wxRadioBox", RadioBoxComponent)
  WINDOW_COMPONENT("wxCheckBox", CheckBoxComponent)
  WINDOW_COMPONENT("wxStaticBitmap", StaticBitmapComponent)
  WINDOW_COMPONENT("wxXpmStaticBitmap", XpmStaticBitmapComponent)
  WINDOW_COMPONENT("wxStaticLine", StaticLineComponent)
  WINDOW_COMPONENT("wxNotebook", NotebookComponent)
  WINDOW_COMPONENT("wxMenuBar", MenuBarComponent)
  WINDOW_COMPONENT("wxMenu", MenuComponent)
  WINDOW_COMPONENT("submenu", MenuComponent)
  WINDOW_COMPONENT("wxMenuItem", MenuItemComponent)
  WINDOW_COMPONENT("separator", SeparatorComponent)
  WINDOW_COMPONENT("wxListCtrl", ListCtrlComponent)
  WINDOW_COMPONENT("wxStatusBar", StatusBarComponent)
  WINDOW_COMPONENT("wxToolBar", ToolBarComponent)
  WINDOW_COMPONENT("tool", ToolComponent)

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
  
  // wxListBox
  MACRO(wxLB_SINGLE)
  MACRO(wxLB_MULTIPLE)
  MACRO(wxLB_EXTENDED)
  MACRO(wxLB_HSCROLL)
  MACRO(wxLB_ALWAYS_SB)
  MACRO(wxLB_NEEDED_SB)
  MACRO(wxLB_SORT)
  
  // wxRadioBox
  MACRO(wxRA_SPECIFY_ROWS)
  MACRO(wxRA_SPECIFY_COLS)
  MACRO(wxRA_USE_CHECKBOX)
  
  // wxStatusBar
  MACRO(wxST_SIZEGRIP)
  
  // wxMenuItem
  MACRO(wxITEM_NORMAL)
  MACRO(wxITEM_CHECK)
  MACRO(wxITEM_RADIO)
  
  // wxToolBar
  MACRO(wxTB_FLAT)  
  MACRO(wxTB_DOCKABLE)
  MACRO(wxTB_HORIZONTAL)
  MACRO(wxTB_VERTICAL)
  MACRO(wxTB_TEXT)
  MACRO(wxTB_NOICONS)
  MACRO(wxTB_NODIVIDER)
  MACRO(wxTB_NOALIGN)
  MACRO(wxTB_HORZ_LAYOUT)
  MACRO(wxTB_HORZ_TEXT) 
  
END_LIBRARY()

