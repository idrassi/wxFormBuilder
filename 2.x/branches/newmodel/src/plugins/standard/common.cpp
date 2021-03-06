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

#include "wx/grid.h"
#include "wx/statline.h"
#include "wx/listctrl.h"
#include "wx/radiobox.h"
#include "wx/bmpbuttn.h"



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
//		xrc.AddWindowProperties();
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
		//xrc.AddProperty(_("style"),_("style"),XRC_TYPE_BITLIST);
		return xrc.GetXrcObject();
	}

	TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
	{
		XrcToXfbFilter filter(xrcObj, _("Panel"));
		filter.AddWindowProperties();
		//filter.AddProperty(_("style"),_("style"),XRC_TYPE_BITLIST);
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
			obj->GetPropertyAsInteger(_("style")) | obj->GetPropertyAsInteger(_("window_style")));
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

class BitmapButtonComponent : public ComponentBase
{
public:

	wxObject* Create(IObject *obj, wxObject *parent)
	{
		return new wxBitmapButton((wxWindow*)parent,-1,
			obj->GetPropertyAsBitmap(_("bitmap")),
			obj->GetPropertyAsPoint(_("pos")),
			obj->GetPropertyAsSize(_("size")),
			obj->GetPropertyAsInteger(_("style")) | obj->GetPropertyAsInteger(_("window_style")));
	}

	TiXmlElement* ExportToXrc(IObject *obj)
	{
		ObjectToXrcFilter xrc(obj, _("wxBitmapButton"), obj->GetPropertyAsString(_("name")));
		xrc.AddWindowProperties();
    xrc.AddProperty(_("bitmap"),_("bitmap"),XRC_TYPE_BITMAP);
		xrc.AddPropertyValue(_("default"),_("0"));
		return xrc.GetXrcObject();
	}

	TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
	{
		XrcToXfbFilter filter(xrcObj, _("wxBitmapButton"));
		filter.AddWindowProperties();
    filter.AddProperty(_("bitmap"),_("bitmap"),XRC_TYPE_BITMAP);
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
			obj->GetPropertyAsInteger(_("style")) | obj->GetPropertyAsInteger(_("window_style")));
	}

	TiXmlElement* ExportToXrc(IObject *obj)
	{
		ObjectToXrcFilter xrc(obj, _("wxTextCtrl"), obj->GetPropertyAsString(_("name")));
		xrc.AddWindowProperties();
		//xrc.AddProperty(_("style"),_("style"),XRC_TYPE_BITLIST);
		xrc.AddProperty(_("value"),_("value"),XRC_TYPE_TEXT);
		return xrc.GetXrcObject();
	}

	TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
	{
		XrcToXfbFilter filter(xrcObj, _("wxTextCtrl"));
		filter.AddWindowProperties();
		//filter.AddProperty(_("style"),_("style"),XRC_TYPE_BITLIST);
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
			obj->GetPropertyAsInteger(_("style")) | obj->GetPropertyAsInteger(_("window_style")));
	}

	TiXmlElement* ExportToXrc(IObject *obj)
	{
		wxString name = obj->GetPropertyAsString(_("name"));
		ObjectToXrcFilter xrc(obj, _("wxStaticText"), name);
		xrc.AddWindowProperties();
		//xrc.AddProperty(_("style"),_("style"),XRC_TYPE_BITLIST);
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
		wxPanel* panel = new wxPanel((wxWindow *)parent,-1,
			obj->GetPropertyAsPoint(_("pos")),
			obj->GetPropertyAsSize(_("size")),
			obj->GetPropertyAsInteger(_("style")) | obj->GetPropertyAsInteger(_("window_style")));
		return panel;
	}

	TiXmlElement* ExportToXrc(IObject *obj)
	{
		ObjectToXrcFilter xrc(obj, _("wxPanel"), obj->GetPropertyAsString(_("name")));
		xrc.AddWindowProperties();
		//xrc.AddProperty(_("style"),_("style"),XRC_TYPE_BITLIST);
		return xrc.GetXrcObject();
	}

	TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
	{
		XrcToXfbFilter filter(xrcObj, _("wxPanel"));
		filter.AddWindowProperties();
		//filter.AddProperty(_("style"),_("style"),XRC_TYPE_BITLIST);
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
			obj->GetPropertyAsInteger(_("window_style")));

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
			obj->GetPropertyAsInteger(_("style")) | obj->GetPropertyAsInteger(_("window_style")));

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
		//xrc.AddProperty(_("style"),_("style"),XRC_TYPE_BITLIST);
		xrc.AddProperty(_("value"),_("value"),XRC_TYPE_TEXT);
		xrc.AddProperty(_("choices"),_("content"),XRC_TYPE_STRINGLIST);
		return xrc.GetXrcObject();
	}

	TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
	{
		XrcToXfbFilter filter(xrcObj, _("wxComboBox"));
		filter.AddWindowProperties();
		//filter.AddProperty(_("style"),_("style"),XRC_TYPE_BITLIST);
		filter.AddProperty(_("value"),_("value"),XRC_TYPE_TEXT);
		filter.AddProperty(_("content"),_("choices"),XRC_TYPE_STRINGLIST);
		return filter.GetXfbObject();
	}
};

class CheckBoxComponent : public ComponentBase
{
public:
	wxObject* Create(IObject *obj, wxObject *parent)
	{
		wxCheckBox *res = new wxCheckBox((wxWindow *)parent,-1,
			obj->GetPropertyAsString(_("label")),
			obj->GetPropertyAsPoint(_("pos")),
			obj->GetPropertyAsSize(_("size")),
			obj->GetPropertyAsInteger(_("window_style")) | obj->GetPropertyAsInteger(_T("style")));
        res->SetValue(obj->GetPropertyAsInteger(_T("checked")) != 0);
        return res;
	}

	TiXmlElement* ExportToXrc(IObject *obj)
	{
		ObjectToXrcFilter xrc(obj, _("wxCheckBox"), obj->GetPropertyAsString(_("name")));
		xrc.AddWindowProperties();
		xrc.AddProperty(_("label"),_("label"),XRC_TYPE_TEXT);
		xrc.AddProperty(_("checked"),_("checked"),XRC_TYPE_BOOL);
		return xrc.GetXrcObject();
	}

	TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
	{
		XrcToXfbFilter filter(xrcObj, _("wxCheckBox"));
		filter.AddWindowProperties();
		filter.AddProperty(_("label"),_("label"),XRC_TYPE_TEXT);
		filter.AddProperty(_("checked"),_("checked"),XRC_TYPE_BOOL);
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
			obj->GetPropertyAsInteger(_("window_style")));
	}

	TiXmlElement* ExportToXrc(IObject *obj)
	{
		ObjectToXrcFilter xrc(obj, _("wxStaticBitmap"), obj->GetPropertyAsString(_("name")));
		xrc.AddWindowProperties();
    xrc.AddProperty(_("bitmap"),_("bitmap"),XRC_TYPE_BITMAP);
		return xrc.GetXrcObject();
	}

	TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
	{
		XrcToXfbFilter filter(xrcObj, _("wxStaticBitmap"));
		filter.AddWindowProperties();
    filter.AddProperty(_("bitmap"),_("bitmap"),XRC_TYPE_BITMAP);
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
			obj->GetPropertyAsInteger(_("style")) | obj->GetPropertyAsInteger(_("window_style")));
	}

	TiXmlElement* ExportToXrc(IObject *obj)
	{
		ObjectToXrcFilter xrc(obj, _("wxStaticLine"), obj->GetPropertyAsString(_("name")));
		xrc.AddWindowProperties();
		//xrc.AddProperty(_("style"),_("style"),XRC_TYPE_BITLIST);
		return xrc.GetXrcObject();
	}

	TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
	{
		XrcToXfbFilter filter(xrcObj, _("wxStaticLine"));
		filter.AddWindowProperties();
		//filter.AddProperty(_("style"),_("style"),XRC_TYPE_BITLIST);
		return filter.GetXfbObject();
	}
};

class ListCtrlComponent : public ComponentBase
{
public:
	wxObject* Create(IObject *obj, wxObject *parent)
	{
		wxListCtrl *lc = new wxListCtrl((wxWindow*)parent, -1,
			obj->GetPropertyAsPoint(_("pos")),
			obj->GetPropertyAsSize(_("size")),
			obj->GetPropertyAsInteger(_("style")) | obj->GetPropertyAsInteger(_("window_style")));


		// Rellenamos
		int i,j;
		wxString buf;
		for (i=0;i<4;i++)
		{
			buf.Printf(wxT("Label %d"),i);
			wxListItem itemCol;
			itemCol.SetText(buf);
			itemCol.SetAlign(wxLIST_FORMAT_LEFT);
			lc->InsertColumn(i, itemCol);
		}

		for (j=0;j<10;j++)
		{
			long temp;
			buf.Printf(wxT("Cell (0,%d)"),j);
			temp = lc->InsertItem(j,buf);
			for (i=1;i<4;i++)
			{
				buf.Printf(wxT("Cell (%d,%d)"),i,j);
				lc->SetItem(temp,i,buf);
			}
		}

		return lc;
	}

	TiXmlElement* ExportToXrc(IObject *obj)
	{
		ObjectToXrcFilter xrc(obj, _("wxListCtrl"), obj->GetPropertyAsString(_("name")));
		xrc.AddWindowProperties();
		//xrc.AddProperty(_("style"),_("style"),XRC_TYPE_BITLIST);
		return xrc.GetXrcObject();
	}

	TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
	{
		XrcToXfbFilter filter(xrcObj, _("wxListCtrl"));
		filter.AddWindowProperties();
		//filter.AddProperty(_("style"),_("style"),XRC_TYPE_BITLIST);
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
			obj->GetPropertyAsInteger(_("style")) | obj->GetPropertyAsInteger(_("window_style")));

		// choices
		wxArrayString choices = obj->GetPropertyAsArrayString(_("choices"));
		for (unsigned int i=0; i<choices.Count(); i++)
			listbox->Append(choices[i]);

		return listbox;
	}

	TiXmlElement* ExportToXrc(IObject *obj)
	{
		ObjectToXrcFilter xrc(obj, _("wxListBox"), obj->GetPropertyAsString(_("name")));
		xrc.AddWindowProperties();
		//xrc.AddProperty(_("style"), _("style"), XRC_TYPE_BITLIST);
		xrc.AddProperty(_("choices"), _("content"), XRC_TYPE_STRINGLIST);
		return xrc.GetXrcObject();
	}

	TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
	{
		XrcToXfbFilter filter(xrcObj, _("wxListBox"));
		filter.AddWindowProperties();
		//filter.AddProperty(_("style"),_("style"), XRC_TYPE_BITLIST);
		filter.AddProperty(_("content"),_("choices"), XRC_TYPE_STRINGLIST);
		return filter.GetXfbObject();
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
			(int)choices.Count(),
			strings,
			majorDim,
			obj->GetPropertyAsInteger(_("style")) | obj->GetPropertyAsInteger(_("window_style")));

		delete []strings;

		return radiobox;
	}

	TiXmlElement* ExportToXrc(IObject *obj)
	{
		ObjectToXrcFilter xrc(obj, _("wxRadioBox"), obj->GetPropertyAsString(_("name")));
		xrc.AddWindowProperties();
		//xrc.AddProperty(_("style"), _("style"), XRC_TYPE_BITLIST);
		xrc.AddProperty(_("choices"), _("content"), XRC_TYPE_STRINGLIST);
		xrc.AddProperty(_("majorDimension"), _("dimension"), XRC_TYPE_INTEGER);
		return xrc.GetXrcObject();
	}

	TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
	{
		XrcToXfbFilter filter(xrcObj, _("wxRadioBox"));
		filter.AddWindowProperties();
		//filter.AddProperty(_("style"),_("style"), XRC_TYPE_BITLIST);
		filter.AddProperty(_("content"),_("choices"), XRC_TYPE_STRINGLIST);
		filter.AddProperty(_("dimension"), _("majorDimension"), XRC_TYPE_INTEGER);
		return filter.GetXfbObject();
	}
};

class StatusBarComponent : public ComponentBase
{
public:
	wxObject* Create(IObject *obj, wxObject *parent)
	{
		wxStatusBar *sb = new wxStatusBar((wxWindow*)parent, -1,
			obj->GetPropertyAsInteger(_("style")) | obj->GetPropertyAsInteger(_("window_style")));
		sb->SetFieldsCount(obj->GetPropertyAsInteger(_("fields")));
		return sb;
	}

	TiXmlElement* ExportToXrc(IObject *obj)
	{
		ObjectToXrcFilter xrc(obj, _("wxStatusBar"), obj->GetPropertyAsString(_("name")));
		xrc.AddWindowProperties();
		//xrc.AddProperty(_("style"),_("style"),XRC_TYPE_BITLIST);
		xrc.AddProperty(_("fields"),_("fields"),XRC_TYPE_INTEGER);
		return xrc.GetXrcObject();
	}

	TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
	{
		XrcToXfbFilter filter(xrcObj, _("wxStatusBar"));
		filter.AddWindowProperties();
		//filter.AddProperty(_("style"),_("style"),XRC_TYPE_BITLIST);
		filter.AddProperty(_("fields"),_("fields"),XRC_TYPE_INTEGER);
		return filter.GetXfbObject();
	}
};

class MenuBarComponent : public ComponentBase
{
public:

	wxObject* Create(IObject *obj, wxObject *parent)
	{
		wxMenuBar *mb = new wxMenuBar(obj->GetPropertyAsInteger(_("style")) |
			obj->GetPropertyAsInteger(_("window_style")));
		return mb;
	}

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

class SubMenuComponent : public ComponentBase
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
    XrcToXfbFilter filter(xrcObj, _("submenu"));
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
			label = obj->GetPropertyAsString(_("label")) + wxT("\\t") + shortcut;

		xrc.AddPropertyValue(_("label"), label);
		xrc.AddProperty(_("help"),_("help"),XRC_TYPE_TEXT);

	    if (!obj->IsNull(_("bitmap")))
	      xrc.AddProperty(_("bitmap"),_("bitmap"),XRC_TYPE_BITMAP);

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
				int pos = label.Find(wxT("\\t"));
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
    filter.AddProperty(_("bitmap"),_("bitmap"),XRC_TYPE_BITMAP);
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
			obj->GetPropertyAsInteger(_("style")) | obj->GetPropertyAsInteger(_("window_style")) | wxTB_NOALIGN | wxTB_NODIVIDER | wxNO_BORDER);

		if (!obj->IsNull(_("bitmapsize")))
			tb->SetToolBitmapSize(obj->GetPropertyAsSize(_("bitmapsize")));
		if (!obj->IsNull(_("margins")))
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
		//xrc.AddProperty(_("style"), _("style"), XRC_TYPE_BITLIST);
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
		//filter.AddProperty(_("style"), _("style"), XRC_TYPE_BITLIST);
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
    xrc.AddProperty(_("bitmap"), _("bitmap"), XRC_TYPE_BITMAP);
		return xrc.GetXrcObject();
	}

	TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
	{
		XrcToXfbFilter filter(xrcObj, _("tool"));
		filter.AddWindowProperties();
		filter.AddProperty(_("label"), _("label"), XRC_TYPE_TEXT);
    filter.AddProperty(_("bitmap"), _("bitmap"), XRC_TYPE_BITMAP);
		return filter.GetXfbObject();
	}
};

class ChoiceComponent : public ComponentBase
{
public:
	wxObject* Create(IObject *obj, wxObject *parent)
	{
		wxArrayString choices = obj->GetPropertyAsArrayString(_("choices"));
		wxString *strings = new wxString[choices.Count()];
		for (unsigned int i=0; i < choices.Count(); i++)
			strings[i] = choices[i];

		wxChoice *choice = new wxChoice((wxWindow*)parent, -1,
			obj->GetPropertyAsPoint(_("pos")),
			obj->GetPropertyAsSize(_("size")),
			(int)choices.Count(),
			strings,
			obj->GetPropertyAsInteger(_("window_style")));

		choice->SetSelection(obj->GetPropertyAsInteger(_("selection")));

		delete []strings;

		return choice;
	}

	TiXmlElement* ExportToXrc(IObject *obj)
	{
		ObjectToXrcFilter xrc(obj, _("wxChoice"), obj->GetPropertyAsString(_("name")));
		xrc.AddWindowProperties();
		//xrc.AddProperty(_("style"), _("style"), XRC_TYPE_BITLIST);
		xrc.AddProperty(_("choices"), _("content"), XRC_TYPE_STRINGLIST);
		xrc.AddProperty(_("selection"), _("selection"), XRC_TYPE_INTEGER);
		return xrc.GetXrcObject();
	}

	TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
	{
		XrcToXfbFilter filter(xrcObj, _("wxChoice"));
		filter.AddWindowProperties();
		//filter.AddProperty(_("style"),_("style"), XRC_TYPE_BITLIST);
		filter.AddProperty(_("content"),_("choices"), XRC_TYPE_STRINGLIST);
		filter.AddProperty(_("selection"), _("selection"), XRC_TYPE_INTEGER);
		return filter.GetXfbObject();
	}

};

class SliderComponent : public ComponentBase
{
public:
	wxObject* Create(IObject *obj, wxObject *parent)
	{
		return new wxSlider((wxWindow *)parent,-1,
			obj->GetPropertyAsInteger(_("value")),
			obj->GetPropertyAsInteger(_("minValue")),
			obj->GetPropertyAsInteger(_("maxValue")),
			obj->GetPropertyAsPoint(_("pos")),
			obj->GetPropertyAsSize(_("size")),
			obj->GetPropertyAsInteger(_("style")) | obj->GetPropertyAsInteger(_("window_style")) | obj->GetPropertyAsInteger(_("window_style")));
	}

	TiXmlElement* ExportToXrc(IObject *obj)
	{
		ObjectToXrcFilter xrc(obj, _("wxSlider"), obj->GetPropertyAsString(_("name")));
		xrc.AddWindowProperties();
		//xrc.AddProperty(_("style"),_("style"), XRC_TYPE_BITLIST);
		xrc.AddProperty(_("value"), _("value"), XRC_TYPE_INTEGER);
		xrc.AddProperty(_("min"), _("minValue"), XRC_TYPE_INTEGER);
		xrc.AddProperty(_("max"), _("maxValue"), XRC_TYPE_INTEGER);
		return xrc.GetXrcObject();
	}

	TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
	{
		XrcToXfbFilter filter(xrcObj, _("wxSlider"));
		filter.AddWindowProperties();
		//filter.AddProperty(_("style"),_("style"), XRC_TYPE_BITLIST);
		filter.AddProperty(_("value"), _("value"), XRC_TYPE_INTEGER);
		filter.AddProperty(_("min"), _("minValue"), XRC_TYPE_INTEGER);
		filter.AddProperty(_("max"), _("maxValue"), XRC_TYPE_INTEGER);
		return filter.GetXfbObject();
	}

};

class GaugeComponent : public ComponentBase
{
public:
	wxObject* Create(IObject *obj, wxObject *parent)
	{
		wxGauge *gauge = new wxGauge((wxWindow *)parent,-1,
			obj->GetPropertyAsInteger(_("range")),
			obj->GetPropertyAsPoint(_("pos")),
			obj->GetPropertyAsSize(_("size")),
			obj->GetPropertyAsInteger(_("style")) | obj->GetPropertyAsInteger(_("window_style")));
		gauge->SetValue(obj->GetPropertyAsInteger(_("value")));
		return gauge;
	}

	TiXmlElement* ExportToXrc(IObject *obj)
	{
		ObjectToXrcFilter xrc(obj, _("wxGauge"), obj->GetPropertyAsString(_("name")));
		xrc.AddWindowProperties();
		//xrc.AddProperty(_("style"),_("style"), XRC_TYPE_BITLIST);
		xrc.AddProperty(_("range"), _("range"), XRC_TYPE_INTEGER);
		xrc.AddProperty(_("value"), _("value"), XRC_TYPE_INTEGER);
		return xrc.GetXrcObject();
	}

	TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
	{
		XrcToXfbFilter filter(xrcObj, _("wxGauge"));
		filter.AddWindowProperties();
		//filter.AddProperty(_("style"),_("style"), XRC_TYPE_BITLIST);
		filter.AddProperty(_("range"), _("range"), XRC_TYPE_INTEGER);
		filter.AddProperty(_("value"), _("value"), XRC_TYPE_INTEGER);
		return filter.GetXfbObject();
	}

};

///////////////////////////////////////////////////////////////////////////////

BEGIN_LIBRARY()

// Los forms no son considerados como windows !
ABSTRACT_COMPONENT("Frame",FrameFormComponent)
ABSTRACT_COMPONENT("Panel",PanelFormComponent)
ABSTRACT_COMPONENT("Dialog",DialogFormComponent)

WINDOW_COMPONENT("wxButton",ButtonComponent)
WINDOW_COMPONENT("wxBitmapButton",BitmapButtonComponent)
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
WINDOW_COMPONENT("wxMenuBar", MenuBarComponent)
WINDOW_COMPONENT("wxMenu", MenuComponent)
WINDOW_COMPONENT("submenu", SubMenuComponent)
WINDOW_COMPONENT("wxMenuItem", MenuItemComponent)
WINDOW_COMPONENT("separator", SeparatorComponent)
WINDOW_COMPONENT("wxListCtrl", ListCtrlComponent)
WINDOW_COMPONENT("wxStatusBar", StatusBarComponent)
WINDOW_COMPONENT("wxToolBar", ToolBarComponent)
WINDOW_COMPONENT("tool", ToolComponent)
WINDOW_COMPONENT("wxChoice", ChoiceComponent)
WINDOW_COMPONENT("wxSlider", SliderComponent)
WINDOW_COMPONENT("wxGauge", GaugeComponent)

// wxWindow style macros
MACRO(wxSIMPLE_BORDER)
MACRO(wxDOUBLE_BORDER)
MACRO(wxSUNKEN_BORDER)
MACRO(wxRAISED_BORDER)
MACRO(wxSTATIC_BORDER)
MACRO(wxNO_BORDER)
MACRO(wxTRANSPARENT_WINDOW)
MACRO(wxTAB_TRAVERSAL)
MACRO(wxWANTS_CHARS)
MACRO(wxVSCROLL)
MACRO(wxHSCROLL)
MACRO(wxALWAYS_SHOW_SB)
MACRO(wxCLIP_CHILDREN)
MACRO(wxFULL_REPAINT_ON_RESIZE)
MACRO(wxWS_EX_VALIDATE_RECURSIVELY)
MACRO(wxWS_EX_BLOCK_EVENTS)
MACRO(wxWS_EX_TRANSIENT)
MACRO(wxWS_EX_PROCESS_IDLE)
MACRO(wxWS_EX_PROCESS_UI_UPDATES)

// wxFrame style macros
MACRO(wxDEFAULT_FRAME_STYLE)
MACRO(wxICONIZE)
MACRO(wxCAPTION)
MACRO(wxMINIMIZE)
MACRO(wxMINIMIZE_BOX)
MACRO(wxMAXIMIZE)
MACRO(wxMAXIMIZE_BOX)
MACRO(wxCLOSE_BOX)
MACRO(wxSTAY_ON_TOP)
MACRO(wxSYSTEM_MENU)
MACRO(wxRESIZE_BORDER)
MACRO(wxFRAME_TOOL_WINDOW)
MACRO(wxFRAME_NO_TASKBAR)
MACRO(wxFRAME_FLOAT_ON_PARENT)
MACRO(wxFRAME_SHAPED)
MACRO(wxFRAME_EX_CONTEXTHELP)
MACRO(wxFRAME_EX_METAL)

// wxDialog style macros
MACRO(wxCAPTION)
MACRO(wxDEFAULT_DIALOG_STYLE)
MACRO(wxRESIZE_BORDER)
MACRO(wxSYSTEM_MENU)
MACRO(wxCLOSE_BOX)
MACRO(wxMAXIMIZE_BOX)
MACRO(wxMINIMIZE_BOX)
MACRO(wxTHICK_FRAME)
MACRO(wxSTAY_ON_TOP)
MACRO(wxNO_3D)
MACRO(wxDIALOG_NO_PARENT)

// wxButton
MACRO(wxBU_LEFT)
MACRO(wxBU_TOP)
MACRO(wxBU_RIGHT)
MACRO(wxBU_BOTTOM)
MACRO(wxBU_EXACTFIT)
MACRO(wxBU_AUTODRAW)

// wxStaticText
MACRO(wxALIGN_LEFT)
MACRO(wxALIGN_CENTRE)
MACRO(wxALIGN_RIGHT)
MACRO(wxST_NO_AUTORESIZE)

// wxTextCtrl
MACRO(wxTE_MULTILINE)
MACRO(wxTE_READONLY)
MACRO(wxTE_RICH)
MACRO(wxTE_AUTO_URL)
MACRO(wxTE_BESTWRAP)
MACRO(wxTE_CAPITALIZE)
MACRO(wxTE_CENTRE)
MACRO(wxTE_CHARWRAP)
MACRO(wxTE_DONTWRAP)
MACRO(wxTE_LEFT)
MACRO(wxTE_NOHIDESEL)
MACRO(wxTE_PASSWORD)
MACRO(wxTE_PROCESS_ENTER)
MACRO(wxTE_PROCESS_TAB)
MACRO(wxTE_RICH2)
MACRO(wxTE_RIGHT)
MACRO(wxTE_WORDWRAP)

// wxStaticLine
MACRO(wxLI_HORIZONTAL)
MACRO(wxLI_VERTICAL)

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

//wxMenuBar
MACRO(wxMB_DOCKABLE)

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

// wxSlider
MACRO(wxSL_AUTOTICKS)
MACRO(wxSL_BOTTOM)
MACRO(wxSL_HORIZONTAL)
MACRO(wxSL_INVERSE)
MACRO(wxSL_LABELS)
MACRO(wxSL_LEFT)
MACRO(wxSL_RIGHT)
MACRO(wxSL_SELRANGE)
MACRO(wxSL_TOP)
MACRO(wxSL_VERTICAL)

// wxComboBox
MACRO(wxCB_DROPDOWN)
MACRO(wxCB_READONLY)
MACRO(wxCB_SIMPLE)
MACRO(wxCB_SORT)

// wxCheckBox
MACRO(wxCHK_2STATE)
MACRO(wxCHK_3STATE)
MACRO(wxCHK_ALLOW_3RD_STATE_FOR_USER)

// wxGauge
MACRO(wxGA_HORIZONTAL)
MACRO(wxGA_SMOOTH)
MACRO(wxGA_VERTICAL)


END_LIBRARY()

